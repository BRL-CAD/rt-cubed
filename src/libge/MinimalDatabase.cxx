/*             M I N I M A L D A T A B A S E . C X X
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
/** @file MinimalDatabase.cxx
 * MinimalDatabase.cxx
 *
 *  Created on: Mar 31, 2011
 *      Author: dloman
 */

#include "MinimalDatabase.h"
#include "raytrace.h"

// TODO should this defined here AND in ConstDatabase.cpp, or should they be combined in a header somewhere?
#if defined (_DEBUG)
#   define LOOKUP_NOISE LOOKUP_NOISY
#else
#   define LOOKUP_NOISE LOOKUP_QUIET
#endif

using namespace BRLCAD;

MinimalDatabase::MinimalDatabase() throw(bad_alloc)
		: MemoryDatabase(), currentFilePath("") {}

MinimalDatabase::MinimalDatabase(std::string filePath) throw(bad_alloc)
		: MemoryDatabase(), currentFilePath(filePath) {
	this->Load();
}

MinimalDatabase::~MinimalDatabase(void) throw() {
}

MinimalObject*
MinimalDatabase::getObjectByName(std::string name) {
	bu_external* ext = this->GetExternal(name.c_str());

	/* Check to see if the lookup succeeded or not. */
	if (ext == NULL) {
		return NULL;
	}

	return new MinimalObject(currentFilePath, name, ext);
}

std::list<MinimalObject*>*
MinimalDatabase::getAllObjectsBelow(std::string name) {
	//TODO implement this recursive treewalk
	return NULL;
}

std::list<MinimalObject*>*
MinimalDatabase::getAllObjects() {
	//TODO implement this recursive treewalk
	return NULL;
}

std::list<MinimalObject*>*
MinimalDatabase::getAllTopObjects() {
	/*
	 * Its ugly and performs two look ups per object, but it works for now.
	 * //TODO implement a dedicated iterator for this
	 */
	ConstDatabase::TopObjectIterator it = this->FirstTopObject();
	std::list<MinimalObject*>* objs = new std::list<MinimalObject*>();
	MinimalObject* obj = NULL;
	std::string name = "";

	while (it.Good()) {
		name = it.Name();

		if (name.length() > 0) {
			obj = this->getObjectByName(name);
			objs->push_back(obj);
		}
		++it;
	}

	return objs;
}

bu_external*
MinimalDatabase::GetExternal
(
    const char*     objectName
) const {
	bu_external* ext = NULL;

    if (m_rtip != 0) {
        if (!BU_SETJUMP) {
            if ((objectName != 0) && (strlen(objectName) > 0)) {
                directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISE);

                if (pDir != RT_DIR_NULL) {
                    /* Check to see if passed in ext was malloced */
                    if (ext == NULL)
                    	ext = (bu_external*)bu_calloc(sizeof(bu_external),1,"GetExternal bu_external calloc");

                	int rVal = db_get_external(ext, pDir, this->m_rtip->rti_dbip);

                	if (rVal < 0) {
                        BU_UNSETJUMP;
                		bu_free(ext, "Freeing bu_external due to error.");
                		return ext;
                	}
                }
            }
        }
        BU_UNSETJUMP;
    }
    return ext;
}

std::string
MinimalDatabase::getFilePath() {
	return this->currentFilePath;
}

bool
MinimalDatabase::Load() throw() {
	return this->Load(this->currentFilePath);
}

bool
MinimalDatabase::Load(const std::string name) throw() {
	return this->Load(name.c_str());
}

bool
MinimalDatabase::Load(const char* name) throw() {
	this->currentFilePath = name;
	return MemoryDatabase::Load(name);
}

bool
MinimalDatabase::Save() throw() {
	return this->Save(this->currentFilePath);
}

bool
MinimalDatabase::Save(const std::string name) throw() {
	return this->Save(name.c_str());
}

bool
MinimalDatabase::Save(const char* name) throw() {
	this->currentFilePath = name;
	return MemoryDatabase::Save(name);
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
