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

PortalManager::PortalManager(quint16 port) : ControlledThread("PortalManager")
{
  this->port = port;
  this->tcpServer = new PkgTcpServer();
  this->fdPortalMap = new QMap<int, Portal*>();
  this->portalsLock = new QMutex();
  this->log = Logger::getInstance();
}

PortalManager::~PortalManager()
{
}

Portal*
PortalManager::connectToHost(QString host, quint16 port)
{
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
	struct timeval timeout;
	fd_set readfds;
	fd_set writefds;
	fd_set exceptionfds;
	int listener = -1;

	this->masterFDSLock.lock();
	FD_ZERO(&masterfds);
	this->masterFDSLock.unlock();

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
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
			this->log->logERROR("PortalManager", s);
		}

		this->masterFDSLock.lock();
		FD_SET(listener, &masterfds);
		fdmax = listener;
		this->masterFDSLock.unlock();
	}

	while (this->runCmd) {
		//Set values EVERY loop since select() on *nix modifies this.
		timeout.tv_sec = 0;
		timeout.tv_usec = 500*1000 * 2;

		this->masterFDSLock.lock();
		readfds = masterfds;
		//writefds = masterfds;
		exceptionfds = masterfds;
		this->masterFDSLock.unlock();

		//Shelect!!
		int retval =
				select(fdmax + 1, &readfds, NULL, &exceptionfds, &timeout);

		QString out("Select returned: ");
		out.append(QString::number(retval));
		out.append(". FD count: ");
		out.append(QString::number(this->fdPortalMap->keys().size()));
		out.append(". MAX FD: ");
		out.append(QString::number(fdmax));
		this->log->logINFO("PortalManager", out);

		//Save time on the loop:
		if (retval == 0) {
			//continue;
		}

		if (retval < 0) {
			//got a selector error

			/*      if(revtal == EABDF) {
			 bu_log("Selector Error: EBADF: An invalid file descriptor was given in one of the sets. (Perhaps a file descriptor that was already closed, or one on which an error has occurred.)\n");
			 } else if (retval == EINTR) {
			 bu_log("Selector Error: EINTR: A signal was caught.\n");
			 } else if (retval == EINVAL) {
			 bu_log("Selector Error: EINVAL: nfds is negative or the value contained within timeout is invalid.\n");
			 } else if (retval == ENOMEM) {
			 bu_log("Selector Error: ENOMEM: unable to allocate memory for internal tables.\n");
			 }*/

			this->log->logERROR("PortalManager", "Selector Error.");

			break;
		}

		for (int i = 0; i <= fdmax; ++i) {
			bool isaFD = FD_ISSET(i, &masterfds);

			//Don't muck with an FD that isn't ours!
			if (!isaFD) {
				continue;
			}

			//Simplify switching later with bools now
			bool isListener = (i == listener);
			bool readyRead = FD_ISSET(i, &readfds) && !isListener;
			bool readyWrite = FD_ISSET(i, &writefds);
			bool readyAccept = FD_ISSET(i, &readfds) && isListener;
			bool readyException = FD_ISSET(i, &exceptionfds);

			QString s("FD:");
			s.append(QString::number(i));

			if (isListener) {
				s.append(" is the listener and");
			}

			s.append(" is on the: masterFDS");

			if (readyRead) {
				s.append(", readFDS");
			}
			if (readyWrite) {
				s.append(", writeFDS");
			}
			if (readyException) {
				s.append(", exceptionFDS");
			}

			log->logDEBUG("PortalManager", s);

			//If nothing to do, then continue;
			if (!readyRead && !readyWrite && !readyAccept && ! readyException){
				continue;
			}


			//Handle exceptions
			if (readyException) {
				//TODO handle exceptions
				perror("Exception on FileDescriptor");
			}



			Portal* p = NULL;
			//Accept new connections:
			if (readyAccept) {
				log->logINFO("PortalManager", "Accept");

				struct pkg_switch* table = this->makeNewSwitchTable();

				PkgTcpClient* client =
						(PkgTcpClient*) this->tcpServer->waitForClient(table, 42);

				if (client == 0) {
					log->logERROR("PortalManager",
							"Error on accepting new client.");
				} else {
					//Handle new client here.
					p = this->makeNewPortal(client, table);
					GSThread::sleep(2);
					p->sendGSNodeName();
				}
			}

			//the only thing we want to do on the listener loop is accept
			if (isListener) {
				continue;
			}

			//If we didnt get a portal from accepting, then get one from the map
			if (p == 0 && this->fdPortalMap->contains(i)) {
				this->portalsLock->lock();
				p = this->fdPortalMap->value(i);
				this->portalsLock->unlock();
			}

			//Check, again, if we have a good portal.
			if (p == 0) {
				//Deal with unmapped file Descriptor
				QString s("FD ");
				s.append(QString::number(i));
				s.append(" not associated with a Portal, dropping connection.");
				this->closeFD(i, s);
				continue;
			}
/*
			  const pkg_switch* table = p->pkgClient->getCallBackTable();
			  pkg_switch sw = table[0];
			  bu_log("PM(3.1): Route[0] type: %d\n", sw.pks_type);
			  bu_log("PM(3.1): Route[0] callback: %d\n", sw.pks_handler);
			  bu_log("PM(3.1): Route[0] user_data: %d\n", sw.pks_user_data);
*/
			//read
			if (readyRead) {
				this->log->logINFO("PortalManager", "Read");

				int readResult = p->read();

				  QString s("Got ");
				  s.append(QString::number(readResult));
				  s.append(" bytes.");
				  Logger::getInstance()->logINFO("PortalManager", s);

				if (readResult == 0) {
					this->closeFD(i, "Lost connection.");
					continue;
				} else if (readResult < 0) {
					this->closeFD(i, "Error on read, dropping connection.");
					continue;
				}
			}

			//write
			if (readyWrite) {
				this->log->logINFO("PortalManager", "Write.");

				int retVal = p->flush();
				bu_log("Flushed %d bytes.", retVal);

				if (retVal < 0) {
					this->closeFD(i, "Error on write, dropping connection.");
					continue;
				}
			}
		} //end FOR
	} //end while
}//end fn


