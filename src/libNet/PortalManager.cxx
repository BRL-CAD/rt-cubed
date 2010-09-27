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
	PkgTcpClient* pkgc = (PkgTcpClient* )this->tcpServer->connectToHost(host.toStdString(), port);

	if (pkgc == NULL) {
		return NULL;
	} else {
		return this->makeNewPortal(pkgc);
	}
}

void
PortalManager::_run()
{
  struct timeval timeout;
  fd_set readfds;
  fd_set writefds;
  fd_set exceptionfds;
  int listener;

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
		}

		this->masterFDSLock.lock();
		FD_SET(listener, &masterfds);
		fdmax = listener;
		this->masterFDSLock.unlock();
	}

  while (this->runCmd) {
	  //Set values EVERY loop since select() on *nix modifies this.
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;


	this->masterFDSLock.lock();
    readfds = masterfds;
    writefds = masterfds;
    exceptionfds = masterfds;
    this->masterFDSLock.unlock();

    //Shelect!!
    int retval = select(fdmax+1, &readfds, &writefds, NULL, &timeout);

    QString out("Loop start.  Select returned: ");
    out.append(QString::number(retval));
    this->log->logINFO("PortalManager", out);

    //Save time on the loop:
    if (retval == 0) {
    	continue;
    }

    if(retval <0) {
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
    	  /*
			if (FD_ISSET(i, &exceptionfds)) {
				//TODO handle exceptions
				perror("Exception on FileDescriptor");
			}
*/

			if (FD_ISSET(i, &readfds)) {
				this->log->logINFO("PortalManager", "Read On Listener.");

				//If we are 'reading' on listener
				if (port != 0 && i == listener) {
					PkgTcpClient* client = (PkgTcpClient*) this->tcpServer->waitForClient(42);

					if (client == 0) {
						  this->log->logERROR("PortalManager", "Error on accepting new client.");
					} else {
						//Handle new client here.
						this->makeNewPortal(client);
					}

					//else we are plain reading.
				} else {
					this->log->logINFO("PortalManager", "Read On Normal FD.");
					//Portal->read here.
					if (this->fdPortalMap->contains(i)) {
						this->portalsLock->lock();
						int readResult = this->fdPortalMap->value(i)->read();
						this->portalsLock->unlock();

						if (readResult == 0) {
							this->closeFD(i, "Lost connection to remote host.");
							continue;
						} else if (readResult < 0) {
							this->closeFD(i, "Error on read, dropping connection to remote host.");
							continue;
						}

					} else {
						//Deal with unmapped file Descriptor
						this->closeFD(i, "Attempting to read from FD not associated with a Portal, dropping connection to remote host.");
						continue;
					}
				}
			}

			/*
			 * Do we really need Write checking?
			 */
			if (FD_ISSET(i, &writefds)) {
				this->log->logINFO("PortalManager", "Write.");

				/*
				//Portal->write here.
				if (this->fdPortalMap->contains(i)) {
					this->portalsLock->lock();
					int readResult = this->fdPortalMap->value(i)->write();
					this->portalsLock->unlock();

					if (readResult == 0) {
						this->closeFD(i,"Lost connection to remote host.\n", &masterfds);
						continue;
					} else if (readResult < 0) {
						this->closeFD(i, "Error on write, dropping connection to remote host.\n", &masterfds);
						continue;
					}

				} else {
                    //Deal with unmapped file Descriptor
					this->closeFD(i,"Attempting to write to FD not associated with a Portal, dropping connection to remote host.", &masterfds);
					continue;
				}
				*/
			}

		} //end FOR
    } //end while
}//end fn


Portal*
PortalManager::makeNewPortal(PkgTcpClient* client) {
	Portal* newPortal = new Portal(client);

	if (newPortal == 0) {
		return 0;
	}

	//Obtain lock and then map this new portal
	this->portalsLock->lock();
	int newFD = newPortal->pkgClient->getFileDescriptor();
	this->fdPortalMap->insert(newFD, newPortal);
	this->portalsLock->unlock();

	//Check maxFD and update if needed.
	if (newFD > fdmax) {
		this->masterFDSLock.lock();
		fdmax = newFD;
		this->masterFDSLock.unlock();
	}

	newPortal->sendGSNodeName();

	return newPortal;
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
