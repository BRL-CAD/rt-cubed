/*            N E T M S G S E R I A L T E S T . C X X
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file netMsgSerialTest.cxx
 *
 * Brief description
 *
 */

#include "libNetwork/NetMsg.h"
#include "libNetwork/GenericOneStringMsg.h"
#include "libNetwork/GenericOneByteMsg.h"
#include "libNetwork/GenericTwoBytesMsg.h"
#include "libNetwork/GenericFourBytesMsg.h"
#include "libNetwork/GenericMultiByteMsg.h"

#include "libNetwork/FailureMsg.h"
#include "libNetwork/SuccessMsg.h"

#include "libNetwork/RemoteGSHostnameSetMsg.h"
#include "libNetwork/NewHostOnNetMsg.h"

#include "libNetwork/GeometryReqMsg.h"
#include "libNetwork/GeometryManifestMsg.h"
#include "libNetwork/GeometryChunkMsg.h"

void
testEquals(NetMsg* msg01, NetMsg* msg02, bool desiredResult,  bool showInfo)
{

  if (msg01->equals(*msg02) == desiredResult) {
      std::cout << "\tPASSED.\n";
  } else {
      std::cout << "\tFAILED.\n";
      showInfo = true;
  }

  if (showInfo) {
      std::cout << "\tmsg01: " << msg01->toStdString() << "\n";
      std::cout << "\tmsg02: " << msg02->toStdString() << "\n";
      std::cout << "\n";
  }
}



void
testStringSerialDeserial(QString in)
{
  std::cout << "Basic String Serial/Deserial Test: ";

  QByteArray ba;
  QDataStream* dsw = new QDataStream(&ba, QIODevice::WriteOnly);

  Utils::putString(dsw, in);

  // Utils::printQByteArray(&ba);

  QDataStream* dsr = new QDataStream(&ba, QIODevice::ReadOnly);
  QString* out = Utils::getString(dsr);

  delete dsw;
  delete dsr;

  if (in == out) {
      std::cout << "\tPASSED.\n\n";
  } else {
      std::cout << "\tFAILED.\n";
      std::cout << "in: " << in.toStdString() << "\n";
      std::cout << "out: " << out->toStdString() << "\n";
      std::cout << "\n";
  }
}

