/*                        O B J E C T . H
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
/** @file Object.h
 *
 * Brief description
 *
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "GE/exception/CloneNotSupportedException.h"

class Object
	{
	protected:
		virtual Object* clone() const throw (CloneNotSupportedException);

	public:
		Object() throw ();
		virtual ~Object() {};

		virtual bool equals(const Object& compare) const throw ();
	};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
