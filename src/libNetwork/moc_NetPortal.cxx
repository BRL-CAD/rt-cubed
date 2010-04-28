/****************************************************************************
** Meta object code from reading C++ file 'NetPortal.h'
**
** Created: Wed Apr 28 16:12:17 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NetPortal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetPortal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetPortal[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      34,   22,   10,   10, 0x05,
      80,   73,   10,   10, 0x05,
     116,   10,   10,   10, 0x05,
     134,   10,   10,   10, 0x05,
     159,  155,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     201,   10,   10,   10, 0x0a,
     237,   10,   10,   10, 0x09,
     264,   10,   10,   10, 0x09,
     285,   10,   10,   10, 0x09,
     309,  155,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_NetPortal[] = {
    "NetPortal\0\0msgReady()\0current,old\0"
    "handshakeStatusUpdate(quint32,quint32)\0"
    "portal\0portalHandshakeComplete(NetPortal*)\0"
    "portalConnected()\0portalDisconnected()\0"
    "err\0socketError(QAbstractSocket::SocketError)\0"
    "sendLocalGSHostnameToRemoteGSHost()\0"
    "moveDataFromSocketBuffer()\0"
    "relaySockConnected()\0relaySockDisconnected()\0"
    "relaySockError(QAbstractSocket::SocketError)\0"
};

const QMetaObject NetPortal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetPortal,
      qt_meta_data_NetPortal, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetPortal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetPortal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetPortal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetPortal))
        return static_cast<void*>(const_cast< NetPortal*>(this));
    return QObject::qt_metacast(_clname);
}

int NetPortal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgReady(); break;
        case 1: handshakeStatusUpdate((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 2: portalHandshakeComplete((*reinterpret_cast< NetPortal*(*)>(_a[1]))); break;
        case 3: portalConnected(); break;
        case 4: portalDisconnected(); break;
        case 5: socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: sendLocalGSHostnameToRemoteGSHost(); break;
        case 7: moveDataFromSocketBuffer(); break;
        case 8: relaySockConnected(); break;
        case 9: relaySockDisconnected(); break;
        case 10: relaySockError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void NetPortal::msgReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NetPortal::handshakeStatusUpdate(quint32 _t1, quint32 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetPortal::portalHandshakeComplete(NetPortal * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetPortal::portalConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void NetPortal::portalDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void NetPortal::socketError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
