/*           C L O N E N O T S U P P O R T E D E X C E P T I O N . C X X
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

/** @file CloneNotSupportedException.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */


#include "lang/CloneNotSupportedException.h"

using ibme::lang::CloneNotSupportedException;

CloneNotSupportedException::CloneNotSupportedException() throw ()
{
}

CloneNotSupportedException::CloneNotSupportedException(const String& message) throw () : Exception(message)
{
}