Portal*
PortalManager::makeNewPortal(PkgTcpClient* client, struct pkg_switch* table) {
	Portal* newPortal = new Portal(client, table);

	if (newPortal == 0) {
		return 0;
	}

	//Obtain lock and then map this new portal
	this->portalsLock->lock();
	int newFD = newPortal->pkgClient->getFileDescriptor();
	this->fdPortalMap->insert(newFD, newPortal);
	this->portalsLock->unlock();

	QString s ("New Portal with FD: ");
	s.append(QString::number(newFD));
	log->logDEBUG("PortalManager", s);

	//Check maxFD and update if needed.
	if (newFD > fdmax) {
		this->masterFDSLock.lock();
		FD_SET(newFD, &masterfds);
		fdmax = newFD;
		this->masterFDSLock.unlock();
	}
	return newPortal;
}

struct pkg_switch*
PortalManager::makeNewSwitchTable()
{
	struct pkg_switch* table = new pkg_switch[2];

	table[0].pks_type = PKG_MAGIC2;
	table[0].pks_handler = &(Portal::callbackSpringboard);
	table[0].pks_title = "SpringBoard";
	table[0].pks_user_data = 0;

	table[1].pks_type = 0;
	table[1].pks_handler = 0;
	table[1].pks_title = (char*)0;
	table[1].pks_user_data = 0;

	return table;
}

void
PortalManager::closeFD(int fd, QString logComment)
{
	close(fd);

	this->masterFDSLock.lock();
	if (FD_ISSET(fd, &this->masterfds)) {
		FD_CLR(fd, &this->masterfds);
	}
	this->masterFDSLock.unlock();

	this->log->logERROR("PortalManager", logComment);
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
