/****************************************************************************
** Meta object code from reading C++ file 'myqtimer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myqtimer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myqtimer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyQTimer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      18,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   27,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyQTimer[] = {
    "MyQTimer\0\0senal()\0senal2()\0seg\0"
    "setseg(int)\0"
};

void MyQTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyQTimer *_t = static_cast<MyQTimer *>(_o);
        switch (_id) {
        case 0: _t->senal(); break;
        case 1: _t->senal2(); break;
        case 2: _t->setseg((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyQTimer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyQTimer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MyQTimer,
      qt_meta_data_MyQTimer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyQTimer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyQTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyQTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyQTimer))
        return static_cast<void*>(const_cast< MyQTimer*>(this));
    return QThread::qt_metacast(_clname);
}

int MyQTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyQTimer::senal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MyQTimer::senal2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
