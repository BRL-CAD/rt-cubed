/*               G S C O M M O N . H
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

/*  NetMsg Types */

#define	FAILURE          	0
#define	SUCCESS          	5

#define REMHOSTNAMESET 		100

#define	DISCONNECTREQ 		150

#define NEWHOSTONNET     	200

#define FULLHOSTLISTREQ		250
#define FULLHOSTLIST		255

#define NEWSESSIONREQ		300
#define NEWSESSION			305

#define	GEOMETRYREQ			400
#define ReqByUUID         10
#define ReqByFilePath     11
#define GEOMETRYMANIFEST	405
#define GEOMETRYCHUNK		410

/*  Failure Codes */
#define UUIDNotFoundFailure      0
#define FileNotFoundFailure      1

#define PORTAL_HANDSHAKE_FAILURE    2
#define UNKNOWN_PORTAL_FAILURE		3
#define PORTAL_WRITE_FAILURE		4
#define PORTAL_READ_FAILURE			5
#define REM_HOST_DISCONNECT			6

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
