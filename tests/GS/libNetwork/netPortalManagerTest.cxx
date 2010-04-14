#include "libNetwork/NetMsg.h"
#include "libNetwork/NetMsgFactory.h"
#include "libNetwork/GenericOneStringMsg.h"
#include "libNetwork/GenericOneByteMsg.h"
#include "libNetwork/GenericTwoBytesMsg.h"
#include "libNetwork/GenericFourBytesMsg.h"
#include "libNetwork/GenericMultiByteMsg.h"

#include "libNetwork/FailureMsg.h"
#include "libNetwork/SuccessMsg.h"

#include "libNetwork/RemHostNameSetMsg.h"
#include "libNetwork/NewHostOnNetMsg.h"

#include "libNetwork/GeometryReqMsg.h"
#include "libNetwork/GeometryManifestMsg.h"
#include "libNetwork/GeometryChunkMsg.h"

#include "libNetwork/NetPortalManager.h"
#include "libNetwork/FailureMsg.h"

#include "NetPortalManagerTester.h"

#include <QCoreApplication>

/* 
 * =====================
 *
 *        Main
 *
 * =====================
 */

int main(int argc, char* argv[])
{
    //Setup
    QHostAddress netMan01Addy = QHostAddress::LocalHost;
    quint16 netMan01Port = 6000;

    QHostAddress netMan02Addy = QHostAddress::LocalHost;
    quint16 netMan02Port = 7000;

    //Core app
    QCoreApplication coreApp(argc, argv);

    NetPortalManager netMan01("Gomer");
    NetPortalManager netMan02("Kiaser");

    NetPortalManagerTester npmt01(&netMan01);
    NetPortalManagerTester npmt02(&netMan02);

    netMan01.listen(netMan01Addy, netMan01Port);
    netMan02.listen(netMan02Addy, netMan02Port);

    //Connect to netMan02
    NetPortal* np01 = npmt01.getNewPortal();
    NetPortal* np02 = npmt02.getNewPortal();
    np01->connectToHost(netMan02Addy, netMan02Port);

    np01->quickSend(12345677);

    return coreApp.exec();
}

