

#include "GS/netMsg/NetMsg.h"
#include "GS/netMsg/NetMsgFactory.h"
#include "GS/netMsg/GenericOneStringMsg.h"
#include "GS/netMsg/GenericOneByteMsg.h"
#include "GS/netMsg/GenericTwoBytesMsg.h"
#include "GS/netMsg/GenericFourBytesMsg.h"
#include "GS/netMsg/GenericMultiByteMsg.h"

#include "GS/netMsg/FailureMsg.h"
#include "GS/netMsg/SuccessMsg.h"

#include "GS/netMsg/RemHostNameSetMsg.h"
#include "GS/netMsg/NewHostOnNetMsg.h"

#include "GS/netMsg/GeometryReqMsg.h"
#include "GS/netMsg/GeometryManifestMsg.h"
#include "GS/netMsg/GeometryChunkMsg.h"

#include "GS/NetPortalManager.h"

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
	QCoreApplication coreApp(argc, argv);

	NetPortalManager netMan01("Gomer");
	NetPortalManager netMan02("Kiaser");

	quint16 netMan01Port = 6000;
	quint16 netMan02Port = 7000;

	netMan01.listen(QHostAddress::LocalHost, netMan01Port);
	netMan02.listen(QHostAddress::LocalHost, netMan02Port);

	//Connect to netMan02
	NetPortal* nsp01 = netMan01.connectTo(QHostAddress::LocalHost, netMan02Port);

	return coreApp.exec();
}

