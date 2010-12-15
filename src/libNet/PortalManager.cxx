/*           P O R T A L M A N A G E R . C X X
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
/** @file PortalManager.cxx
 *
 * Brief description
 *
 */
#include "brlcad/bu.h"
#include "Portal.h"
#include "PortalManager.h"
#include "NetMsgFactory.h"
#include "PkgTcpClient.h"
#include "NetMsgTypes.h"

#include <stdio.h>
#include <errno.h>

PortalManager::PortalManager(quint16 port) :
	ControlledThread("PortalManager") {
	this->port = port;
	this->tcpServer = new PkgTcpServer();
	this->fdPortalMap = new QMap<int, Portal*> ();
	this->portalsLock = new QMutex();
	this->log = Logger::getInstance();
	this->fdmax = 0;
}

PortalManager::~PortalManager() {}

Portal*
PortalManager::connectToHost(QString host, quint16 port) {
	struct pkg_switch* table = this->makeNewSwitchTable();

	PkgTcpClient* pkgc = (PkgTcpClient*) this->tcpServer->connectToHost(
			host.toStdString(), port, table);

	if (pkgc == NULL) {
		return NULL;
	} else {
		Portal* p = this->makeNewPortal(pkgc, table);
		return p;
	}
}

void
PortalManager::_run() {
	this->log->logINFO("PortalManager", "Running");
	struct timeval timeout;
	fd_set readfds;
	fd_set exceptionfds;
	int listener = -1;

	this->masterFDSLock.lock();
	FD_ZERO(&masterfds);
	this->masterFDSLock.unlock();

	FD_ZERO(&readfds);
	FD_ZERO(&exceptionfds);

	if (this->port != 0) {
		listener = this->tcpServer->listen(this->port);
		if (listener < 0) {
			this->log->logERROR("PortalManager", "Failed to listen");
			return;
		} else {
			QString s("Listening on port: ");
			s.append(QString::number(port));
			s.append(" FD:");
			s.append(QString::number(listener));
			this->log->logINFO("PortalManager", s);
		}

		this->masterFDSLock.lock();
		FD_SET(listener, &masterfds);
		fdmax = listener;
		this->masterFDSLock.unlock();
	}

	bool isListener = false;
	bool readyRead = false;
	bool readyAccept = false;
	bool readyException = false;

	while (this->runCmd) {
		/* Set values EVERY loop since select() on *nix modifies this. */
		timeout.tv_sec = 0;
		timeout.tv_usec = 100 * 1000;

		this->masterFDSLock.lock();
		readfds = masterfds;
		exceptionfds = masterfds;
		this->masterFDSLock.unlock();

		/* Shelect!! */
		int retVal = select(fdmax + 1, &readfds, NULL, &exceptionfds, &timeout);

		/*
		if (retVal != 0) {
			QString out("Select returned: ");
			out.append(QString::number(retVal));
			out.append(". FD count: ");
			out.append(QString::number(this->fdPortalMap->keys().size()));
			out.append(". MAX FD: ");
			out.append(QString::number(fdmax));
			this->log->logINFO("PortalManager", out);
		}
		 */

		if (retVal < 0) {
			/* got a selector error */

			this->log->logERROR("PortalManager", "Selector Error: " + QString::number(errno));

			break;
		}

		for (int i = 0; i <= fdmax; ++i) {
			bool isaFD = FD_ISSET(i, &masterfds);

			/* Don't muck with an FD that isn't ours!*/
			if (!isaFD) {
				continue;
			}

			/* Simplify switching later with bools now*/
			isListener = (i == listener);
 			readyRead = FD_ISSET(i, &readfds) && !isListener;
			readyAccept = FD_ISSET(i, &readfds) && isListener;
			readyException = FD_ISSET(i, &exceptionfds);

			/* If nothing to do, then continue;*/
			if (!readyRead && !readyAccept && !readyException) {
				continue;
			}

			/* Handle exceptions */
			if (readyException) {
				/* TODO handle exceptions */
				perror("Exception on FileDescriptor");
			}

			Portal* p = NULL;
			/* Accept new connections: */
			if (readyAccept) {
				/* log->logINFO("PortalManager", "Accept"); */

				struct pkg_switch* table = this->makeNewSwitchTable();

				PkgTcpClient* client =
						(PkgTcpClient*) this->tcpServer->waitForClient(table,
								42);

				if (client == 0) {
					log->logERROR("PortalManager",
							"Error on accepting new client.");
				} else {
					/* Handle new client here. */
					p = this->makeNewPortal(client, table);
				}
			}

			/* the only thing we want to do on the listener loop is accept */
			if (isListener) {
				continue;
			}

			/* If we didnt get a portal from accepting, then get one from the map */
			if (p == 0 && this->fdPortalMap->contains(i)) {
				this->portalsLock->lock();
				p = this->fdPortalMap->value(i);
				this->portalsLock->unlock();
			}

			/* Check, again, if we have a good portal. */
			if (p == 0) {
				/* Deal with unmapped file Descriptor */
				QString s("FD ");
				s.append(QString::number(i));
				s.append(" not associated with a Portal, dropping connection.");
				this->closeFD(i, s);
				continue;
			}

			/* read */
			if (readyRead) {
				/* this->log->logINFO("PortalManager", "Read"); */

				int readResult = p->read();

				if (readResult == 0) {
					this->closeFD(i, "");
					continue;
				} else if (readResult < 0) {
					this->closeFD(i, "Error on read, dropping connection.");
					continue;
				}
			}
		} /* end FOR */
	} /* end while */
	this->log->logINFO("PortalManager", "Shutdown");
}/* end fn */

