/****************************************************************************
** Meta object code from reading C++ file 'NetPortalManager.h'
**
** Created: Wed Apr 28 16:12:17 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NetPortalManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetPortalManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetPortalManager[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   17,   17,   17, 0x09,
      88,   81,   17,   17, 0x09,
     133,  122,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_NetPortalManager[] = {
    "NetPortalManager\0\0nsp\0"
    "newIncomingConnection(NetPortal*)\0"
    "handlePortalDisconnect()\0portal\0"
    "mapPortalToGSHostname(NetPortal*)\0"
    "gsHostname\0unmapPortalToGSHostname(QString)\0"
};

const QMetaObject NetPortalManager::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_NetPortalManager,
      qt_meta_data_NetPortalManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetPortalManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetPortalManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetPortalManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetPortalManager))
        return static_cast<void*>(const_cast< NetPortalManager*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int NetPortalManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newIncomingConnection((*reinterpret_cast< NetPortal*(*)>(_a[1]))); break;
        case 1: handlePortalDisconnect(); break;
        case 2: mapPortalToGSHostname((*reinterpret_cast< NetPortal*(*)>(_a[1]))); break;
        case 3: unmapPortalToGSHostname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NetPortalManager::newIncomingConnection(NetPortal * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
