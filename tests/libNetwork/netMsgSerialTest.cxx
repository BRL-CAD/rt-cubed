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

#include "libnetwork.h"
#include "libutility.h"

#include <string>

#include <QDataStream>
#include <QString>

void
logInfo(QString s) {
    Logger::getInstance()->logINFO("NetMsgSerialTest",s);
}
void
logBanner(QString s) {
    Logger::getInstance()->logBANNER("NetMsgSerialTest",s);
}

void testMsg(NetMsg* msg01, QString typeName)
{
    NetMsgFactory factory;

    QByteArray* networkSim = new QByteArray();
    msg01->serialize(networkSim);

    factory.addData(*networkSim);

    delete networkSim;

    NetMsg* msg02 = factory.makeMsg();

    bool pass = (msg02 != NULL) && (*msg01 == *msg02);

    if (pass) {
	logInfo(typeName + ": PASSED");
    } else {
	logInfo(typeName + ": FAILED");
	logInfo("\tMsg01: " + msg01->toString());
	logInfo("\tMsg02: " + msg02->toString());
    }
    delete msg02;
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
  QString strUUID01("{60a03846-c39b-42e6-865f-394056a4fa04}");
  QString strUUID02("{90645abd-3109-4538-a425-07810542cc2d}");
  QString strUUID03("{732986e8-5ef9-4329-b457-bc83df959e1f}");
  QString strUUID04("{84d05702-41c4-449d-947b-3c18a8f93cd9}");
  QString strUUID05("{b2dd5d49-1654-49f4-83b2-512b9e2fc4dc}");
  QString strUUID06("{ada2005b-02e1-4431-b7e8-432def490632}");

  QList<QString>* items = new QList<QString>();
  items->push_back(strUUID01);
  items->push_back(strUUID02);
  items->push_back(strUUID03);
  items->push_back(strUUID04);
  items->push_back(strUUID05);
  items->push_back(strUUID06);

  Logger::getInstance();

  /* Test Normal */
  TypeOnlyMsg msg001(DISCONNECTREQ);
  testMsg(&msg001, "TypeOnlyMsg-Normal");
  /* Test Reply */
  TypeOnlyMsg msg002(DISCONNECTREQ, &msg001);
  testMsg(&msg002, "TypeOnlyMsg-Reply");


  /* Test Normal */
  GenericFourBytesMsg msg011(TEST_GENERIC_4BYTE_MSG, 8675309);
  testMsg(&msg011, "GenericFourBytesMsg-Normal");
  /* Test Reply */
  GenericFourBytesMsg msg012(TEST_GENERIC_4BYTE_MSG, &msg011, 8675309);
  testMsg(&msg012, "GenericFourBytesMsg-Reply");


  /* Test Normal */
  GenericTwoBytesMsg msg031(TEST_GENERIC_2BYTE_MSG, 5309);
  testMsg(&msg031, "GenericTwoBytesMsg-Normal");
  /* Test Reply */
  GenericTwoBytesMsg msg032(TEST_GENERIC_2BYTE_MSG, &msg031, 5309);
  testMsg(&msg032, "GenericTwoBytesMsg-Reply");


  /* Test Normal */
  GenericOneByteMsg msg041(TEST_GENERIC_1BYTE_MSG, 42);
  testMsg(&msg041, "GenericOneByteMsg-Normal");
  /* Test Reply */
  GenericOneByteMsg msg042(TEST_GENERIC_1BYTE_MSG, &msg041, 42);
  testMsg(&msg042, "GenericOneByteMsg-Reply");


  std::string s05 = strUUID01.toStdString();
  char* data05 = (char*) s05.c_str();

  /* Test Normal */
  GenericMultiByteMsg msg051(TEST_GENERIC_MULTIBYTE_MSG, data05, s05.length());
  testMsg(&msg051, "GenericMultiByteMsg-Normal");
  /* Test Reply */
  GenericMultiByteMsg msg052(TEST_GENERIC_MULTIBYTE_MSG, &msg051, data05, s05.length());
  testMsg(&msg052, "GenericMultiByteMsg-Reply");


  /* Test Normal */
  GenericOneStringMsg msg061(TEST_GENERIC_1STRING_MSG, strUUID01);
  testMsg(&msg061, "GenericOneStringMsg-Normal");
  /* Test Reply */
  GenericOneStringMsg msg062(TEST_GENERIC_1STRING_MSG, &msg061, strUUID01);
  testMsg(&msg062, "GenericOneStringMsg-Reply");


  /* Test Normal */
  FailureMsg msg071(42);
  testMsg(&msg071, "FailureMsg-Normal");
  /* Test Reply */
  FailureMsg msg072(&msg071, 42);
  testMsg(&msg072, "FailureMsg-Reply");


  /* Test Normal */
  SuccessMsg msg081(42);
  testMsg(&msg081, "SuccessMsg-Normal");
  /* Test Reply */
  SuccessMsg msg082(&msg081, 42);
  testMsg(&msg082, "SuccessMsg-Reply");


  std::string s09 = strUUID02.toStdString();
  char* data09 = (char*) s09.c_str();

  /* Test Normal */
  GeometryChunkMsg msg091(data09, s09.length());
  testMsg(&msg091, "GeometryChunkMsg-Normal");
  /* Test Reply */
  GeometryChunkMsg msg092(&msg091, data09, s09.length());
  testMsg(&msg092, "GeometryChunkMsg-Reply");


  /* Test Normal */
  GeometryManifestMsg msg101(*items);
  testMsg(&msg101, "GeometryManifestMsg-Normal");
  /* Test Reply */
  GeometryManifestMsg msg102(&msg101, *items);
  testMsg(&msg102, "GeometryManifestMsg-Reply");


  /* Test Normal */
  GeometryReqMsg msg111(ReqByFilePath, "/path/to/a/geometry/resource");
  testMsg(&msg111, "GeometryReqMsg-Normal");
  /* Test Reply */
  GeometryReqMsg msg112(&msg111, ReqByFilePath, "/path/to/a/geometry/resource");
  testMsg(&msg112, "GeometryReqMsg-Reply");


  /* Test Normal */
  NewHostOnNetMsg msg121("Kiaser Sose");
  testMsg(&msg121, "NewHostOnNetMsg-Normal");
  /* Test Reply */
  NewHostOnNetMsg msg122(&msg121, "Kiaser Sose");
  testMsg(&msg122, "NewHostOnNetMsg-Reply");


  /* Test Normal */
  NewSessionReqMsg msg131("Kiaser Sose", "YourMom");
  testMsg(&msg131, "NewSessionReqMsg-Normal");
  /* Test Reply */
  NewSessionReqMsg msg132(&msg131, "Kiaser Sose", "YourMom");
  testMsg(&msg132, "NewSessionReqMsg-Reply");


  /* Test Normal */
  RemoteGSHostnameSetMsg msg141("RogerRamJet");
  testMsg(&msg141, "RemoteGSHostnameSetMsg-Normal");
  /* Test Reply */
  RemoteGSHostnameSetMsg msg142(&msg141, "RogerRamJet");
  testMsg(&msg142, "RemoteGSHostnameSetMsg-Reply");

  QUuid uuid = QUuid::createUuid();

  /* Test Normal */
  SessionInfoMsg msg151(uuid);
  testMsg(&msg151, "SessionInfoMsg-Normal");
  /* Test Reply */
  SessionInfoMsg msg152(&msg151, uuid);
  testMsg(&msg152, "SessionInfoMsg-Reply");


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
