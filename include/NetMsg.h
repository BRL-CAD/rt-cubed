/*                        N E T M S G . H
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
/** @file NetMsg.h
 *
 * Brief description
 *
 */

#ifndef __NETMSG_H__
#define __NETMSG_H__

/*  NetMsg Types */

#define	FAILURE          	0
#define	SUCCESS          	5

#define REMGSHOSTNAMESET	100

#define	DISCONNECTREQ 		150

#define NEWHOSTONNET     	200

#define FULLHOSTLISTREQ		250
#define FULLHOSTLIST		255

#define NEWSESSIONREQ		300
#define SESSIONINFO		305
#define LOGOUTSESSION		310

#define	GEOMETRYREQ		400
#define ReqByUUID       	  10
#define ReqByFilePath  		  11
#define GEOMETRYMANIFEST	405
#define GEOMETRYCHUNK		410

/*  Failure Codes */
#define UUIDNotFoundFailure      10
#define FileNotFoundFailure      20

#define PORTAL_HANDSHAKE_FAILURE   	30
#define UNKNOWN_PORTAL_FAILURE		40
#define PORTAL_WRITE_FAILURE		50
#define PORTAL_READ_FAILURE		60
#define REM_HOST_DISCONNECT		70
#define LOCAL_DISCONNECT_REQ		80

#define AUTHENTICATION_FAILED		90

#include "IOException.h"
#include "libutility.h"
#include <QDataStream>
#include <QByteArray>
#include <QUuid>
#include <sstream>

class NetMsg
{

public:

	//Normal Constructor
	NetMsg(quint32 mType);

	//Reply Constructor
	NetMsg(quint32 mType, NetMsg* msg);

	//Deserializing Constructors
	NetMsg(QDataStream* ds, QString origin);

	//Destructor
	virtual ~NetMsg();

	//Serializers
	QByteArray* serialize();
	void serialize(QByteArray* ba);

	/*
	 *Getters n Setters
	 */
	quint32 getMsgLen();
	quint32 getMsgType();
	QUuid getMsgUUID();
	bool msgHasReUUID();
	QUuid getReUUID();

	/*
	 * Utilities
	 */
	virtual QString toString();
	virtual std::string toStdString();
	virtual bool equals(NetMsg& msg);
	void printMe();

protected:
	quint32 msgLen;
	quint32 msgType;
	QUuid msgUUID;
	bool hasReUUID;
	QUuid reUUID;
	QString origin;

	virtual bool _serialize(QDataStream* ds);
	virtual bool _equals(NetMsg& msg);

	//Disable Default Constructor
	NetMsg(){};
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
