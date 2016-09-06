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
// The simulation layout consists of N backboneNodes routers interconnected
// by an ad hoc wifi network.
// Each backboneNodes router also has a local 802.11 network and is connected
// to a remote node through point to point network.  An additional set of (K-1) nodes are connected to
// this backboneNodes.
//
// The nodes are populated with TCP/IP stacks.
//
//
//          +--------------------------------------------------------+
//          |                                                        |
//          |              CSMA-------------CSMA            |
//          |                                                        |
//          +--------------------------------------------------------+
//                   |       o o o (N backboneNodes routers)       |
//               +--------+                               +--------+
//     wired p2p | mobile |                     wired p2p | mobile |
//    -----------| router |                    -----------| router |
//               ---------                                ---------
//                   |                                        |
//          +----------------+                       +----------------+
//          |     802.11     |                       |     802.11     |
//          |   infra net    |                       |   infra net    |
//          |   K-1 hosts    |                       |   K-1 hosts    |
//          +----------------+                       +----------------+
//
//We will send packet from any of the wifi nodes to  the corresponding remote node(server)
//attached to the AP node.


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
NS_LOG_COMPONENT_DEFINE ("edgecloud_Stream");

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
  uint32_t nWifis = 6;
  uint32_t nStas = 4;
  uint32_t p2pNode = 1;



  //
  // For convenience, we add the local variables to the command line argument
  // system so that they can be overridden with flags such as
  // "--nWifis=20"
  //
  CommandLine cmd;

  cmd.AddValue ("nWifis", "number of wifi networks", nWifis);
  cmd.AddValue ("nStas", "Number of stations per wifi network", nStas);

  //
  // The system global variables and the local values added to the argument
  // system can be overridden by command line arguments by using this call.
  //
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpTraceClient", LOG_LEVEL_INFO);
  //LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);


  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  // Construct the backboneNodes                                                //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////

  //
  // Create a container to manage the nodes of the adhoc (backboneNodes) network.
  // Later we'll create the rest of the nodes we'll need.
  //
  NodeContainer backboneNodes;
  backboneNodes.Create (nWifis);
  //
  // Create the backboneNodes wifi net devices and install them into the nodes in
  // our container
  //
  CsmaHelper csma;

  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy.SetChannel (wifiChannel.Create ());

  csma.SetChannelAttribute ("DataRate", StringValue ("5Mbps"));
  csma.SetChannelAttribute ("Delay", StringValue ("5ms"));
  NetDeviceContainer backboneNodesDevices = csma.Install (backboneNodes);

  InternetStackHelper internet;

  internet.Install (backboneNodes);

  //
  // Assign IPv4 addresses to the device drivers (actually to the associated
  // IPv4 interfaces) we just created.
  //
  Ipv4AddressHelper ipAddrs;
  ipAddrs.SetBase ("192.168.0.0", "255.255.255.0");
  ipAddrs.Assign (backboneNodesDevices);

  //
  // The ad-hoc network nodes need a mobility model so we aggregate one to
  // each of the nodes we just finished building.
  //
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (20.0),
                                 "MinY", DoubleValue (20.0),
                                 "DeltaX", DoubleValue (500.0),
                                 "DeltaY", DoubleValue (20.0),
                                 "GridWidth", UintegerValue (5),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (backboneNodes);


  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  // Construct the p2p Nodes                                                    //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////

  // Reset the address base-- all of the CSMA networks will be in
  // the "172.16 address space
  ipAddrs.SetBase ("172.16.0.0", "255.255.255.0");


  for (uint32_t i = 0; i < nWifis; ++i)
    {
      NS_LOG_INFO ("Configuring p2p network for backboneNodes node " << i);
      //
      // Create a container to manage the nodes of the p2pNetwork.  We need
      // two containers here; one with all of the new nodes, and one
      // with all of the nodes including new and existing nodes
      //
      NodeContainer p2pNodes;
      p2pNodes.Create (1);
      // Now, create the container with all nodes on this link
      NodeContainer p2pNetwork (backboneNodes.Get (i), p2pNodes);
      //
      // Create the CSMA net devices and install them into the nodes in our
      // collection.
      //
      PointToPointHelper p2p;
      p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
      p2p.SetChannelAttribute ("Delay", StringValue ("5ms"));
      NetDeviceContainer p2pDevices = p2p.Install(p2pNetwork);
      //NetDeviceContainer p2pNetworkDevices = csma.Install (p2pNetwork);
      //
      // Add the IPv4 protocol stack to the new p2pNetwork nodes
      //
      internet.Install (p2pNodes);
      //
      // Assign IPv4 addresses to the device drivers (actually to the
      // associated IPv4 interfaces) we just created.
      //
      ipAddrs.Assign (p2pDevices);



      /*Ptr<Ipv4> ipv4 = backboneNodes.Get (i)->GetObject<Ipv4>();
      Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
      Ipv4Address addri = iaddr.GetLocal ();
      Ipv4StaticRoutingHelper ipv4RoutingHelper;
      Ptr<Ipv4> ipv4n0 = p2pNodes.Get(0)->GetObject<Ipv4> ();
      Ptr<Ipv4StaticRouting> staticRouting_n0 = ipv4RoutingHelper.GetStaticRouting (ipv4n0);
      staticRouting_n0->SetDefaultRoute(addri, 1);*/
      //
      // Assign a new network prefix for the next p2p Network, according to the
      // network mask initialized above
      //
      ipAddrs.NewNetwork ();

      //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
      //
      // The new p2pNetwork nodes need a mobility model so we aggregate one
      // to each of the nodes we just finished building.
      //


      MobilityHelper mobilityp2pNetwork;
      Ptr<ListPositionAllocator> subnetAlloc =
        CreateObject<ListPositionAllocator> ();
      for (uint32_t j = 0; j < p2pNodes.GetN (); ++j)
        {
          subnetAlloc->Add (Vector (0.0, j*10 + 10, 0.0));
        }
      mobilityp2pNetwork.PushReferenceMobilityModel (backboneNodes.Get (i));
      mobilityp2pNetwork.SetPositionAllocator (subnetAlloc);
      mobilityp2pNetwork.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
      mobilityp2pNetwork.Install (p2pNodes);
    }


  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  // Construct the mobile networks                                         //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////

  // Reset the address base-- all of the 802.11 networks will be in
  // the "10.0" address space



  ipAddrs.SetBase ("10.0.0.0", "255.255.255.0");

  for (uint32_t i = 0; i < nWifis; ++i)
    {
      NS_LOG_INFO ("Configuring wireless network for backboneNodes node " << i);
      //
      // Create a container to manage the nodes of the wifi network.  We need
      // two containers here; one with all of the new nodes, and one
      // with all of the nodes including new and existing nodes
      //
      NodeContainer stas;
      stas.Create (nStas);
      // Now, create the container with all nodes on this link
      NodeContainer infra (backboneNodes.Get (i), stas);
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
      NetDeviceContainer apDevices = wifiInfra.Install (wifiPhy, macInfra, backboneNodes.Get (i));
      // Collect all of these new devices
      NetDeviceContainer sta_ap_Devices (apDevices, staDevices);

      // Add the IPv4 protocol stack to the nodes in our container
      //
      internet.Install (stas);
      //
      // Assign IPv4 addresses to the device drivers (actually to the associated
      // IPv4 interfaces) we just created.
      //


      ipAddrs.Assign (sta_ap_Devices);

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
      uint32_t temp1 = 0,temp2=0;
      for (uint32_t j = 0; j < infra.GetN (); ++j)
      {
         	  subnetAlloc->Add (Vector (15.0+temp1, j+2, 15.0+temp2));
              temp1=temp1+3;
              temp2=temp2+15;

      }
      mobility.PushReferenceMobilityModel (backboneNodes.Get (i));
      mobility.SetPositionAllocator (subnetAlloc);
      mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

      mobility.Install (stas);
    }
  // Create router nodes, initialize routing database and set up the routing
  // tables in the nodes.
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  // Application configuration                                             //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////


  NS_LOG_INFO ("Create Applications.");

  /*
  //get the index of the source node
  uint32_t firstNodeIndex = nWifis;
  Ptr<Node> appSource = NodeList::GetNode (firstNodeIndex);
  Ipv4Address sourceAddr = appSource->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

  // We want the sink to be the last node created in the topology.
  uint32_t lastNodeIndex = nWifis+nWifis*(p2pNode)+4;
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
  clientApps.Stop (Seconds (10.0));*/
  uint32_t j = 0;
  uint32_t k = -2;
  for (uint32_t i = 0; i < nWifis; ++i)
  {
	  if(i%2==0)
	  {
		  k+=2;
	  }

  	  //get the index of the source node
  	  uint32_t firstNodeIndex = nWifis+k;
  	  Ptr<Node> appSource = NodeList::GetNode (firstNodeIndex);
  	  Ipv4Address sourceAddr = appSource->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

  	  for (uint32_t m= 0; m < nStas; ++m)
  	  {
  	  // We want the sink to be the last node created in the topology.
  	  uint32_t lastNodeIndex = nWifis+nWifis*(p2pNode)+j;
  	  Ptr<Node> appSink = NodeList::GetNode (lastNodeIndex);
  	  // Let's fetch the IP address of the last node, which is on Ipv4Interface 1
  	  //Ipv4Address remoteAddr = appSink->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();

  	  UdpEchoServerHelper echoServer (9);

  	  ApplicationContainer serverApps = echoServer.Install (appSource);
  	  serverApps.Start (Seconds (1.0));
  	  //serverApps.Stop (Seconds (300.0));

  	  uint32_t MaxPacketSize = 1024;
  	  Time interPacketInterval = Seconds (0.01);
  	  uint32_t maxPacketCount = 3500;

  	  UdpEchoClientHelper echoClient (sourceAddr, 9);
  	  echoClient.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  	  echoClient.SetAttribute ("Interval", TimeValue (interPacketInterval));
  	  echoClient.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  	  ApplicationContainer clientApps = echoClient.Install (appSink);
  	  clientApps.Start (Seconds (2.0));
  	  //clientApps.Stop (Seconds (300.0));
  	  j+=1;
  	  // pcap trace on the application data sink
  	  wifiPhy.EnablePcap ("edgecloud_Stream", appSink->GetId (), 0);
  	  }
  }


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
  Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream ("edgecloud_Stream.tr");
  wifiPhy.EnableAsciiAll (stream);
  //p2p.EnableAsciiAll (stream);
  internet.EnableAsciiIpv4All (stream);

  // p2p captures in non-promiscuous mode
  p2p.EnablePcapAll ("edgecloud_Stream", false);
  //pcap captures on the backboneNodes wifi devices
  //wifiPhy.EnablePcap ("edgecloud_Stream", backboneNodesDevices, false);


  AnimationInterface anim ("edgecloud_Stream.xml");

  ///////////////////////////////////////////////////////////////////////////
  //                                                                       //
  // Run simulation                                                        //
  //                                                                       //
  ///////////////////////////////////////////////////////////////////////////

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop ();
  Simulator::Run ();
  Simulator::Destroy ();
}
