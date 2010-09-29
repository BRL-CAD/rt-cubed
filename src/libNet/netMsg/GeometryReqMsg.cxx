/*              G E O M E T R Y R E Q M S G . C X X
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
/** @file GeometryReqMsg.cxx
 *
 * Brief description
 *
 */

#include "NetMsgTypes.h"
#include "GeometryReqMsg.h"

/* Normal Constructor */
GeometryReqMsg::GeometryReqMsg(quint8 requestType, QString data) :
    GenericOneStringMsg(GEOMETRYREQ, data), reqType(requestType)
{
}

/* Reply Constructor */
GeometryReqMsg::GeometryReqMsg(NetMsg* msg, quint8 requestType, QString data) :
	GenericOneStringMsg(GEOMETRYREQ, msg, data), reqType(requestType)
{
}

/* Deserializing Constructor */
GeometryReqMsg::GeometryReqMsg(QDataStream* ds, Portal* origin) :
    GenericOneStringMsg(ds, origin)
{
    *ds >> this->reqType;
}

/* Destructor */
GeometryReqMsg::~GeometryReqMsg()
{
}

bool GeometryReqMsg::_serialize(QDataStream* ds)
{
    //Call the super
    GenericOneStringMsg::_serialize(ds);

    *ds << this->reqType;
    return true;
}

QString GeometryReqMsg::toString()
{
    QString out;

    out.append(GenericOneStringMsg::toString());
    out.append("' requestType: '");
    out.append(QString::number(this->reqType));
    out.append("'");

    return out;
}

bool GeometryReqMsg::_equals(const NetMsg& msg)
{
    GeometryReqMsg& gmsg = (GeometryReqMsg&) msg;

    if (this->getRequestType() != gmsg.getRequestType()) {
	return false;
    }

    return true;
}

/*
 *Getters n Setters
 */
quint8 GeometryReqMsg::getRequestType()
{
    return this->reqType;
}

QString
GeometryReqMsg::getData()
{
    return this->strData;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
