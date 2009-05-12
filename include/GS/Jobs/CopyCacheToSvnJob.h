/*                 C O P Y C A C H E T O S V N J O B . H
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

/** @file CopyCacheToSvnJob.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_COPYCACHETOSVNJOB_H_)
#define _COPYCACHETOSVNJOB_H_

#include "GS/Jobs/AbstractJob.h"
#include <string>

class CopyCacheToSvnJob : public AbstractJob
{

public:
  CopyCacheToSvnJob( std::string resToCopy);
  virtual ~CopyCacheToSvnJob();

  virtual bool doJob();

private:
  std::string resToCopy();

};

#endif // !defined(_COPYCACHETOSVNJOB_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
