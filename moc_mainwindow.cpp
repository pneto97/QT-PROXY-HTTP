/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "sendRequestAndReply"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "sendUrlAndDepth"
QT_MOC_LITERAL(4, 48, 12), // "unlockSpider"
QT_MOC_LITERAL(5, 61, 24), // "on_actionproxy_triggered"
QT_MOC_LITERAL(6, 86, 25), // "on_actionspider_triggered"
QT_MOC_LITERAL(7, 112, 23), // "on_actiondump_triggered"
QT_MOC_LITERAL(8, 136, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(9, 158, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(10, 182, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(11, 206, 15), // "on_textReceived"
QT_MOC_LITERAL(12, 222, 18), // "on_requestReceived"
QT_MOC_LITERAL(13, 241, 14), // "on_requestSent"
QT_MOC_LITERAL(14, 256, 16), // "on_replyReceived"
QT_MOC_LITERAL(15, 273, 17), // "on_replyRetrieved"
QT_MOC_LITERAL(16, 291, 13) // "on_nodeSpider"

    },
    "MainWindow\0sendRequestAndReply\0\0"
    "sendUrlAndDepth\0unlockSpider\0"
    "on_actionproxy_triggered\0"
    "on_actionspider_triggered\0"
    "on_actiondump_triggered\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_textReceived\0on_requestReceived\0"
    "on_requestSent\0on_replyReceived\0"
    "on_replyRetrieved\0on_nodeSpider"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,
       3,    2,   94,    2, 0x06 /* Public */,
       4,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  100,    2, 0x08 /* Private */,
       6,    0,  101,    2, 0x08 /* Private */,
       7,    0,  102,    2, 0x08 /* Private */,
       8,    0,  103,    2, 0x08 /* Private */,
       9,    0,  104,    2, 0x08 /* Private */,
      10,    0,  105,    2, 0x08 /* Private */,
      11,    1,  106,    2, 0x0a /* Public */,
      12,    1,  109,    2, 0x0a /* Public */,
      13,    0,  112,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendRequestAndReply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sendUrlAndDepth((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->unlockSpider(); break;
        case 3: _t->on_actionproxy_triggered(); break;
        case 4: _t->on_actionspider_triggered(); break;
        case 5: _t->on_actiondump_triggered(); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_pushButton_3_clicked(); break;
        case 9: _t->on_textReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_requestReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_requestSent(); break;
        case 12: _t->on_replyReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->on_replyRetrieved(); break;
        case 14: _t->on_nodeSpider((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendRequestAndReply)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendUrlAndDepth)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::unlockSpider)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendRequestAndReply(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendUrlAndDepth(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::unlockSpider()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
