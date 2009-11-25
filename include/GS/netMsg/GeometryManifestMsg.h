/*           G E O M E T R Y M A N I F E S T M S G . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file GeometryManifestMsg.h
 *
 * Brief description
 *
 */

#ifndef __GEOMETRYMANIFESTMSG_H__
#define __GEOMETRYMANIFESTMSG_H__

#include <vector>
#include "iBME/iBMECommon.h"
#include "GE/io/DataStream.h"
#include "GS/netMsg/NetMsg.h"


class GeometryManifestMsg : public NetMsg
{

public:

  //Normal Constructor
  GeometryManifestMsg( QList<QString>& items);

  //Reply Constructor
  GeometryManifestMsg(NetMsg* msg, QList<QString>& items );

  //Deserializing Constructor
  GeometryManifestMsg(QDataStream* ds);

  //Destructor
  virtual ~GeometryManifestMsg();
  
  virtual QString toString();

  /*
   *Getters n Setters
   */
  quint32 getNumOfItems();
  QList<QString>* getItemData();

private:
  QList<QString>* itemData;
  
  virtual bool _serialize(QDataStream* ds);

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
