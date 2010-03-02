

#include "GS/libNetwork/NetMsg.h"
#include "GS/libNetwork/NetMsgFactory.h"
#include "GS/libNetwork/GenericOneStringMsg.h"
#include "GS/libNetwork/GenericOneByteMsg.h"
#include "GS/libNetwork/GenericTwoBytesMsg.h"
#include "GS/libNetwork/GenericFourBytesMsg.h"
#include "GS/libNetwork/GenericMultiByteMsg.h"

#include "GS/libNetwork/FailureMsg.h"
#include "GS/libNetwork/SuccessMsg.h"

#include "GS/libNetwork/RemHostNameSetMsg.h"
#include "GS/libNetwork/NewHostOnNetMsg.h"

#include "GS/libNetwork/GeometryReqMsg.h"
#include "GS/libNetwork/GeometryManifestMsg.h"
#include "GS/libNetwork/GeometryChunkMsg.h"

#include "GS/libNetwork/NetPortalManager.h"

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

