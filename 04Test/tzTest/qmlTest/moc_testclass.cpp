/****************************************************************************
** Meta object code from reading C++ file 'testclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImagePaintEvent_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImagePaintEvent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImagePaintEvent_t qt_meta_stringdata_ImagePaintEvent = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ImagePaintEvent"
QT_MOC_LITERAL(1, 16, 8), // "sigPaint"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "ImagePaintEvent\0sigPaint\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImagePaintEvent[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void ImagePaintEvent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImagePaintEvent *_t = static_cast<ImagePaintEvent *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigPaint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImagePaintEvent::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImagePaintEvent::sigPaint)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ImagePaintEvent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImagePaintEvent.data,
      qt_meta_data_ImagePaintEvent,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImagePaintEvent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImagePaintEvent::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImagePaintEvent.stringdata0))
        return static_cast<void*>(const_cast< ImagePaintEvent*>(this));
    return QObject::qt_metacast(_clname);
}

int ImagePaintEvent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ImagePaintEvent::sigPaint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_testclass_t {
    QByteArrayData data[11];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_testclass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_testclass_t qt_meta_stringdata_testclass = {
    {
QT_MOC_LITERAL(0, 0, 9), // "testclass"
QT_MOC_LITERAL(1, 10, 17), // "sigUpdateImageRGB"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "sigUpdateImageIris"
QT_MOC_LITERAL(4, 48, 27), // "slotOnBtnOpenIrisDevClicked"
QT_MOC_LITERAL(5, 76, 21), // "slotUpdateImageov2710"
QT_MOC_LITERAL(6, 98, 26), // "slotOnBtnOpenRGBDevClicked"
QT_MOC_LITERAL(7, 125, 18), // "ov5640imageUpdated"
QT_MOC_LITERAL(8, 144, 3), // "img"
QT_MOC_LITERAL(9, 148, 30), // "slotOnBtnSaveImgIrisDevClicked"
QT_MOC_LITERAL(10, 179, 29) // "slotOnBtnSaveImgRGBDevClicked"

    },
    "testclass\0sigUpdateImageRGB\0\0"
    "sigUpdateImageIris\0slotOnBtnOpenIrisDevClicked\0"
    "slotUpdateImageov2710\0slotOnBtnOpenRGBDevClicked\0"
    "ov5640imageUpdated\0img\0"
    "slotOnBtnSaveImgIrisDevClicked\0"
    "slotOnBtnSaveImgRGBDevClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_testclass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    1,   59,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void testclass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        testclass *_t = static_cast<testclass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigUpdateImageRGB(); break;
        case 1: _t->sigUpdateImageIris(); break;
        case 2: _t->slotOnBtnOpenIrisDevClicked(); break;
        case 3: _t->slotUpdateImageov2710(); break;
        case 4: _t->slotOnBtnOpenRGBDevClicked(); break;
        case 5: _t->ov5640imageUpdated((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->slotOnBtnSaveImgIrisDevClicked(); break;
        case 7: _t->slotOnBtnSaveImgRGBDevClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (testclass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&testclass::sigUpdateImageRGB)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (testclass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&testclass::sigUpdateImageIris)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject testclass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_testclass.data,
      qt_meta_data_testclass,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *testclass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *testclass::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_testclass.stringdata0))
        return static_cast<void*>(const_cast< testclass*>(this));
    return QObject::qt_metacast(_clname);
}

int testclass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void testclass::sigUpdateImageRGB()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void testclass::sigUpdateImageIris()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
