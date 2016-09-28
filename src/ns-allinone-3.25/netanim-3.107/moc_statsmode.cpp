/****************************************************************************
** Meta object code from reading C++ file 'statsmode.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "statsmode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statsmode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__NodeButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_netanim__NodeButton[] = {
    "netanim::NodeButton\0\0buttonClickedSlot()\0"
};

void netanim::NodeButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NodeButton *_t = static_cast<NodeButton *>(_o);
        switch (_id) {
        case 0: _t->buttonClickedSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData netanim::NodeButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::NodeButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_netanim__NodeButton,
      qt_meta_data_netanim__NodeButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::NodeButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::NodeButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::NodeButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__NodeButton))
        return static_cast<void*>(const_cast< NodeButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int netanim::NodeButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_netanim__StatsMode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      31,   19,   19,   19, 0x08,
      63,   19,   19,   19, 0x08,
      84,   19,   19,   19, 0x08,
     113,  107,   19,   19, 0x08,
     144,  138,   19,   19, 0x08,
     168,  138,   19,   19, 0x08,
     186,   19,   19,   19, 0x08,
     231,  218,   19,   19, 0x08,
     278,  264,   19,   19, 0x08,
     311,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__StatsMode[] = {
    "netanim::StatsMode\0\0testSlot()\0"
    "clickRoutingTraceFileOpenSlot()\0"
    "selectAllNodesSlot()\0deselectAllNodesSlot()\0"
    "index\0statTypeChangedSlot(int)\0value\0"
    "updateTimelineSlot(int)\0fontSizeSlot(int)\0"
    "clickFlowMonTraceFileOpenSlot()\0"
    "allowedNodes\0allowedNodesChangedSlot(QString)\0"
    "counterString\0counterIndexChangedSlot(QString)\0"
    "showChartSlot()\0"
};

void netanim::StatsMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StatsMode *_t = static_cast<StatsMode *>(_o);
        switch (_id) {
        case 0: _t->testSlot(); break;
        case 1: _t->clickRoutingTraceFileOpenSlot(); break;
        case 2: _t->selectAllNodesSlot(); break;
        case 3: _t->deselectAllNodesSlot(); break;
        case 4: _t->statTypeChangedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateTimelineSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->fontSizeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->clickFlowMonTraceFileOpenSlot(); break;
        case 8: _t->allowedNodesChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->counterIndexChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->showChartSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netanim::StatsMode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::StatsMode::staticMetaObject = {
    { &Mode::staticMetaObject, qt_meta_stringdata_netanim__StatsMode,
      qt_meta_data_netanim__StatsMode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::StatsMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::StatsMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::StatsMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__StatsMode))
        return static_cast<void*>(const_cast< StatsMode*>(this));
    return Mode::qt_metacast(_clname);
}

int netanim::StatsMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Mode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
