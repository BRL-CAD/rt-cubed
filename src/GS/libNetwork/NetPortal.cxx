/*               N E T S O C K P O R T A L . C X X
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
/** @file NetPortal.cxx
 *
 * Brief description
 *
 */

#include "GS/GSCommon.h"
#include "GS/libNetwork/NetPortal.h"
#include "GS/libNetwork/NetMsg.h"
#include "GS/libNetwork/RemHostNameSetMsg.h"
#include "GS/libNetwork/NetPortalManager.h"

#include <QHostAddress>

NetPortal::NetPortal(NetPortalManager* nspm)
{
	this->log = Logger::getInstance();
	this->nspm = nspm;
	this->handshakeStatus = NotConnected;

	QObject::connect(sock, SIGNAL(connected()), this,
			SLOT(relaySockConnected()));
	QObject::connect(sock, SIGNAL(disconnected()), this, SLOT(
			relaySockDisconnected()));
	QObject::connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(relaySockError(QAbstractSocket::SocketError)));

	QObject::connect(sock, SIGNAL(readyRead()), this, SLOT(
			moveDataFromSocketBuffer()));

}

NetPortal::~NetPortal()
{

}

/************************/
/* QTcpSocket Delegates */
/************************/

void NetPortal::connectToHost(QString hostname, quint16 port)
{
	this->sock->connectToHost(hostname, port);
}
void NetPortal::connectToHost(QHostAddress address, quint16 port)
{
	this->sock->connectToHost(address, port);
}
void NetPortal::disconnect(quint8 reason)
{
	QString msg;
	msg += "Disconnected from: " + this->sock->peerAddress().toString() + " ("
			+ this->remHostName + "). Reason code: " + reason + "\n";
	this->log->log(Logger::INFO, msg);

	this->sock->disconnectFromHost();
}

/***************************/
/* QTcpSocket Signal Relay */
/***************************/
void NetPortal::relaySockConnected()
{
	emit portalConnected();
}
void NetPortal::relaySockDisconnected()
{
	this->updateHandshakeStatus(NetPortal::NotConnected);
	emit portalDisconnected();
}
void NetPortal::relaySockError(QAbstractSocket::SocketError err)
{
	emit socketError(err);
}

/***************/
/* Handshaking */
/***************/

void NetPortal::updateHandshakeStatus(HandshakeStatus newStatus)
{
	if (this->handshakeStatus != newStatus)
	{
		HandshakeStatus oldStatus = this->handshakeStatus;
		this->handshakeStatus = newStatus;
		emit handshakeStatusUpdate(newStatus, oldStatus);
	}
}

/*****************/
/* Incoming Data */
/*****************/

void NetPortal::moveDataFromSocketBuffer()
{
	//get data off socket
	QByteArray data = this->sock->readAll();

	//put into factory buffer & attempt a msg build.
	this->factory->addData(data);
	this->attemptToBuildMsg();
}

void NetPortal::attemptToBuildMsg(){
	this->factory->attemptToMakeMsgs();

	QString msg;
	msg += "New data from: " + this->sock->peerAddress().toString() + ". ";
	msg += this->factory->getInboxSize() + " Msgs in factory inbox.\n";
	this->log->log(Logger::INFO, msg);

	if (this->hasMsg())
	{

		switch (this->handshakeStatus)
		{
		case (NetPortal::Ready):
			//Normally, just emit a signal.
			emit msgReady();
			break;
		case (NetPortal::NotConnected):
		case (NetPortal::Handshaking):
		{
			this->updateHandshakeStatus(NetPortal::Handshaking);
			NetMsg* msg = this->getNextMsg();

			if (msg->getMsgType() != REMHOSTNAMESET)
			{
				this->disconnect(PORTAL_HANDSHAKE_FAILURE);
				break;
			}

			RemHostNameSetMsg* rhnsm = (RemHostNameSetMsg*) msg;

			QString remoteHostname =
					((RemHostNameSetMsg*) msg)->getRemoteHostName();

			delete rhnsm;

			//Zero length check
			if (remoteHostname.isEmpty())
			{
				this->disconnect(PORTAL_HANDSHAKE_FAILURE);
				break;
			}

			//If the nspm returns a NetPortal object, then this host is already on the network!
			if (this->nspm->getPortalByRemHostname(remoteHostname) != NULL)
			{
				this->disconnect(PORTAL_HANDSHAKE_FAILURE);
				break;
			}

			this->remHostName = remoteHostname;
			this->updateHandshakeStatus(NetPortal::Ready);
			emit portalHandshakeComplete();

			break;
		}
		default:
			//Should be failed
			this->disconnect(PORTAL_HANDSHAKE_FAILURE);
			break;
		}

	}
}

/**
 * This function blocks until all data is sent.
 */
void NetPortal::send(NetMsg& msg)
{
	QByteArray ba;
	msg.serialize(&ba);

	QString str;
	str += "Sending msg of type: " + msg.getMsgType();
	str += ", id: " + msg.getMsgUUID();
	str += ", length: " + QString::number(ba.size()) + "\n";
	this->log->log(Logger::INFO, str);

	quint64 totalToSend = ba.size();
	quint64 thisSend = 0;
	quint64 totalSent = 0;

	//TODO needs to be a better way to do this
	while (totalSent < totalToSend)
	{
		thisSend = this->sock->write(ba);

		//Check for socket failure
		if (thisSend == -1)
		{
			this->disconnect(PORTAL_WRITE_FAILURE);
			return;
		}

		//Check for Zero bytes sent
		if (thisSend == 0)
		{
			if (totalSent != totalToSend)
			{
				std::cerr << "Did not send all data from Msg to host: "
						<< this->remHostName.toStdString() << "\n";
			}
			return;
		}
		totalSent += thisSend;
	}

}

bool NetPortal::hasMsg()
{
	return this->factory->hasMsgsAvailable();
}

NetMsg* NetPortal::getNextMsg()
{
	return this->factory->getNextMsg();
}

QString NetPortal::getRemoteHostName()
{
	return this->remHostName;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
