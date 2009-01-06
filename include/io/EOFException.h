/*           E O F E X C E P T I O N . H
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

/** @file EOFException.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */


#ifndef _CLASS_EOFEXCEPTION_H
#define _CLASS_EOFEXCEPTION_H

#ifdef __cplusplus

#include "io/IOException.h"


namespace ibme {
	namespace io {

		class  EOFException : public IOException
		{
		public:
			EOFException() throw ();
			EOFException(const String& message) throw ();
		};
	}
}

#endif

#endif
