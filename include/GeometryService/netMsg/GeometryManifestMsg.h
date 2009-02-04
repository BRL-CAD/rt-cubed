/*                  G E O M E T R Y M A N I F E S T M S G. H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_GEOMETRYMANIFESTMSG_H_)
#define _GEOMETRYMANIFESTMSG_H_

#include <vector>
#include "iBME/iBMECommon.h"
#include "io/DataStream.h"
#include "GeometryService/netMsg/NetMsg.h"


class GeometryManifestMsg : public NetMsg
{

public:

  //Constructor
  GeometryManifestMsg(uInt mType, UUID mUUID, UUID rUUID);

  //Deserializing Constructors
  GeometryManifestMsg(uByte data[], uInt len);
  GeometryManifestMsg(DataStream* ds);

  //Destructor
  virtual ~GeometryManifestMsg();
  
  virtual String toString();

  /*
   *Getters n Setters
   */
  uInt getNumOfItems();

  std::vector<String>* getItemData();


private:
  std::vector<String> itemData;
  virtual bool _deserialize(DataStream* ds);
  virtual bool _serialize(DataStream* ds);

};

#endif // !defined(_GEOMETRYMANIFESTMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
