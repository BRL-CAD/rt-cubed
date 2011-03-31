/*                 M I N I M A L O B J E C T . H
 * BRL-CAD
 *
 * Copyright (c) 2011 United States Government as represented by
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
/** @file MinimalObject.h
 * MinimalObject.h
 *
 *  Created on: Mar 31, 2011
 *      Author: dloman
 */

#ifndef __MINIMALOBJECT_H__
#define __MINIMALOBJECT_H__

#include <brlcad/Object.h>
#include <string>

namespace BRLCAD {
	class MinimalObject : public BRLCAD::Object {
	public:
		MinimalObject(void) throw(bad_alloc);
		virtual ~MinimalObject(void) throw();

		bu_external* getBuExternal();
		std::string getFilePath();
		std::string getFileName();
		std::string getObjectName();

	private:
		bu_external* ext;
		std::string filePath;
		std::string fileName;
		std::string objName;

	};
}
#endif /* __MINIMALOBJECT_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
