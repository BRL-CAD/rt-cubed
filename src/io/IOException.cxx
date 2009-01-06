
/*            I O E X C E P T I O N . C X X
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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

/** @file IOException.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/IOException.h"
#include "lang/Exception.h"

using ibme::io::IOException;

IOException::IOException()
{
}

IOException::IOException(const String& message) : ibme::lang::Exception(message)
{
}
