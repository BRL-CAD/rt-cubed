/*                   A B S T R A C T J O B . H
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
/** @file AbstractJob.h
 *
 * Brief description
 *
 */

#ifndef __ABSTRACTJOB_H__
#define __ABSTRACTJOB_H__

#include "iBME/iBMECommon.h"
#include "GS/GSCommon.h"

class AbstractJob {

public:
	AbstractJob();
	virtual ~AbstractJob();

	JobResult doJob();
	JobStatus getStatus();

private:
	unsigned int jobID;

	JobStatus status;

	virtual JobResult _doJob();
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
