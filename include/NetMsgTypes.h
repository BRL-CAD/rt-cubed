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

#define	TEST_GENERIC_4BYTE_MSG	        0x0020
#define	TEST_GENERIC_2BYTE_MSG	        0x0021
#define	TEST_GENERIC_1BYTE_MSG          0x0022
#define	TEST_GENERIC_MULTIBYTE_MSG	0x0023
#define	TEST_GENERIC_1STRING_MSG	0x0024

#define	FAILURE			        0x0050
#define	SUCCESS          	        0x0051

#define REMGSHOSTNAMESET	        0x0100

#define	DISCONNECTREQ 		        0x0150

#define NEWHOSTONNET                    0x0200

#define FULLHOSTLISTREQ		        0x0250
#define FULLHOSTLIST		        0x0255

#define NEWSESSIONREQ		        0x0300
#define SESSIONINFO		        0x0305
#define LOGOUTSESSION		        0x0310

#define	GEOMETRYREQ		        0x0400
#define ReqByUUID       	          0x0010
#define ReqByFilePath  		          0x0011
#define GEOMETRYMANIFEST	        0x0405
#define GEOMETRYCHUNK		        0x0410

/*  Failure Codes */
#define UUIDNotFoundFailure             0x0010
#define FileNotFoundFailure             0x0020

#define PORTAL_HANDSHAKE_FAILURE   	0x0030
#define UNKNOWN_PORTAL_FAILURE		0x0040
#define PORTAL_WRITE_FAILURE		0x0050
#define PORTAL_READ_FAILURE		0x0060
#define REM_HOST_DISCONNECT		0x0070
#define LOCAL_DISCONNECT_REQ		0x0080

#define AUTHENTICATION_FAILED		0x0090

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