void
testNetMsg()
{
  std::cout << "NetMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  NetMsg* m1 = new NetMsg(1200340056);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  NetMsg* m2 = new NetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";
  NetMsg* m3 = new NetMsg(8675309, m2);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  NetMsg* m4 = new NetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3,m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testGenericOneStringMsg(QString str)
{
  std::cout << "GenericOneStringMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GenericOneStringMsg* m1 = new GenericOneStringMsg(1200340056, str);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericOneStringMsg* m2 = new GenericOneStringMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";
  GenericOneStringMsg* m3 = new GenericOneStringMsg(8675309, m2, str);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericOneStringMsg* m4 = new GenericOneStringMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3,m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testGenericOneByteMsg()
{
  std::cout << "GenericOneByteMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GenericOneByteMsg* m1 = new GenericOneByteMsg(1200340056, 123);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericOneByteMsg* m2 = new GenericOneByteMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GenericOneByteMsg* m3 = new GenericOneByteMsg(1200340056, m2, 123);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericOneByteMsg* m4 = new GenericOneByteMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testGenericTwoBytesMsg()
{
  std::cout << "GenericTwoBytesMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GenericTwoBytesMsg* m1 = new GenericTwoBytesMsg(1200340056, 12345);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericTwoBytesMsg* m2 = new GenericTwoBytesMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GenericTwoBytesMsg* m3 = new GenericTwoBytesMsg(1200340056, m2, 12345);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericTwoBytesMsg* m4 = new GenericTwoBytesMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testGenericFourBytesMsg()
{
  std::cout << "GenericFourBytesMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GenericFourBytesMsg* m1 = new GenericFourBytesMsg(1200340056, 987654321);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericFourBytesMsg* m2 = new GenericFourBytesMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GenericFourBytesMsg* m3 = new GenericFourBytesMsg(1200340056, m2, 987654321);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericFourBytesMsg* m4 = new GenericFourBytesMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}


void
testGenericMultiByteMsg()
{
  std::cout << "GenericMultiByteMsg:\n";

  char data[] = {12,34,56,78,90,98,76,65,54,43,32,10};

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GenericMultiByteMsg* m1 = new GenericMultiByteMsg(1200340056, data, 12);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericMultiByteMsg* m2 = new GenericMultiByteMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GenericMultiByteMsg* m3 = new GenericMultiByteMsg(1200340056, m2, data, 12);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GenericMultiByteMsg* m4 = new GenericMultiByteMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testFailureMsg()
{
  std::cout << "FailureMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  FailureMsg* m1 = new FailureMsg(123);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  FailureMsg* m2 = new FailureMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  FailureMsg* m3 = new FailureMsg(m2, 123);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  FailureMsg* m4 = new FailureMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testSuccessMsg()
{
  std::cout << "SuccessMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  SuccessMsg* m1 = new SuccessMsg(123);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  SuccessMsg* m2 = new SuccessMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  SuccessMsg* m3 = new SuccessMsg(m2, 123);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  SuccessMsg* m4 = new SuccessMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testRemoteHostnameSetMsg()
{
  std::cout << "RemoteGSHostnameSetMsg Test:\n";
  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  RemoteGSHostnameSetMsg* m1 = new RemoteGSHostnameSetMsg("Gomer Pyle");
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  RemoteGSHostnameSetMsg* m2 = new RemoteGSHostnameSetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID):\t";

  RemoteGSHostnameSetMsg* m3 = new RemoteGSHostnameSetMsg(m2, "Kiaser Sose");
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  RemoteGSHostnameSetMsg* m4 = new RemoteGSHostnameSetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testNewHostOnNetMsg()
{
  std::cout << "NewHostOnNetMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  NewHostOnNetMsg* m1 = new NewHostOnNetMsg("Gomer Pyle");
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  NewHostOnNetMsg* m2 = new NewHostOnNetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID):\t";

  NewHostOnNetMsg* m3 = new NewHostOnNetMsg(m2, "Kiaser Sose");
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  NewHostOnNetMsg* m4 = new NewHostOnNetMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);


  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}

void
testGeometryReqMsg(QString uuid01, QString uuid02)
{
  std::cout << "GeometryReqMsg:\n";

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GeometryReqMsg* m1 = new GeometryReqMsg(ReqByUUID, uuid01);
  m1->serialize(networkSim);

  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryReqMsg* m2 = new GeometryReqMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID):\t";

  GeometryReqMsg* m3 = new GeometryReqMsg(m2, ReqByUUID, uuid02);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryReqMsg* m4 = new GeometryReqMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);


  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}


void
testGeometryChunkMsg()
{
  std::cout << "GeometryChunkMsg:\n";

  char data[] = {12,34,56,78,90,98,76,65,54,43,32,10};

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GeometryChunkMsg* m1 = new GeometryChunkMsg(data, 12);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryChunkMsg* m2 = new GeometryChunkMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GeometryChunkMsg* m3 = new GeometryChunkMsg( m2, data, 12);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryChunkMsg* m4 = new GeometryChunkMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
      std::cout << "\n";
}



void
testGeometryManifestMsg(QList<QString>* items)
{
  std::cout << "GeometryManifestMsg:\n";

  QList<QString> items01;
  items01.append(*items);
  //items01.append(*items);

  QList<QString> items02;
  items02.append(*items);

  QDataStream* qds;
  QByteArray* networkSim = new QByteArray();
  std::cout << "\t Equality (without RegardingUUID): ";

  GeometryManifestMsg* m1 = new GeometryManifestMsg(items01);
  m1->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryManifestMsg* m2 = new GeometryManifestMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m1, m2, true, false);
  networkSim->clear();

  std::cout << "\t Equality (with RegardingUUID): ";

  GeometryManifestMsg* m3 = new GeometryManifestMsg( m2, items02);
  m3->serialize(networkSim);
  qds = new QDataStream(networkSim, QIODevice::ReadOnly);
  GeometryManifestMsg* m4 = new GeometryManifestMsg(qds, "TestOrigin");
  delete qds;

  testEquals(m3, m4, true, false);

  std::cout << "\t Diff Fail Test:\t\t";
  testEquals(m1, m1, true, false);

  std::cout << "\t Diff Succeed Test:\t\t";
  testEquals(m1, m3, false, false);

  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete networkSim;
   
std::cout << "\n";
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

  QList<QString>* items = new QList<QString>();
  items->push_back(uuid01);
  items->push_back(uuid02);
  items->push_back(uuid03);
  items->push_back(uuid04);
  items->push_back(uuid05);
  items->push_back(uuid06);


  std::cout << "\n\n";
  
  testStringSerialDeserial(uuid01);
  testNetMsg();
  testGenericOneStringMsg(uuid02);

  testGenericOneByteMsg();
  testGenericTwoBytesMsg();
  testGenericFourBytesMsg();
  testGenericMultiByteMsg();

  testFailureMsg();
  testSuccessMsg();
 
  testRemoteHostnameSetMsg();

  testNewHostOnNetMsg();

  testGeometryReqMsg(uuid03, uuid04);
  testGeometryChunkMsg();
  

  testGeometryManifestMsg(items);


  std::cout << "\n\n";

  delete items;

  return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
