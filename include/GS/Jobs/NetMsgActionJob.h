/*               N E T M S G A C T I O N J O B . H
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
/** @file NetMsgActionJob.h
 *
 * Brief description
 *
 */

#ifndef __NETMSGACTIONJOB_H__
#define __NETMSGACTIONJOB_H__

#include "GS/Jobs/AbstractJob.h"
#include "GS/netMsg/NetMsg.h"

class NetMsgActionJob : public AbstractJob
{

public:

  virtual ~NetMsgActionJob();

  NetMsgActionJob(NetMsg& msg);
  virtual bool doJob();

private:
  NetMsgActionJob();
  NetMsg& msg();

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
