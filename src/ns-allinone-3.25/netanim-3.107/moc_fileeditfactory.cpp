/****************************************************************************
** Meta object code from reading C++ file 'fileeditfactory.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtpropertybrowser/src/fileeditfactory.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileeditfactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileEditFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   17,   16,   16, 0x08,
      89,   73,   16,   16, 0x08,
     134,  128,   16,   16, 0x08,
     163,  156,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FileEditFactory[] = {
    "FileEditFactory\0\0property,value\0"
    "slotPropertyChanged(QtProperty*,QString)\0"
    "property,filter\0slotFilterChanged(QtProperty*,QString)\0"
    "value\0slotSetValue(QString)\0object\0"
    "slotEditorDestroyed(QObject*)\0"
};

void FileEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileEditFactory *_t = static_cast<FileEditFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slotFilterChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileEditFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileEditFactory::staticMetaObject = {
    { &QtAbstractEditorFactory<FilePathManager>::staticMetaObject, qt_meta_stringdata_FileEditFactory,
      qt_meta_data_FileEditFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileEditFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileEditFactory))
        return static_cast<void*>(const_cast< FileEditFactory*>(this));
    return QtAbstractEditorFactory<FilePathManager>::qt_metacast(_clname);
}

int FileEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAbstractEditorFactory<FilePathManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
