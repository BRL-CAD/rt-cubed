/*                      N E T M S G . C X X
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
/** @file NetMsg.cxx
 *
 * Brief description
 *
 */

#include "libNetwork/NetMsg.h"
#include <sstream>

//Normal Constructor
NetMsg::NetMsg(quint32 mType) :
    msgLen(0), msgType(mType), hasReUUID(false), reUUID(NULL)
{
    msgUUID = QUuid::createUuid();
}

//Reply Constructor
NetMsg::NetMsg(quint32 mType, NetMsg* msg) :
    msgLen(0), msgType(mType)
{
    if (msg->getMsgUUID() != NULL) {

	QString strUUID = msg->getMsgUUID().toString();

	QUuid uuid(strUUID);

	this->reUUID = uuid;

	this->hasReUUID = true;

    }
    else {

	this->reUUID = NULL;
	this->hasReUUID = false;
    }

    msgUUID = QUuid::createUuid();

}

//Deserializing Constructors
NetMsg::NetMsg(QDataStream* ds, QString origin)
{
    this->origin = origin;

    try {
	*ds >> this->msgLen;

	*ds >> this->msgType;

	this->msgUUID = *Utils::getQUuid(ds);

	*ds >> this->hasReUUID;

	if (this->hasReUUID) {
	    this->reUUID = *Utils::getQUuid(ds);
	}

    } catch (IOException ioe) {
	std::cerr << "Error in NetMsg(): " << ioe.getMessage() << std::endl;
    }

}

//Destructor
NetMsg::~NetMsg()
{
}

//Serializers
QByteArray* NetMsg::serialize()
{
    QByteArray* ba = new QByteArray();

    this->serialize(ba);

    return ba;
}

void NetMsg::serialize(QByteArray* ba)
{
    //Make a BA for the subclass
    QByteArray* subBA = new QByteArray();

    //Make a DS for the subclass
    QDataStream* subDS = new QDataStream(subBA, QIODevice::ReadWrite);

    //Serialize Header
    *subDS << this->msgType;
    Utils::putQUuid(subDS, this->msgUUID);
    *subDS << this->hasReUUID;

    if (this->hasReUUID) {
	Utils::putQUuid(subDS, this->reUUID);
    }

    //Call subclass serialize
    if (!this->_serialize(subDS)) {
	std::cerr << "A serialization Error in NetMsg::serialize() occurred.\n";
	return;
    }

    //Make a DS & BA
    QByteArray* outBA = new QByteArray();
    QDataStream outDS(outBA, QIODevice::ReadWrite);

    //write the length msgLen
    outDS << subBA->size();

    //Then add the entire contents of subBA
    *outBA += *subBA;

    //Finally, dump serialized object into the supplied BA:
    *ba += *outBA;

    delete subDS;
    delete subBA;
    delete outBA;
}

bool NetMsg::_serialize(QDataStream* ds)
{
    return true;
}

/*
 *Getters n Setters
 */
quint32 NetMsg::getMsgLen()
{
    return this->msgLen;
}
quint32 NetMsg::getMsgType()
{
    return this->msgType;
}
QUuid NetMsg::getMsgUUID()
{
    return this->msgUUID;
}
bool NetMsg::msgHasReUUID()
{
    return this->hasReUUID;
}
QUuid NetMsg::getReUUID()
{
    return this->reUUID;
}

/*
 * Utilities
 */
bool NetMsg::equals(NetMsg& msg)
{
    if (this->getMsgType() != msg.getMsgType()) {
	return false;
    }

    if (this->getMsgUUID() != msg.getMsgUUID()) {
	return false;
    }

    if (this->msgHasReUUID() != msg.msgHasReUUID()) {
	return false;
    }

    if (this->msgHasReUUID()) {
	if (this->getReUUID() != msg.getReUUID()) {
	    return false;
	}
    }

    return this->_equals(msg);
}

bool NetMsg::_equals(NetMsg& msg)
{
    return true;
}

QString NetMsg::toString()
{
    QString out;

    out += "msgType: '" + QString::number(this->msgType);

    if (this->msgUUID != NULL) {
	out += "'\t msgUUID: '" + this->msgUUID.toString();
    }

    out += "'\t hasReUUID: '" + QString::number(this->hasReUUID);

    if (this->reUUID != NULL) {
	out += "'\t reUUID: '" + this->reUUID.toString();
    }

    out += "'";

    return out;
}

std::string NetMsg::toStdString()
{
    return this->toString().toStdString();
}

void NetMsg::printMe()
{
    std::cout << this->toStdString();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
