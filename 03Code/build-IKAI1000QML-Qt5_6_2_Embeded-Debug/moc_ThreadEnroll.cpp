/****************************************************************************
** Meta object code from reading C++ file 'ThreadEnroll.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IKAI1000QML/ThreadEnroll.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ThreadEnroll.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ThreadEnroll_t {
    QByteArrayData data[14];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadEnroll_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadEnroll_t qt_meta_stringdata_ThreadEnroll = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ThreadEnroll"
QT_MOC_LITERAL(1, 13, 11), // "enrollState"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "state"
QT_MOC_LITERAL(4, 32, 11), // "beginEnroll"
QT_MOC_LITERAL(5, 44, 12), // "enrollResult"
QT_MOC_LITERAL(6, 57, 14), // "IKSDKIrisInfo*"
QT_MOC_LITERAL(7, 72, 8), // "enrIrisL"
QT_MOC_LITERAL(8, 81, 7), // "numEnrL"
QT_MOC_LITERAL(9, 89, 8), // "enrIrisR"
QT_MOC_LITERAL(10, 98, 7), // "numEnrR"
QT_MOC_LITERAL(11, 106, 12), // "IKResultFlag"
QT_MOC_LITERAL(12, 119, 6), // "IKflag"
QT_MOC_LITERAL(13, 126, 8) // "doEnroll"

    },
    "ThreadEnroll\0enrollState\0\0state\0"
    "beginEnroll\0enrollResult\0IKSDKIrisInfo*\0"
    "enrIrisL\0numEnrL\0enrIrisR\0numEnrR\0"
    "IKResultFlag\0IKflag\0doEnroll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadEnroll[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    5,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 11,    7,    8,    9,   10,   12,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ThreadEnroll::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ThreadEnroll *_t = static_cast<ThreadEnroll *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enrollState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->beginEnroll(); break;
        case 2: _t->enrollResult((*reinterpret_cast< IKSDKIrisInfo*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< IKSDKIrisInfo*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< IKResultFlag(*)>(_a[5]))); break;
        case 3: _t->doEnroll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ThreadEnroll::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadEnroll::enrollState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ThreadEnroll::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadEnroll::beginEnroll)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ThreadEnroll::*_t)(IKSDKIrisInfo * , int , IKSDKIrisInfo * , int , IKResultFlag );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadEnroll::enrollResult)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ThreadEnroll::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ThreadEnroll.data,
      qt_meta_data_ThreadEnroll,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ThreadEnroll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadEnroll::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadEnroll.stringdata0))
        return static_cast<void*>(const_cast< ThreadEnroll*>(this));
    return QObject::qt_metacast(_clname);
}

int ThreadEnroll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThreadEnroll::enrollState(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadEnroll::beginEnroll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ThreadEnroll::enrollResult(IKSDKIrisInfo * _t1, int _t2, IKSDKIrisInfo * _t3, int _t4, IKResultFlag _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
