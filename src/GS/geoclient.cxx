/*                   G E O C L I E N T . C X X
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
/** @file geoclient.cxx
 *
 * Brief description
 *
 */

#include "GeometryService.h"
#include "libjob.h"
#include "libutility.h"
#include "libevent.h"
#include "libnet.h"

#include <string>
#include <iostream>
#include <stdlib.h>

#include <QtCore/QString>
#include <QtCore/QStringList>

bool stayRun = true;
std::string prompt ="geoclient> ";

void
logInfo(QString s)
{
	Logger::getInstance()->logINFO("geoclient", s);
}

void
logBanner(QString s)
{
	Logger::getInstance()->logBANNER("geoclient", s);
}

/**
 * Prints the 'usage' statement to the console along with an optional message
 */
void
printUsage(std::string customMsg) {
	if (customMsg.length() > 0) {
		customMsg += "\n";
		QString s(customMsg.c_str());
		logInfo(s);
	}
	logInfo("Usage: geoclient\n");

	return;
}

void
handleSendShutdown(QString host, quint16 port, QString uname, QString passwd) {

	/* Log */
	QString s("Trying to connect to ");
	s.append(host);
	s.append(":");
	s.append(QString::number(port));
	logInfo(s);

	PortalManager pm;
	pm.start();
	Portal* p = pm.connectToHost(host, port);
	GSThread::msleep(250);

	if (p == NULL){
		pm.shutdown();
		logInfo("Connection failed.");
		return;
	}

	/* Authenticate */
	/* TODO Make session AUTH */

	NewSessionReqMsg nsrm(uname, passwd);
	p->send(&nsrm);
	GSThread::msleep(1250);

	//Send Shutdown
	TypeOnlyMsg tom(CMD_SHUTDOWN);
	p->sendThenDisconnect(&tom);
	GSThread::msleep(250);
	pm.shutdown();

	delete p;
}


void
processIn(std::string in) {
	QString qin(in.c_str());

	//convert to lowercase
	qin = qin.toLower();

    //split string
	QStringList list = qin.split(" ");

	//check to see if there is at least one element
	if (list.length() <= 0) {
		return;
	}
	QString cmd = list.takeAt(0);

    if (cmd == "exit" || cmd == "quit") {
		stayRun = false;
		return;
	}

    if (cmd == "test01") {
    	processIn("sendshutdown localhost 5309 guest guest");
    	return;
    }

    if (cmd == "test02") {
    	processIn("sendshutdown localhost 5309 g g");
    	return;
    }

    if(cmd == "sendshutdown") {
     	if (list.size() !=4 ) {
     		logInfo("useage: sendshutdown ip port uname passwd");
     		return;
     	}

     	QString host = list.at(0);
     	quint16 port = atoi(list.at(1).toStdString().c_str());
     	QString uname = list.at(2);
     	QString passwd = list.at(3);

    	if (port <=0 || host.length() == 0 || uname.length() == 0 || passwd.length() == 0){
     		logInfo("useage: sendshutdown ip port uname passwd");
    		return;
    	}

    	handleSendShutdown(host, port, uname, passwd);
 		return;
     }

	logInfo("\tunknown command: '" + cmd + "'");
}

/*
 * =====================
 *
 *        Main
 *
 * =====================
 */

int
main(int argc, char* argv[])
{
	Logger::getInstance();
	JobManager::getInstance()->startup();

	logBanner("==================================");
	logBanner("GeometryService Test/Stress Client");
	logBanner("==================================");

	std::string in;
	while (stayRun) {
		in == "";
		std::cout << prompt;
		getline (std::cin, in);

		processIn(in);
	}

	logInfo("Exiting.");
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
