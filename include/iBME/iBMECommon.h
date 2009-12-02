/*                    I B M E C O M M O N . H
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
/** @file iBMECommon.h
 *
 * Brief description
 *
 */

#ifndef __IBMECOMMON_H__
#define __IBMECOMMON_H__

#include <iostream>

  // These are only temporary
  typedef std::string     UUID;
  typedef std::string     URL;
//  typedef std::string     String;



  // These are Perminent
/*
  typedef uint8_t    uChar;
  typedef int8_t     Char;

  typedef uint8_t    uByte;
  typedef int8_t     Byte;

  typedef uint16_t   uShort;
  typedef int16_t    Short;

  typedef uint32_t   uInt;
  typedef int32_t    Int;

  typedef uint64_t   uLong;
  typedef int64_t    Long;
*/

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




#endif //ndef (_IBMECOMMON_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
