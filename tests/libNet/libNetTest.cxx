/*                  L I B N E T T E S T . C X X
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
/** @file libNetTest.cxx
 *
 * Brief description
 *
 */

#include "brlcad/bu.h"
#include "libnet.h"
#include "libjob.h"
#include "libutility.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <QtCore/QDataStream>
#include <QtCore/QString>

void logInfo(QString s) {
	Logger::getInstance()->logINFO("libNetTest", s);
}
void logBanner(QString s) {
	Logger::getInstance()->logBANNER("libNetTest", s);
}

/**
 * Prints the 'usage' statement to the console along with an optional message
 */
void printUsage(std::string customMsg) {
	if (customMsg.length() > 0) {
		customMsg += "\n";
		QString s(customMsg.c_str());
		logInfo(s);
	}
	logInfo("Usage for Client: pkgcppTest client ipAddress port.\n");
	logInfo("Usage for Server: pkgcppTest server port.\n");

	return;
}

/**
 * Converts char* data to a valid port number
 */
int getValidPort(char* data) {
	std::string portStr(data);
	int port = atoi(data);

	//Hardcode prolly not best for OS determined port range....
	if (port > 0x0000 && port < 0xFFFF) {
		//More validation goes here, if needed.
	} else {
		printUsage("Supplied Port '" + portStr + "' is invalid.");
		bu_exit(1, "");
	}
	return port;
}

/* 
 * =====================
 *
 *        Main
 *
 * =====================
 */

int main(int argc, char* argv[]) {
	Logger::getInstance();
	JobManager::getInstance()->startup();

	logBanner("libNetTest");

	if (argc > 4 || argc < 3) {
		printUsage("Incorrect ARG count.");
		bu_exit(1, "");
	}

	bool isServer;
	short port;
	std::string ip("");

	//Get app mode.  Either client or server
	std::string cliServ(argv[1]);
	std::transform(cliServ.begin(), cliServ.end(), cliServ.begin(), tolower);

	if (cliServ == "client") {
		isServer = false;
		ip = argv[2];
		port = getValidPort(argv[3]);
	} else if (cliServ == "server") {
		isServer = true;
		port = getValidPort(argv[2]);
	} else {
		printUsage("Unknown mode: '" + cliServ + "'");
		bu_exit(1, "");
	}

	QString s("Running in ");
	s.append(cliServ.c_str());
	s.append(" mode.");
	logInfo(s);

	if (isServer) {
		PortalManager pm(port);
		pm.start();

		//listen for a loooong time.
		GSThread::sleep(60 * 60); //1 hr
		logInfo("Shutting down...");
		pm.shutdown();

	} else {
		PortalManager pm;
		pm.start();

		GSThread::sleep(3);

		s = "Trying to connect to ";
		s.append(ip.c_str());
		s.append(":");
		s.append(QString::number(port));
		logInfo(s);

		QString t(ip.c_str()); //this is dumb!
		Portal* p = pm.connectToHost(t, port);

		if (p != 0) {
			GSThread::sleep(2);
			TypeOnlyMsg tom(RUALIVE);
			p->send(&tom);
			GSThread::sleep(2);
			logInfo("Shutting down...");
			p->disconnect();
		}

		GSThread::sleep(2);
		logInfo("Shutting down...");
		pm.shutdown();
	}

	GSThread::sleep(1);
	JobManager::getInstance()->shutdown(true);
	GSThread::sleep(1);
	return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
