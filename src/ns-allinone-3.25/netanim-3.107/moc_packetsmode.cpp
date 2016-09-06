/****************************************************************************
** Meta object code from reading C++ file 'packetsmode.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "packetsmode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packetsmode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__PacketsMode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      33,   21,   21,   21, 0x08,
      46,   21,   21,   21, 0x08,
      73,   60,   21,   21, 0x08,
     113,  102,   21,   21, 0x08,
     153,  140,   21,   21, 0x08,
     190,  186,   21,   21, 0x08,
     215,   21,   21,   21, 0x08,
     235,   21,   21,   21, 0x08,
     257,   21,   21,   21, 0x08,
     277,   21,   21,   21, 0x08,
     303,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__PacketsMode[] = {
    "netanim::PacketsMode\0\0testSlot()\0"
    "zoomInSlot()\0zoomOutSlot()\0fromTimeText\0"
    "fromTimeChangedSlot(QString)\0toTimeText\0"
    "toTimeChangedSlot(QString)\0allowedNodes\0"
    "allowedNodesChangedSlot(QString)\0reg\0"
    "regexFilterSlot(QString)\0showGridLinesSlot()\0"
    "showPacketTableSlot()\0filterClickedSlot()\0"
    "submitFilterClickedSlot()\0"
    "showGraphClickedSlot()\0"
};

void netanim::PacketsMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PacketsMode *_t = static_cast<PacketsMode *>(_o);
        switch (_id) {
        case 0: _t->testSlot(); break;
        case 1: _t->zoomInSlot(); break;
        case 2: _t->zoomOutSlot(); break;
        case 3: _t->fromTimeChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->toTimeChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->allowedNodesChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->regexFilterSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->showGridLinesSlot(); break;
        case 8: _t->showPacketTableSlot(); break;
        case 9: _t->filterClickedSlot(); break;
        case 10: _t->submitFilterClickedSlot(); break;
        case 11: _t->showGraphClickedSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netanim::PacketsMode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::PacketsMode::staticMetaObject = {
    { &Mode::staticMetaObject, qt_meta_stringdata_netanim__PacketsMode,
      qt_meta_data_netanim__PacketsMode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::PacketsMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::PacketsMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::PacketsMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__PacketsMode))
        return static_cast<void*>(const_cast< PacketsMode*>(this));
    return Mode::qt_metacast(_clname);
}

int netanim::PacketsMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Mode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
