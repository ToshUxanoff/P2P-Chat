/****************************************************************************
** Meta object code from reading C++ file 'clientwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/clientwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientWindow_t {
    QByteArrayData data[19];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientWindow_t qt_meta_stringdata_ClientWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientWindow"
QT_MOC_LITERAL(1, 13, 27), // "on_SearchLine_returnPressed"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 12), // "ConnDetector"
QT_MOC_LITERAL(4, 55, 8), // "Resolver"
QT_MOC_LITERAL(5, 64, 4), // "Data"
QT_MOC_LITERAL(6, 69, 13), // "ConnectToPeer"
QT_MOC_LITERAL(7, 83, 2), // "IP"
QT_MOC_LITERAL(8, 86, 4), // "Port"
QT_MOC_LITERAL(9, 91, 8), // "UserName"
QT_MOC_LITERAL(10, 100, 6), // "onRead"
QT_MOC_LITERAL(11, 107, 26), // "on_NameInput_returnPressed"
QT_MOC_LITERAL(12, 134, 17), // "SendMessageToPeer"
QT_MOC_LITERAL(13, 152, 8), // "PeerName"
QT_MOC_LITERAL(14, 161, 18), // "on_SendMsg_clicked"
QT_MOC_LITERAL(15, 180, 31), // "on_FriendList_itemDoubleClicked"
QT_MOC_LITERAL(16, 212, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 229, 4), // "item"
QT_MOC_LITERAL(18, 234, 25) // "on_MsgInput_returnPressed"

    },
    "ClientWindow\0on_SearchLine_returnPressed\0"
    "\0ConnDetector\0Resolver\0Data\0ConnectToPeer\0"
    "IP\0Port\0UserName\0onRead\0"
    "on_NameInput_returnPressed\0SendMessageToPeer\0"
    "PeerName\0on_SendMsg_clicked\0"
    "on_FriendList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_MsgInput_returnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    3,   69,    2, 0x08 /* Private */,
      10,    0,   76,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    1,   78,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,
      15,    1,   82,    2, 0x08 /* Private */,
      18,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,

       0        // eod
};

void ClientWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientWindow *_t = static_cast<ClientWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_SearchLine_returnPressed(); break;
        case 1: _t->ConnDetector(); break;
        case 2: { int _r = _t->Resolver((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->ConnectToPeer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->onRead(); break;
        case 5: _t->on_NameInput_returnPressed(); break;
        case 6: _t->SendMessageToPeer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_SendMsg_clicked(); break;
        case 8: _t->on_FriendList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->on_MsgInput_returnPressed(); break;
        default: ;
        }
    }
}

const QMetaObject ClientWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ClientWindow.data,
      qt_meta_data_ClientWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ClientWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
