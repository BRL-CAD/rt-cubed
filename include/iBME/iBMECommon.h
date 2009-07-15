/*                      I B M E C O M M O N . H
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

/** @file iBMECommon.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _IBMECOMMON_H_
#define _IBMECOMMON_H_

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

#define RemHostNameSET 		0
#define	RemHostNameSETFAIL 	5
#define	RemHostNameSETOK 	10

#define	DisconnectREQ 		15
#define NewHostOnNetINFO 	20

#define FullHostListREQ		25
#define FullHostListREQFAIL	30
#define FullHostListREQOK	35

#define NewSessionREQ		40
#define NewSessionREQFAIL	45
#define NewSessionREQOK		50


#define	GeometryREQ		100
   #define ReqByUUID         0
   #define ReqByFilePath     1
#define	GeometryREQFAIL		105
#define GeometryMANIFEST	110
#define GeometryCHUNK		115


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
