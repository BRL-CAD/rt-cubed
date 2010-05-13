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

#include "libnetwork.h"
#include "libutility.h"
#include "PrintingMsgHandler.h"

#include <QCoreApplication>
#include <QHostAddress>


/* 
 * =====================
 *
 *        Main
 *
 * =====================
 */



int main(int argc, char* argv[])
{
    Logger* log = Logger::getInstance();

    log->logBANNER("GatewayTest","GatewayTest");

    //Setup
    QHostAddress serverAddy = QHostAddress::LocalHost;
    quint16 serverPort = 6000;

    QHostAddress clientAddy = QHostAddress::LocalHost;
    quint16 clientPort = 7000;

    PrintingMsgHandler serverMsgHandler("ServerHandler");
    Gateway serverGate("ImaServer", &serverMsgHandler);

    PrintingMsgHandler clientMsgHandler("ClientHandler");
    Gateway clientGate("ImaClient", &clientMsgHandler);

    //Startup the server
    serverGate.start();
    serverGate.listen(serverAddy, serverPort);

    ThreadUtils::sleep(2);


    clientGate.stop();
    serverGate.stopListening();

    return 0;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
