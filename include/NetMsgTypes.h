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
#define	TEST_GENERIC_MULTIBYTE_MSG		0x0023
#define	TEST_GENERIC_1STRING_MSG		0x0024

#define	RUALIVE							0x0042
#define	IMALIVE							0x0043

#define	FAILURE			        		0x0050
#define	SUCCESS          	        	0x0051

#define GS_REMOTE_NODENAME_SET	        0x0100

#define	DISCONNECTREQ 		        	0x0150

#define NEWNODEONNET                	0x0200

#define FULLNODELISTREQ		        	0x0250
#define FULL_NODE_LIST		        	0x0255

#define NEWSESSIONREQ		        	0x0300
#define SESSIONINFO		        		0x0305

#define	GEOMETRYREQ		        		0x0400
#define  REQ_BY_UUID       	        	  0x00
#define  REQ_BY_PATH	  		    	  0x01
#define GEOMETRYMANIFEST	        	0x0405
#define GEOMETRYCHUNK		        	0x0410

//Admin commands
#define CMD_SHUTDOWN					0x9000

/*  Failure Codes */
const char UNHANDLED_MSG_TYPE 	   = 0x01;
const char OPERATION_NOT_AVAILABLE = 0x02;
const char BAD_REQUEST			   = 0x03;
const char COULD_NOT_FIND_GEOMETRY = 0x04;
const char ACCOUNT_VALIDATION_FAIL = 0x05;


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
