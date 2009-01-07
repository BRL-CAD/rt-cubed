/*                 C O P Y C A C H E T O D I S K J O B . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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

/** @file CopyCacheToDiskJob.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_COPYCACHETODISKJOB_H_)
#define _COPYCACHETODISKJOB_H_

#include "GeometryService/Jobs/AbstractJob.h"
#include "GeometryEngine/DbObject.h"

class CopyCacheToDiskJob : public AbstractJob
{

public:
  CopyCacheToDiskJob(DbObject& resToCopy);
  virtual ~CopyCacheToDiskJob();

  virtual bool doJob();

private:
  DbObject& resToCopy();

};

#endif // !defined(_COPYCACHETODISKJOB_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
