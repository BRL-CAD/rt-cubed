/*             G E N E R I C O N E B Y T E M S G . C X X
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
/** @file GenericOneByteMsg.cxx
 *
 * Brief description
 *
 */

#include "GS/netMsg/GenericOneByteMsg.h"
#include <sstream>

//Normal Constructor
GenericOneByteMsg::GenericOneByteMsg(quint32 type, quint8 b):
  NetMsg(type), data(b)
{
}

  //Reply Constructor
GenericOneByteMsg::GenericOneByteMsg(quint32 type, NetMsg* msg, quint8 b):
  NetMsg(type, msg), data(b)
{
}

//Deserializing Constructors
GenericOneByteMsg::GenericOneByteMsg(QDataStream* ds):
NetMsg(ds)
{
   *ds >> this->data;
}

//Destructor
GenericOneByteMsg::~GenericOneByteMsg()
{
}

bool GenericOneByteMsg::_serialize(QDataStream* ds)
{
  *ds << this->data;
  return true;
}

QString GenericOneByteMsg::toString() 
{
  QString out;

  out.append(NetMsg::toString());
  out.append("\t data: '");
  out.append(QString::number(this->data));
  out.append("'");
  
  return out;
}

bool
GenericOneByteMsg::_equals(NetMsg& msg) 
{
  GenericOneByteMsg& gmsg = (GenericOneByteMsg&) msg;

  if (this->getData() != gmsg.getData()) {
    return false;
  }

  return true;
}

 /*
 *Getters n Setters
 */
quint8 GenericOneByteMsg::getData() {return this->data;}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
