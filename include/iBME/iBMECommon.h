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

#define REMHOSTNAMESET 		5
#define	REMHOSTNAMESETOK 	10

#define	DISCONNECTREQ 		15
#define NEWHOSTONNET     	20

#define FULLHOSTLISTREQ		25
#define FULLHOSTLISTREQFAIL	30
#define FULLHOSTLISTREQOK	35

#define NEWSESSIONREQ		40
#define NEWSESSIONREQFAIL	45
#define NEWSESSIONREQOK		50

#define	GEOMETRYREQ		100
   #define ReqByUUID         10
   #define ReqByFilePath     11
#define	GEOMETRYREQFAIL		105
#define GEOMETRYMANIFEST	110
#define GEOMETRYCHUNK		115


/*  Failure Codes */
#define UUIDNotFoundFailure      0
#define FileNotFoundFailure      1




#endif //ndef (_IBMECOMMON_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
