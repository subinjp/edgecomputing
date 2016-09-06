/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

//
// This ns-3 example demonstrates the use of helper functions to ease 
// the construction of simulation scenarios.
// 
// The simulation topology consists of a mixed wired and wireless
// scenario in which a hierarchical mobility model is used.
//
// The simulation layout consists of N backbone routers interconnected
// by an ad hoc wifi network.
// Each backbone router also has a local 802.11 network and is connected
// to a local LAN.  An additional set of (K-1) nodes are connected to
// this backbone.  Finally, a local LAN is connected to each router
// on the backbone, with L-1 additional hosts.
//
// The nodes are populated with TCP/IP stacks, and OLSR unicast routing
// on the backbone.  An example UDP transfer is shown.  The simulator
// be configured to output tcpdumps or traces from different nodes.
//
//
//          +--------------------------------------------------------+
//          |                                                        |
//          |              802.11 ad hoc, ns-2 mobility              | 
//          |                                                        |
//          +--------------------------------------------------------+
//                   |       o o o (N backbone routers)       |
//               +--------+                               +--------+
//     wired LAN | mobile |                     wired LAN | mobile |
//    -----------| router |                    -----------| router |
//               ---------                                ---------
//                   |                                        |
//          +----------------+                       +----------------+
//          |     802.11     |                       |     802.11     |
//          |   infra net    |                       |   infra net    |
//          |   K-1 hosts    |                       |   K-1 hosts    |
//          +----------------+                       +----------------+
//
// We'll send data from the first wired LAN node on the first wired LAN
// to the last wireless STA on the last infrastructure net, thereby
// causing packets to traverse CSMA to adhoc to infrastructure links
// 
// Note that certain mobility patterns may cause packet forwarding
// to fail (if nodes become disconnected) 

#include <fstream>
#include <string>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

//
// Define logging keyword for this file
//
NS_LOG_COMPONENT_DEFINE ("wifi_p2p");

//
// This function will be used below as a trace sink, if the command-line
// argument or default value "useCourseChangeCallback" is set to true
// 

