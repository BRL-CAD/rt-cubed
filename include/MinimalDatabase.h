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
#include <stdio.h>
#include <iostream>

namespace BRLCAD {

	/* Need a simple super class to expose constructor */
	class MinimalCombination: public BRLCAD::Combination {
	protected:
		MinimalCombination(resource* resp, directory* pDir, rt_db_internal* ip,
				db_i* dbip): BRLCAD::Combination(resp, pDir,ip, dbip) {};
		friend class MinimalDatabase;
	};


	class MinimalDatabase : public MemoryDatabase {
	public:
		MinimalDatabase();
		MinimalDatabase(std::string filePath);
		virtual ~MinimalDatabase(void);

		bool Load(const std::string name);
		bool Load(const char* name);
		bool Load();

		bool Save(const std::string name);
		bool Save(const char* name);
		bool Save();


		std::string getFilePath();

 		MinimalObject* getObjectByName(std::string name);
		std::list<MinimalObject*>* getAllObjectsBelow(std::string name);
		void getAllObjectsBelow(std::string name, std::list<MinimalObject*>* list);
		std::list<MinimalObject*>* getAllObjects();
		std::list<MinimalObject*>* getAllTopObjects();

	std::list<MinimalObject*>* getAllObjs();
	std::list<MinimalObject*>* getAllObjsBelow(const std::string objectName);
	void getAllObjsBelowRecursor(const std::string, const char*,
			std::list<MinimalObject*>*) ;
	void treeNodeRecursor(const BRLCAD::Combination::ConstTreeNode&,
			const std::string, std::list<MinimalObject*>*);

	struct bu_external* buildExternal(struct directory*, struct db_i*);
	MinimalObject* buildMinimalObject(std::string, std::string, struct bu_external*);

	private:
	/// Performs database object look ups, but copies the contents into a bu_external which it returns
	bu_external* GetExternal(const char* objectName);

	void _searchNode(BRLCAD::Combination::ConstTreeNode node,
			std::list<MinimalObject*>* list);

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
