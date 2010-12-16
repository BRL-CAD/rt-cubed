/*                    G S C L I E N T . C X X
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
/** @file GSClient.cxx
 * GSClient.cxx
 *
 */

#include "GSClient.h"

const std::string GSClient::defaultPrompt ="geoclient> ";

GSClient::GSClient() {
	this->ccReg = ClientCmdRegistry::getInstance();
	this->log = Logger::getInstance();
	this->jobMan = JobManager::getInstance();
	this->portMan = new PortalManager();

	this->stayRun = true;
	this->prompt = defaultPrompt;
}

GSClient::~GSClient() {
	delete this->portMan;
}

int
GSClient::run()
{
	this->log->logBANNER("geoclient","==================================");
	this->log->logBANNER("geoclient","GeometryService Test/Stress Client");
	this->log->logBANNER("geoclient","==================================");

	std::string in;
	while (this->stayRun) {
		in == "";
		std::cout << prompt;
		getline (std::cin, in);

		/* make a qstring */
		QString qin(in.c_str());

		/* convert to lowercase */
		qin = qin.toLower();

	    /* split string */
		QStringList list = qin.split(" ");

		/* check to see if there is at least one element */
		if (list.length() <= 0) {
			continue;
		}
		QString cmd = list.takeFirst();

		this->execCmd(cmd, list);

	}

	this->log->logINFO("geoclient","Exiting.");
	return 0;
}

bool
GSClient::execCmd(QString cmd, QStringList args)
{
	AbstractClientCmd* acc = this->ccReg->getCmd(cmd);

	if (acc == NULL) {
		this->log->logINFO("GSClient", "Unknown Command: '" + cmd + "'.");
		return false;
	}

	return acc->exec(this, args);
}

PortalManager*
GSClient::getPortMan()
{
	return this->portMan;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