int 
main (int argc, char *argv[])
{
  //
  // First, we declare and initialize a few local variables that control some 
  // simulation parameters.
  //
  uint32_t backboneNodes = 3;
  uint32_t infraNodes = 2;
  uint32_t lanNodes = 1;



  //
  // For convenience, we add the local variables to the command line argument
  // system so that they can be overridden with flags such as 
  // "--backboneNodes=20"
  //
  CommandLine cmd;
  cmd.AddValue ("backboneNodes", "number of backbone nodes", backboneNodes);
  cmd.AddValue ("infraNodes", "number of leaf nodes", infraNodes);
  cmd.AddValue ("lanNodes", "number of LAN nodes", lanNodes);

  //
  // The system global variables and the local values added to the argument
  // system can be overridden by command line arguments by using this call.
  //
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);


  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Construct the backbone                                                //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  //
  // Create a container to manage the nodes of the adhoc (backbone) network.
  // Later we'll create the rest of the nodes we'll need.
  //
  NodeContainer backbone;
  backbone.Create (backboneNodes);
  //
  // Create the backbone wifi net devices and install them into the nodes in 
  // our container
  //
  WifiHelper wifi;
  WifiMacHelper mac;
  mac.SetType ("ns3::AdhocWifiMac");
  //wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
  //                              "DataMode", StringValue ("OfdmRate54Mbps"));
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy.SetChannel (wifiChannel.Create ());
  NetDeviceContainer backboneDevices = wifi.Install (wifiPhy, mac, backbone);

  // We enable OLSR (which will be consulted at a higher priority than
  // the global routing) on the backbone ad hoc nodes
  NS_LOG_INFO ("Enabling OLSR routing on all backbone nodes");
  //OlsrHelper olsr;
  //
  // Add the IPv4 protocol stack to the nodes in our container
  //
  InternetStackHelper internet;
  //internet.SetRoutingHelper (olsr); // has effect on the next Install ()
  internet.Install (backbone);

  //
  // Assign IPv4 addresses to the device drivers (actually to the associated
  // IPv4 interfaces) we just created.
  //
  Ipv4AddressHelper ipAddrs;
  ipAddrs.SetBase ("192.168.0.0", "255.255.255.0");
  ipAddrs.Assign (backboneDevices);

  //
  // The ad-hoc network nodes need a mobility model so we aggregate one to 
  // each of the nodes we just finished building.
  //
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (20.0),
                                 "MinY", DoubleValue (20.0),
                                 "DeltaX", DoubleValue (20.0),
                                 "DeltaY", DoubleValue (20.0),
                                 "GridWidth", UintegerValue (5),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (backbone);


  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Construct the LANs                                                    //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  // Reset the address base-- all of the CSMA networks will be in
  // the "172.16 address space
  ipAddrs.SetBase ("172.16.0.0", "255.255.255.0");


  for (uint32_t i = 0; i < backboneNodes; ++i)
    {
      NS_LOG_INFO ("Configuring local area network for backbone node " << i);
      //
      // Create a container to manage the nodes of the LAN.  We need
      // two containers here; one with all of the new nodes, and one
      // with all of the nodes including new and existing nodes
      //
      NodeContainer newLanNodes;
      newLanNodes.Create (1);
      // Now, create the container with all nodes on this link
      NodeContainer lan (backbone.Get (i), newLanNodes);
      //
      // Create the CSMA net devices and install them into the nodes in our 
      // collection.
      //
      PointToPointHelper p2p;
      p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
      p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
      NetDeviceContainer p2pDevices = p2p.Install(lan);
      //NetDeviceContainer lanDevices = csma.Install (lan);
      //
      // Add the IPv4 protocol stack to the new LAN nodes
      //
      internet.Install (newLanNodes);
      //
      // Assign IPv4 addresses to the device drivers (actually to the 
      // associated IPv4 interfaces) we just created.
      //


      ipAddrs.Assign (p2pDevices);



      /*Ptr<Ipv4> ipv4 = backbone.Get (i)->GetObject<Ipv4>();
      Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
      Ipv4Address addri = iaddr.GetLocal ();
      Ipv4StaticRoutingHelper ipv4RoutingHelper;
      Ptr<Ipv4> ipv4n0 = newLanNodes.Get(0)->GetObject<Ipv4> ();
      Ptr<Ipv4StaticRouting> staticRouting_n0 = ipv4RoutingHelper.GetStaticRouting (ipv4n0);
      staticRouting_n0->SetDefaultRoute(addri, 1);*/
      //
      // Assign a new network prefix for the next LAN, according to the
      // network mask initialized above
      //



      ipAddrs.NewNetwork ();

      //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
      //
      // The new LAN nodes need a mobility model so we aggregate one
      // to each of the nodes we just finished building.
      //


      MobilityHelper mobilityLan;
      Ptr<ListPositionAllocator> subnetAlloc = 
        CreateObject<ListPositionAllocator> ();
      for (uint32_t j = 0; j < newLanNodes.GetN (); ++j)
        {
          subnetAlloc->Add (Vector (0.0, j*10 + 10, 0.0));
        }
      mobilityLan.PushReferenceMobilityModel (backbone.Get (i));
      mobilityLan.SetPositionAllocator (subnetAlloc);
      mobilityLan.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
      mobilityLan.Install (newLanNodes);
    }


  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Construct the mobile networks                                         //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  // Reset the address base-- all of the 802.11 networks will be in
  // the "10.0" address space



  ipAddrs.SetBase ("10.0.0.0", "255.255.255.0");

  for (uint32_t i = 0; i < backboneNodes; ++i)
    {
      NS_LOG_INFO ("Configuring wireless network for backbone node " << i);
      //
      // Create a container to manage the nodes of the LAN.  We need
      // two containers here; one with all of the new nodes, and one
      // with all of the nodes including new and existing nodes
      //
      NodeContainer stas;
      stas.Create (infraNodes);
      // Now, create the container with all nodes on this link
      NodeContainer infra (backbone.Get (i), stas);
      //
      // Create an infrastructure network
      //
      WifiHelper wifiInfra;
      WifiMacHelper macInfra;
      wifiPhy.SetChannel (wifiChannel.Create ());
      // Create unique ssids for these networks
      std::string ssidString ("wifi-infra");
      std::stringstream ss;
      ss << i;
      ssidString += ss.str ();
      Ssid ssid = Ssid (ssidString);
      //wifiInfra.SetRemoteStationManager ("ns3::ArfWifiManager");
      // setup stas
      macInfra.SetType ("ns3::StaWifiMac",
                        "Ssid", SsidValue (ssid),
                        "ActiveProbing", BooleanValue (false));
      NetDeviceContainer staDevices = wifiInfra.Install (wifiPhy, macInfra, stas);
      // setup ap.
      macInfra.SetType ("ns3::ApWifiMac",
                        "Ssid", SsidValue (ssid));
      NetDeviceContainer apDevices = wifiInfra.Install (wifiPhy, macInfra, backbone.Get (i));
      // Collect all of these new devices
      NetDeviceContainer infraDevices (apDevices, staDevices);

      // Add the IPv4 protocol stack to the nodes in our container
      //
      internet.Install (stas);
      //
      // Assign IPv4 addresses to the device drivers (actually to the associated
      // IPv4 interfaces) we just created.
      //


      ipAddrs.Assign (infraDevices);

      //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

      //
      // Assign a new network prefix for each mobile network, according to 
      // the network mask initialized above
      //
      ipAddrs.NewNetwork ();
      //
      // The new wireless nodes need a mobility model so we aggregate one 
      // to each of the nodes we just finished building.
      //
      Ptr<ListPositionAllocator> subnetAlloc = 
        CreateObject<ListPositionAllocator> ();
      for (uint32_t j = 0; j < infra.GetN (); ++j)
        {
          subnetAlloc->Add (Vector (0.0, j, 0.0));
        }
      mobility.PushReferenceMobilityModel (backbone.Get (i));
      mobility.SetPositionAllocator (subnetAlloc);
      mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

      mobility.Install (stas);
    }

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Application configuration                                             //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  // Create the OnOff application to send UDP datagrams of size
  // 210 bytes at a rate of 10 Kb/s, between two nodes
  // We'll send data from the first wired LAN node on the first wired LAN
  // to the last wireless STA on the last infrastructure net, thereby
  // causing packets to traverse CSMA to adhoc to infrastructure links

  NS_LOG_INFO ("Create Applications.");
  /*uint16_t port = 9;   // Discard port (RFC 863)

  // Let's make sure that the user does not define too few nodes
  // to make this example work.  We need lanNodes > 1  and infraNodes > 1
  NS_ASSERT (lanNodes > 1 && infraNodes > 1);*/

  // We want the source to be the first node created outside of the backbone
  // Conveniently, the variable "backboneNodes" holds this node index value
  uint32_t firstNodeIndex = backboneNodes+2;
  Ptr<Node> appSource = NodeList::GetNode (firstNodeIndex);
  Ipv4Address sourceAddr = appSource->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

  // We want the sink to be the last node created in the topology.
  uint32_t lastNodeIndex = backboneNodes+backboneNodes*(lanNodes);
  Ptr<Node> appSink = NodeList::GetNode (lastNodeIndex);
  // Let's fetch the IP address of the last node, which is on Ipv4Interface 1
  //Ipv4Address remoteAddr = appSink->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (appSource);
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (sourceAddr, 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (3.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (appSink);
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  /*for (uint32_t i = 0; i < backboneNodes; ++i)
  {
  	  uint32_t j = 0;
	  Ptr<Node> appSource = NodeList::GetNode (backboneNodes+i);
	  Ipv4Address sourceAddr = appSource->GetObject<Ipv4> ()->GetAddress (2, 0).GetLocal ();

	  // We want the sink to be the last node created in the topology.
	  uint32_t lastNodeIndex = backboneNodes + backboneNodes*(lanNodes) + j;
	  Ptr<Node> appSink = NodeList::GetNode (lastNodeIndex);
	  // Let's fetch the IP address of the last node, which is on Ipv4Interface 1
	  //Ipv4Address remoteAddr = appSink->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

	  UdpEchoServerHelper echoServer (9);

	  ApplicationContainer serverApps = echoServer.Install (appSource);
	  serverApps.Start (Seconds (1.0));
	  serverApps.Stop (Seconds (10.0));

	  UdpEchoClientHelper echoClient (sourceAddr, 9);
	  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
	  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	  ApplicationContainer clientApps = echoClient.Install (appSink);
	  clientApps.Start (Seconds (2.0));
	  clientApps.Stop (Seconds (10.0));
	  j+=2;
  }*/


  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Tracing configuration                                                 //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  NS_LOG_INFO ("Configure Tracing.");
  PointToPointHelper p2p;

  //
  // Let's set up some ns-2-like ascii traces, using another helper class
  //
  AsciiTraceHelper ascii;
  Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream ("wifimodified.tr");
  wifiPhy.EnableAsciiAll (stream);
  //p2p.EnableAsciiAll (stream);
  internet.EnableAsciiIpv4All (stream);

  // Csma captures in non-promiscuous mode
    //p2p.EnablePcapAll ("mixed-wireless", false);
    // pcap captures on the backbone wifi devices
    wifiPhy.EnablePcap ("wifimodified", backboneDevices, false);
    // pcap trace on the application data sink
    wifiPhy.EnablePcap ("wifimodified", appSink->GetId (), 0);

  AnimationInterface anim ("wifi-p2p.xml");

  /////////////////////////////////////////////////////////////////////////// 
  //                                                                       //
  // Run simulation                                                        //
  //                                                                       //
  /////////////////////////////////////////////////////////////////////////// 

  NS_LOG_INFO ("Run Simulation.");
  //AnimationInterface anim("mixedwireless.xml");
  Simulator::Stop (Seconds (10.0));
  Simulator::Run ();
  Simulator::Destroy ();
}
