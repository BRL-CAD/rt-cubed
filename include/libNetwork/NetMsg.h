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

#include "GS/GSCommon.h"

#include "GE/exception/IOException.h"
#include "utility.h"
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
  NetMsg(){}

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
