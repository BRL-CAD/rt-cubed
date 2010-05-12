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
#include "libjob.h"

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
    logBanner("Testing " + typeName);

    NetMsgFactory factory;

    QByteArray* networkSim = new QByteArray();
    msg01->serialize(networkSim);

    factory.addData(*networkSim);

    delete networkSim;

    NetMsg* msg02 = factory.makeMsg();

    bool pass = (msg02 != NULL) && (*msg01 == *msg02);

    if (pass) {
	logInfo("Overall: PASSED");
    } else {
	logInfo("Overall: FAILED");
    }

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
  

  Logger::getInstance();

  TypeOnlyMsg msg01(DISCONNECTREQ);
  testMsg(&msg01, "TypeOnlyMsg");

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
