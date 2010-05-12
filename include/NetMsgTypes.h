/*                    N E T M S G T Y P E S . H
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
/** @file NetMsgTypes.h
 *
 * Brief description
 *
 */

#ifndef __NETMSGTYPES_H__
#define __NETMSGTYPES_H__

/*  NetMsg Types */

#define	FAILURE          	0
#define	SUCCESS          	5

#define REMGSHOSTNAMESET	100

#define	DISCONNECTREQ 		150

#define NEWHOSTONNET     	200

#define FULLHOSTLISTREQ		250
#define FULLHOSTLIST		255

#define NEWSESSIONREQ		300
#define SESSIONINFO		305
#define LOGOUTSESSION		310

#define	GEOMETRYREQ		400
#define ReqByUUID       	  10
#define ReqByFilePath  		  11
#define GEOMETRYMANIFEST	405
#define GEOMETRYCHUNK		410

/*  Failure Codes */
#define UUIDNotFoundFailure      10
#define FileNotFoundFailure      20

#define PORTAL_HANDSHAKE_FAILURE   	30
#define UNKNOWN_PORTAL_FAILURE		40
#define PORTAL_WRITE_FAILURE		50
#define PORTAL_READ_FAILURE		60
#define REM_HOST_DISCONNECT		70
#define LOCAL_DISCONNECT_REQ		80

#define AUTHENTICATION_FAILED		90

#endif /* __NETMSGTYPES_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
