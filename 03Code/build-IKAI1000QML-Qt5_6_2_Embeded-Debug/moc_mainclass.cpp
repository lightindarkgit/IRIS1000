/****************************************************************************
** Meta object code from reading C++ file 'mainclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../IKAI1000QML/mainclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainclass.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ThreadSwipeCard_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadSwipeCard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadSwipeCard_t qt_meta_stringdata_ThreadSwipeCard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ThreadSwipeCard"
QT_MOC_LITERAL(1, 16, 13), // "sigSendCarNum"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "hid"
QT_MOC_LITERAL(4, 35, 3) // "pid"

    },
    "ThreadSwipeCard\0sigSendCarNum\0\0hid\0"
    "pid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadSwipeCard[] = {

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
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void ThreadSwipeCard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ThreadSwipeCard *_t = static_cast<ThreadSwipeCard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSendCarNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ThreadSwipeCard::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadSwipeCard::sigSendCarNum)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ThreadSwipeCard::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ThreadSwipeCard.data,
      qt_meta_data_ThreadSwipeCard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ThreadSwipeCard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadSwipeCard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadSwipeCard.stringdata0))
        return static_cast<void*>(const_cast< ThreadSwipeCard*>(this));
    return QThread::qt_metacast(_clname);
}

int ThreadSwipeCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void ThreadSwipeCard::sigSendCarNum(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_mainClass_t {
    QByteArrayData data[55];
    char stringdata0[710];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainClass_t qt_meta_stringdata_mainClass = {
    {
QT_MOC_LITERAL(0, 0, 9), // "mainClass"
QT_MOC_LITERAL(1, 10, 21), // "sigPersonTableUpdated"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 17), // "sigUpdateImageRGB"
QT_MOC_LITERAL(4, 51, 18), // "sigUpdateImageIris"
QT_MOC_LITERAL(5, 70, 19), // "sigUpdateAddIrisImg"
QT_MOC_LITERAL(6, 90, 4), // "left"
QT_MOC_LITERAL(7, 95, 5), // "right"
QT_MOC_LITERAL(8, 101, 20), // "sigUpdateEditIrisImg"
QT_MOC_LITERAL(9, 122, 14), // "msgTextChanged"
QT_MOC_LITERAL(10, 137, 14), // "leftNumChanged"
QT_MOC_LITERAL(11, 152, 15), // "rightNumChanged"
QT_MOC_LITERAL(12, 168, 14), // "cppIdentResult"
QT_MOC_LITERAL(13, 183, 5), // "index"
QT_MOC_LITERAL(14, 189, 7), // "strName"
QT_MOC_LITERAL(15, 197, 5), // "strID"
QT_MOC_LITERAL(16, 203, 15), // "cppEnrollResult"
QT_MOC_LITERAL(17, 219, 6), // "result"
QT_MOC_LITERAL(18, 226, 3), // "str"
QT_MOC_LITERAL(19, 230, 12), // "sigQmlCarNum"
QT_MOC_LITERAL(20, 243, 3), // "hid"
QT_MOC_LITERAL(21, 247, 3), // "pid"
QT_MOC_LITERAL(22, 251, 27), // "slotOnBtnOpenIrisDevClicked"
QT_MOC_LITERAL(23, 279, 21), // "slotUpdateImageov2710"
QT_MOC_LITERAL(24, 301, 26), // "slotOnBtnOpenRGBDevClicked"
QT_MOC_LITERAL(25, 328, 18), // "ov5640imageUpdated"
QT_MOC_LITERAL(26, 347, 3), // "img"
QT_MOC_LITERAL(27, 351, 30), // "slotOnBtnSaveImgIrisDevClicked"
QT_MOC_LITERAL(28, 382, 29), // "slotOnBtnSaveImgRGBDevClicked"
QT_MOC_LITERAL(29, 412, 18), // "savePersonIrisData"
QT_MOC_LITERAL(30, 431, 12), // "DBPersonInfo"
QT_MOC_LITERAL(31, 444, 10), // "personInfo"
QT_MOC_LITERAL(32, 455, 16), // "slotReciveCarNum"
QT_MOC_LITERAL(33, 472, 18), // "saveEnrollIrisData"
QT_MOC_LITERAL(34, 491, 14), // "IKSDKIrisInfo*"
QT_MOC_LITERAL(35, 506, 8), // "enrIrisL"
QT_MOC_LITERAL(36, 515, 7), // "numEnrL"
QT_MOC_LITERAL(37, 523, 8), // "enrIrisR"
QT_MOC_LITERAL(38, 532, 7), // "numEnrR"
QT_MOC_LITERAL(39, 540, 12), // "IKResultFlag"
QT_MOC_LITERAL(40, 553, 6), // "IKflag"
QT_MOC_LITERAL(41, 560, 15), // "showEnrollState"
QT_MOC_LITERAL(42, 576, 5), // "state"
QT_MOC_LITERAL(43, 582, 13), // "showIdenState"
QT_MOC_LITERAL(44, 596, 4), // "flag"
QT_MOC_LITERAL(45, 601, 14), // "getUserIrisImg"
QT_MOC_LITERAL(46, 616, 3), // "uid"
QT_MOC_LITERAL(47, 620, 7), // "msgText"
QT_MOC_LITERAL(48, 628, 7), // "leftNum"
QT_MOC_LITERAL(49, 636, 8), // "rightNum"
QT_MOC_LITERAL(50, 645, 12), // "ableCapImage"
QT_MOC_LITERAL(51, 658, 9), // "identFlag"
QT_MOC_LITERAL(52, 668, 14), // "qmlStartEnroll"
QT_MOC_LITERAL(53, 683, 11), // "irisEnrMode"
QT_MOC_LITERAL(54, 695, 14) // "startSwipeCard"

    },
    "mainClass\0sigPersonTableUpdated\0\0"
    "sigUpdateImageRGB\0sigUpdateImageIris\0"
    "sigUpdateAddIrisImg\0left\0right\0"
    "sigUpdateEditIrisImg\0msgTextChanged\0"
    "leftNumChanged\0rightNumChanged\0"
    "cppIdentResult\0index\0strName\0strID\0"
    "cppEnrollResult\0result\0str\0sigQmlCarNum\0"
    "hid\0pid\0slotOnBtnOpenIrisDevClicked\0"
    "slotUpdateImageov2710\0slotOnBtnOpenRGBDevClicked\0"
    "ov5640imageUpdated\0img\0"
    "slotOnBtnSaveImgIrisDevClicked\0"
    "slotOnBtnSaveImgRGBDevClicked\0"
    "savePersonIrisData\0DBPersonInfo\0"
    "personInfo\0slotReciveCarNum\0"
    "saveEnrollIrisData\0IKSDKIrisInfo*\0"
    "enrIrisL\0numEnrL\0enrIrisR\0numEnrR\0"
    "IKResultFlag\0IKflag\0showEnrollState\0"
    "state\0showIdenState\0flag\0getUserIrisImg\0"
    "uid\0msgText\0leftNum\0rightNum\0ableCapImage\0"
    "identFlag\0qmlStartEnroll\0irisEnrMode\0"
    "startSwipeCard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       8,  200, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x06 /* Public */,
       3,    0,  130,    2, 0x06 /* Public */,
       4,    0,  131,    2, 0x06 /* Public */,
       5,    2,  132,    2, 0x06 /* Public */,
       8,    2,  137,    2, 0x06 /* Public */,
       9,    0,  142,    2, 0x06 /* Public */,
      10,    0,  143,    2, 0x06 /* Public */,
      11,    0,  144,    2, 0x06 /* Public */,
      12,    3,  145,    2, 0x06 /* Public */,
      16,    2,  152,    2, 0x06 /* Public */,
      19,    2,  157,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  162,    2, 0x0a /* Public */,
      23,    0,  163,    2, 0x0a /* Public */,
      24,    0,  164,    2, 0x0a /* Public */,
      25,    1,  165,    2, 0x0a /* Public */,
      27,    0,  168,    2, 0x0a /* Public */,
      28,    0,  169,    2, 0x0a /* Public */,
      29,    1,  170,    2, 0x0a /* Public */,
      32,    2,  173,    2, 0x0a /* Public */,
      33,    5,  178,    2, 0x08 /* Private */,
      41,    1,  189,    2, 0x08 /* Private */,
      43,    2,  192,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      45,    1,  197,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,
    QMetaType::Void, 0x80000000 | 34, QMetaType::Int, 0x80000000 | 34, QMetaType::Int, 0x80000000 | 39,   35,   36,   37,   38,   40,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void, QMetaType::Long, QMetaType::Int,   13,   44,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   46,

 // properties: name, type, flags
      47, QMetaType::QString, 0x00495003,
      48, QMetaType::Int, 0x00495003,
      49, QMetaType::Int, 0x00495003,
      50, QMetaType::Bool, 0x00095103,
      51, QMetaType::Bool, 0x00095103,
      52, QMetaType::Bool, 0x00095103,
      53, QMetaType::Int, 0x00095103,
      54, QMetaType::Bool, 0x00095103,

 // properties: notify_signal_id
       5,
       6,
       7,
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void mainClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainClass *_t = static_cast<mainClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigPersonTableUpdated(); break;
        case 1: _t->sigUpdateImageRGB(); break;
        case 2: _t->sigUpdateImageIris(); break;
        case 3: _t->sigUpdateAddIrisImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sigUpdateEditIrisImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->msgTextChanged(); break;
        case 6: _t->leftNumChanged(); break;
        case 7: _t->rightNumChanged(); break;
        case 8: _t->cppIdentResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: _t->cppEnrollResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->sigQmlCarNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->slotOnBtnOpenIrisDevClicked(); break;
        case 12: _t->slotUpdateImageov2710(); break;
        case 13: _t->slotOnBtnOpenRGBDevClicked(); break;
        case 14: _t->ov5640imageUpdated((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 15: _t->slotOnBtnSaveImgIrisDevClicked(); break;
        case 16: _t->slotOnBtnSaveImgRGBDevClicked(); break;
        case 17: _t->savePersonIrisData((*reinterpret_cast< DBPersonInfo(*)>(_a[1]))); break;
        case 18: _t->slotReciveCarNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->saveEnrollIrisData((*reinterpret_cast< IKSDKIrisInfo*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< IKSDKIrisInfo*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< IKResultFlag(*)>(_a[5]))); break;
        case 20: _t->showEnrollState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->showIdenState((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->getUserIrisImg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigPersonTableUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigUpdateImageRGB)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigUpdateImageIris)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigUpdateAddIrisImg)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigUpdateEditIrisImg)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::msgTextChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::leftNumChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::rightNumChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)(int , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::cppIdentResult)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::cppEnrollResult)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (mainClass::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainClass::sigQmlCarNum)) {
                *result = 10;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        mainClass *_t = static_cast<mainClass *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getmsgText(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getleftNum(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getrightNum(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->ableCapImage(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->identFlag(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->qmlStartEnroll(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->irisEnrMode(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->getStartSwipeCard(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        mainClass *_t = static_cast<mainClass *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setmsgText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setleftNum(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setrightNum(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setAbleCapImage(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setIdentFlag(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setQmlStartEnroll(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setIrisEnrMode(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setStartSwipeCard(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject mainClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mainClass.data,
      qt_meta_data_mainClass,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mainClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainClass::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mainClass.stringdata0))
        return static_cast<void*>(const_cast< mainClass*>(this));
    return QObject::qt_metacast(_clname);
}

int mainClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void mainClass::sigPersonTableUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void mainClass::sigUpdateImageRGB()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void mainClass::sigUpdateImageIris()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void mainClass::sigUpdateAddIrisImg(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void mainClass::sigUpdateEditIrisImg(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void mainClass::msgTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void mainClass::leftNumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void mainClass::rightNumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void mainClass::cppIdentResult(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void mainClass::cppEnrollResult(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void mainClass::sigQmlCarNum(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
