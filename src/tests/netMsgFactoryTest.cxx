/*            N E T M S G F A C T O R Y T E S T . C X X
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
/** @file netMsgFactoryTest.cxx
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

void testEquals(NetMsg* msg01, NetMsg* msg02, bool desiredResult, bool showInfo)
{

	if (msg01->equals(*msg02) == desiredResult)
	{
		std::cout << "\tPASSED.\n";
	}
	else
	{
		std::cout << "\tFAILED.\n";
		showInfo = true;
	}

	if (showInfo)
	{
		std::cout << "\tmsg01: " << msg01->toStdString() << "\n";
		std::cout << "\tmsg02: " << msg02->toStdString() << "\n";
		std::cout << "\n";
	}
}

bool testFactoryCommon(NetMsgFactory* factory, QByteArray& data)
{
	if (!factory->addData(data))
	{
		std::cout << "Factory failure: addData()\n";
		return false;
	}

	factory->attemptToMakeMsgs();

	if (!factory->hasMsgsAvailable())
	{
		std::cout << "Factory failure: hasMsgsAvailable()\n";
		return false;
	}
	return true;
}

void testNetMsg(NetMsgFactory* factory)
{
	std::cout << "NetMsg: \t";

	QByteArray networkSim;
	NetMsg m1(150);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	NetMsg* m2 = (NetMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGenericOneStringMsg(NetMsgFactory* factory, QString str)
{
	std::cout << "GenericOneStringMsg: ";

	QByteArray networkSim;
	GenericOneStringMsg m1(100, str);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GenericOneStringMsg* m2 = (GenericOneStringMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGenericOneByteMsg(NetMsgFactory* factory)
{
	std::cout << "GenericOneByteMsg: ";

	QByteArray networkSim;
	GenericOneByteMsg m1(0, 123);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GenericOneByteMsg* m2 = (GenericOneByteMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGenericTwoBytesMsg(NetMsgFactory* factory)
{
	std::cout << "GenericTwoBytesMsg: ";

	QByteArray networkSim;
	GenericTwoBytesMsg m1(0, 12300);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GenericTwoBytesMsg* m2 = (GenericTwoBytesMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}
void testGenericFourBytesMsg(NetMsgFactory* factory)
{
	std::cout << "GenericFourBytesMsg: ";

	QByteArray networkSim;
	GenericFourBytesMsg m1(0, 987654321);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GenericFourBytesMsg* m2 = (GenericFourBytesMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}

void testGenericMultiByteMsg(NetMsgFactory* factory)
{
	std::cout << "GenericMultiByteMsg: ";

	char data[] =
	{ 12, 34, 56, 78, 90, 98, 76, 65, 54, 43, 32, 10 };

	QByteArray networkSim;
	GenericMultiByteMsg m1(0, data, 12);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GenericMultiByteMsg* m2 = (GenericMultiByteMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}

void testFailureMsg(NetMsgFactory* factory)
{
	std::cout << "FailureMsg: \t";

	QByteArray networkSim;
	FailureMsg m1(123);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	FailureMsg* m2 = (FailureMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testSuccessMsg(NetMsgFactory* factory)
{
	std::cout << "SuccessMsg: \t";

	QByteArray networkSim;
	SuccessMsg m1(123);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	SuccessMsg* m2 = (SuccessMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}

void testRemHostNameSetMsg(NetMsgFactory* factory)
{
	std::cout << "RemHostNameSetMsg Test:";

	QByteArray networkSim;
	RemHostNameSetMsg m1("Gomer Pyle");
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	RemHostNameSetMsg* m2 = (RemHostNameSetMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}

void testNewHostOnNetMsg(NetMsgFactory* factory)
{
	std::cout << "NewHostOnNetMsg: ";

	QByteArray networkSim;
	NewHostOnNetMsg m1("Gomer Pyle");
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	NewHostOnNetMsg* m2 = (NewHostOnNetMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGeometryReqMsg(NetMsgFactory* factory, QString uuid01)
{
	std::cout << "GeometryReqMsg: ";

	QByteArray networkSim;
	GeometryReqMsg m1(ReqByUUID, uuid01);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GeometryReqMsg* m2 = (GeometryReqMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGeometryChunkMsg(NetMsgFactory* factory)
{
	std::cout << "GeometryChunkMsg: ";

	char data[] =
	{ 12, 34, 56, 78, 90, 98, 76, 65, 54, 43, 32, 10 };

	QByteArray networkSim;
	GeometryChunkMsg m1(data, 12);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GeometryChunkMsg* m2 = (GeometryChunkMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;
}

void testGeometryManifestMsg(NetMsgFactory* factory, QList<QString>* items)
{
	std::cout << "GeometryManifestMsg: ";

	QByteArray networkSim;
	GeometryManifestMsg m1(*items);
	m1.serialize(&networkSim);

	if (!testFactoryCommon(factory, networkSim))
		return;

	GeometryManifestMsg* m2 = (GeometryManifestMsg*) factory->getNextMsg();
	testEquals(&m1, m2, true, false);
	delete m2;

}

//TODO make the intentional Diff failing fn calls work.

/* 
 * =====================
 *
 *        Main
 *
 * =====================
 */

int main(int argc, char* argv[])
{
	//Setup common values to use
	QString uuid01("{60a03846-c39b-42e6-865f-394056a4fa04}");
	QString uuid02("{90645abd-3109-4538-a425-07810542cc2d}");
	QString uuid03("{732986e8-5ef9-4329-b457-bc83df959e1f}");
	QString uuid04("{84d05702-41c4-449d-947b-3c18a8f93cd9}");
	QString uuid05("{b2dd5d49-1654-49f4-83b2-512b9e2fc4dc}");
	QString uuid06("{ada2005b-02e1-4431-b7e8-432def490632}");

	QList<QString>* items = new QList<QString> ();
	items->push_back(uuid01);
	items->push_back(uuid02);
	items->push_back(uuid03);
	items->push_back(uuid04);
	items->push_back(uuid05);
	items->push_back(uuid06);

	NetMsgFactory* factory = new NetMsgFactory();

	std::cout << "\n\n";

	testNetMsg(factory);
	testGenericOneStringMsg(factory, uuid02);
	testGenericOneByteMsg(factory);
	//	testGenericTwoBytesMsg();
	//	testGenericFourBytesMsg();
	//	testGenericMultiByteMsg();

	testFailureMsg(factory);
	testSuccessMsg(factory);

	testRemHostNameSetMsg(factory);

	testNewHostOnNetMsg(factory);

	testGeometryReqMsg(factory, uuid03);
	testGeometryChunkMsg(factory);

	testGeometryManifestMsg(factory, items);

	/*
	 *
	 */
	std::cout << "\n\nMultipleMsgTest: \n\n";

	QByteArray networkSim;

	GeometryReqMsg m1(ReqByUUID, uuid01);
	m1.serialize(&networkSim);

	GeometryManifestMsg m2(*items);
	m2.serialize(&networkSim);
	m2.serialize(&networkSim);

	char data[] =
	{ 12, 34, 56, 78, 90, 98, 76, 65, 54, 43, 32, 10 };
	GeometryChunkMsg m3(data, 12);
	m3.serialize(&networkSim);
	m3.serialize(&networkSim);
	m3.serialize(&networkSim);

	factory->addData(networkSim);

	//Make msgs.
	factory->attemptToMakeMsgs();


	//print the messages
	while (factory->hasMsgsAvailable())
	{
		NetMsg* msg = factory->getNextMsg();
		std::cout << "MsgType: " << msg->getMsgType() << "\n";
	}

	/*
	 *
	 */
	delete items;
	delete factory;
	return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
