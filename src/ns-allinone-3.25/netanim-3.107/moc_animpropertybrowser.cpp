/****************************************************************************
** Meta object code from reading C++ file 'animpropertybrowser.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "animpropertybrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animpropertybrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__AnimPropertyBroswer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   30,   29,   29, 0x08,
      69,   67,   29,   29, 0x08,
     107,   67,   29,   29, 0x08,
     144,   67,   29,   29, 0x08,
     181,   67,   29,   29, 0x08,
     221,  216,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__AnimPropertyBroswer[] = {
    "netanim::AnimPropertyBroswer\0\0newIndex\0"
    "nodeIdSelectorSlot(QString)\0,\0"
    "valueChangedSlot(QtProperty*,QString)\0"
    "valueChangedSlot(QtProperty*,double)\0"
    "valueChangedSlot(QtProperty*,QColor)\0"
    "valueChangedSlot(QtProperty*,bool)\0"
    "mode\0modeChangedSlot(QString)\0"
};

void netanim::AnimPropertyBroswer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnimPropertyBroswer *_t = static_cast<AnimPropertyBroswer *>(_o);
        switch (_id) {
        case 0: _t->nodeIdSelectorSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->valueChangedSlot((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->valueChangedSlot((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->valueChangedSlot((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 4: _t->valueChangedSlot((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->modeChangedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netanim::AnimPropertyBroswer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::AnimPropertyBroswer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_netanim__AnimPropertyBroswer,
      qt_meta_data_netanim__AnimPropertyBroswer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::AnimPropertyBroswer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::AnimPropertyBroswer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::AnimPropertyBroswer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__AnimPropertyBroswer))
        return static_cast<void*>(const_cast< AnimPropertyBroswer*>(this));
    return QWidget::qt_metacast(_clname);
}

int netanim::AnimPropertyBroswer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
