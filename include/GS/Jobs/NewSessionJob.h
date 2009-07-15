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
/** @file NewSessionJob.h
 *
 *	Description:
 *
 *	$HeadURL: $
 *	$Date: $
 *	$Revision: $
 *	$Author: $ 
 *
 */

#ifndef _NEWSESSIONJOB_H_
#define _NEWSESSIONJOB_H_

#include "GS/Jobs/AbstractJob.h"
#include "GS/AbstractPortal.h"

class NewSessionJob : public AbstractJob
{

public:

  virtual ~NewSessionJob();
  NewSessionJob(AbstractPortal& portal);
  virtual bool doJob();

private:
  NewSessionJob();

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
