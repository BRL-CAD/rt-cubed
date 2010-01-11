/*               G S C O M M O N . H
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
/** @file GeometryService.h
 *
 * Brief description
 *
 */

#ifndef __GSCOMMON_H__
#define __GSCOMMON_H__

//JobManager stuff
#define MAX_JOBWORKERS 5


enum JobWorkerStatus
{
	WORKER_NOTREADY, WORKER_READY, WORKER_RUNNING
};
enum JobStatus
{
	JOB_NOTSTARTED, JOB_RUNNING, JOB_FINISHED
};
enum JobResult
{
	JOB_COMPLETED_NO_ERRORS, JOB_COMPLETED_WITH_ERRORS, JOB_FAILED
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
