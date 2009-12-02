/*            N E T S O C K P O R T A L M A N A G E R T E S T . C X X
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file netSockPortalManagerTest.cxx
 *
 * Brief description
 *
 */

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

#include "GS/NetSockPortalManager.h"

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

	NetSockPortalManager netMan01("Gomer");
	NetSockPortalManager netMan02("Kiaser");

	quint16 netMan01Port = 6000;
	quint16 netMan02Port = 7000;

	netMan01.listen(QHostAddress::LocalHost, netMan01Port);
	netMan02.listen(QHostAddress::LocalHost, netMan02Port);

	//Connect to netMan02
	NetSockPortal* nsp01 = netMan01.connectTo(QHostAddress::LocalHost, netMan02Port);

	return coreApp.exec();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