Portal*
PortalManager::makeNewPortal(PkgTcpClient* client, struct pkg_switch* table) {
	Portal* p = new Portal(this, client, table);

	if (p == 0) {
		return 0;
	}

	/* Obtain lock and then map this new portal */
	this->portalsLock->lock();
	int newFD = p->pkgClient->getFileDescriptor();
	this->fdPortalMap->insert(newFD, p);
	this->portalsLock->unlock();

	QString s("New Portal with FD: ");
	s.append(QString::number(newFD));
	log->logDEBUG("PortalManager", s);

	/* Check maxFD and update if needed. */
	if (newFD > fdmax) {
		this->masterFDSLock.lock();
		FD_SET(newFD, &masterfds);
		fdmax = newFD;
		this->masterFDSLock.unlock();
	}

	p->sendGSNodeName();

	return p;
}

struct pkg_switch*
PortalManager::makeNewSwitchTable() {
	struct pkg_switch* table = new pkg_switch[2];

	table[0].pks_type = PKG_MAGIC2;
	table[0].pks_handler = &(Portal::callbackSpringboard);
	table[0].pks_title = "SpringBoard";
	table[0].pks_user_data = 0;

	table[1].pks_type = 0;
	table[1].pks_handler = 0;
	table[1].pks_title = (char*) 0;
	table[1].pks_user_data = 0;

	return table;
}

void
PortalManager::closeFD(int fd, QString logComment) {
	close(fd);

	this->masterFDSLock.lock();
	if (FD_ISSET(fd, &this->masterfds)) {
		FD_CLR(fd, &this->masterfds);
	}
	this->masterFDSLock.unlock();

	this->portalsLock->lock();
	this->fdPortalMap->remove(fd);
	this->portalsLock->unlock();

	if (logComment.length() >0) {
		this->log->logINFO("PortalManager", logComment);
	}
}

void
PortalManager::disconnect(Portal* p)
{
	int fd = p->pkgClient->getFileDescriptor();
	this->closeFD(fd, "Disconnect requested.");
}

bool
PortalManager::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();
	switch(type) {
	case DISCONNECTREQ:
		this->handleDisconnectReqMsg((TypeOnlyMsg*)msg);
		return true;
	}
	return false;
}

void
PortalManager::handleDisconnectReqMsg(TypeOnlyMsg* msg)
{
	Portal* origin = msg->getOrigin();

	/* validate incoming data */
	if (origin == 0) {
		/* TODO Figure out how to how to handle NULL Portal */
		log->logERROR("PortalManager", "handleDisconnectReqMsg(): NULL Portal!");
		return;
	}

	this->disconnect(origin);
}
/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
