/*        N E T P O R T A L M A N A G E R T E S T . C X X
 * BRLCAD
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
/** @file netPortalManagerTest.cxx
 *
 * Brief description
 *
 */

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
    np01->connectToNetHost(netMan02Addy, netMan02Port);

    np01->quickSend(12345677);

    return coreApp.exec();
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
