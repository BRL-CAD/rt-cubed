/*               M I N I M A L D A T A B A S E . H
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
/** @file MinimalDatabase.h
 * MinimalDatabase.h
 *
 *  Created on: Mar 31, 2011
 *      Author: dloman
 */

#ifndef __MINIMALDATABASE_H__
#define __MINIMALDATABASE_H__

#include "MinimalObject.h"

#include "brlcad/MemoryDatabase.h"
#include "brlcad/Combination.h"
#include "brlcad/cicommon.h"
#include <new>
#include <list>
#include <string.h>

namespace BRLCAD {
	class MinimalDatabase : public MemoryDatabase {
	public:
		MinimalDatabase() throw(bad_alloc);
		MinimalDatabase(std::string filePath) throw(bad_alloc);
		virtual ~MinimalDatabase(void) throw();

		bool Load(const std::string name) throw() ;
		bool Load(const char* name) throw() ;
		bool Load() throw() ;

		bool Save(const std::string name) throw() ;
		bool Save(const char* name) throw() ;
		bool Save() throw() ;


		std::string getFilePath();

 		MinimalObject* getObjectByName(std::string name);
		std::list<MinimalObject*>* getAllObjectsBelow(std::string name);
		void getAllObjectsBelow(std::string name, std::list<MinimalObject*>* list);
		std::list<MinimalObject*>* getAllObjects();
		std::list<MinimalObject*>* getAllTopObjects();

	private:
		/// Performs database object look ups, but copies the contents into a bu_external which it returns
		bu_external* GetExternal(const char* objectName) const;

		void _searchNode(BRLCAD::Combination::ConstTreeNode node, std::list<MinimalObject*>* list);

		std::string currentFilePath;
	};
}
#endif /* __MINIMALDATABASE_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
