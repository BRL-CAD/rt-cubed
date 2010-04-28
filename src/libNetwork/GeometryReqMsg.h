/*                G E O M E T R Y R E Q M S G . H
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
/** @file GeometryReqMsg.h
 *
 * Brief description
 *
 */

#ifndef __GEOMETRYREQMSG_H__
#define __GEOMETRYREQMSG_H__


#include "GenericOneStringMsg.h"

class GeometryReqMsg: public GenericOneStringMsg
{

public:

    //Only Constructor
    GeometryReqMsg(quint8 requestType, QString data);

    //Reply Constructor
    GeometryReqMsg(NetMsg* msg, quint8 requestType, QString s);

    //Deserializing Constructors
    GeometryReqMsg(QDataStream* ds, QString origin);

    //Destructor
    virtual ~GeometryReqMsg();

    virtual QString toString();

    /*
     *Getters n Setters
     */
    quint8 getRequestType();

    QString getData();

private:
    quint8 reqType;

    bool _serialize(QDataStream* ds);
    bool _equals(NetMsg& msg);

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
