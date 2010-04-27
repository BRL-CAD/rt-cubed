/*             G E N E R I C T W O B Y T E S M S G . C X X
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
/** @file GenericTwoBytesMsg.cxx
 *
 * Brief description
 *
 */

#include "libNetwork/GenericTwoBytesMsg.h"
#include <sstream>

//Normal Constructor
GenericTwoBytesMsg::GenericTwoBytesMsg(quint32 type, quint16 b) :
    NetMsg(type), data(b)
{
}

//Reply Constructor
GenericTwoBytesMsg::GenericTwoBytesMsg(quint32 type, NetMsg* msg, quint16 b) :
    NetMsg(type, msg), data(b)
{
}

//Deserializing Constructors
GenericTwoBytesMsg::GenericTwoBytesMsg(QDataStream* ds, QString origin) :
    NetMsg(ds, origin)
{
    *ds >> this->data;
}

//Destructor
GenericTwoBytesMsg::~GenericTwoBytesMsg()
{
}

bool GenericTwoBytesMsg::_serialize(QDataStream* ds)
{
    *ds << this->data;
    return true;
}

QString GenericTwoBytesMsg::toString()
{
    QString out;

    out.append(NetMsg::toString());
    out.append("\t data: '");
    out.append(QString::number(this->data));
    out.append("'");

    return out;
}

bool GenericTwoBytesMsg::_equals(NetMsg& msg)
{
    GenericTwoBytesMsg& gmsg = (GenericTwoBytesMsg&) msg;

    if (this->getData() != gmsg.getData()) {
	return false;
    }

    return true;
}

/*
 *Getters n Setters
 */
quint16 GenericTwoBytesMsg::getData()
{
    return this->data;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
