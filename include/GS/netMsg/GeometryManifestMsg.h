/*
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
 *	Description:
 *
 *	$HeadURL: $
 *	$Date$
 *	$Revision: $
 *	$Author: $ 
 *
 */

#ifndef _GEOMETRYMANIFESTMSG_H_
#define _GEOMETRYMANIFESTMSG_H_

#include <vector>
#include "iBME/iBMECommon.h"
#include "GE/io/DataStream.h"
#include "GS/netMsg/NetMsg.h"


class GeometryManifestMsg : public NetMsg
{

public:

  //Constructor
  GeometryManifestMsg(unsigned int mType, UUID mUUID, UUID rUUID);

  //Deserializing Constructors
  GeometryManifestMsg(unsigned char* data, unsigned int len);
  GeometryManifestMsg(DataStream* ds);

  //Destructor
  virtual ~GeometryManifestMsg();
  
  virtual std::string toString();

  /*
   *Getters n Setters
   */
  unsigned int getNumOfItems();

  std::vector<std::string>* getItemData();

  

private:
  std::vector<std::string>* itemData;
  virtual bool _deserialize(DataStream* ds);
  virtual bool _serialize(DataStream* ds);

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
