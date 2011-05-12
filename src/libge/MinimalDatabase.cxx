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
    if (m_wdbp != 0) {
        if (!BU_SETJUMP)
            wdb_close(m_wdbp);

        BU_UNSETJUMP;
        m_wdbp = NULL;
    }

    if (m_rtip != 0) {
        if (!BU_SETJUMP)
            rt_free_rti(m_rtip);

        BU_UNSETJUMP;
        m_rtip = NULL;
    }

    if (m_resp != 0) {
        rt_clean_resource_complete(0, m_resp);
        bu_free(m_resp, "BRLCAD::ConstDatabase::~ConstDatabase::m_resp");
        m_resp = NULL;
    }
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
	std::list<MinimalObject*>* list = new std::list<MinimalObject*>();
	this->getAllObjectsBelow(name, list);
	return list;
}

void
MinimalDatabase::getAllObjectsBelow(std::string name, std::list<MinimalObject*>* list) {
	Object* o = this->Get(name.c_str());

	/* Validate */
	if (o == NULL)
		return;

	bu_external* ext = this->GetExternal(name.c_str());
	if (ext == NULL)
		return;

	/* Archive */
	//TODO need to check to see if list already contains new element.
	list->push_back(new MinimalObject(this->currentFilePath,name, ext));

	/* Recurse */
	const BRLCAD::Combination* comb = dynamic_cast<const BRLCAD::Combination*>(o);
	if (comb != 0)
		this->_searchNode(comb->Tree(), list);

}

void
MinimalDatabase::_searchNode(BRLCAD::Combination::ConstTreeNode node, std::list<MinimalObject*>* list) {

	switch (node.Operation()) {
	case BRLCAD::Combination::ConstTreeNode::Union:
	case BRLCAD::Combination::ConstTreeNode::Intersection:
	case BRLCAD::Combination::ConstTreeNode::Subtraction:
	case BRLCAD::Combination::ConstTreeNode::ExclusiveOr:
		_searchNode(node.LeftOperand(), list);
		_searchNode(node.RightOperand(),list);
		break;

	case BRLCAD::Combination::ConstTreeNode::Not:
		_searchNode(node.Operand(), list);
		break;

	case BRLCAD::Combination::ConstTreeNode::Leaf:
		this->getAllObjectsBelow(node.Name(), list);
	}

}

std::list<MinimalObject*>*
MinimalDatabase::getAllObjects() {
	/*
	 * Its ugly and performs two look ups per object, but it works for now.
	 * //TODO implement a dedicated iterator for this
	 */
	ConstDatabase::TopObjectIterator it = this->FirstTopObject();
	std::list<MinimalObject*>* list = new std::list<MinimalObject*>();

	std::string name = "";

	while (it.Good()) {
		name = it.Name();

		if (name.length() > 0)
			this->getAllObjectsBelow(name, list);

		++it;
	}

	return list;
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


std::list<MinimalObject*>*
MinimalDatabase::getAllObjs()
{
	std::list<MinimalObject*>* objList = new std::list<MinimalObject*>();

	ConstDatabase::TopObjectIterator it = this->FirstTopObject();
	std::string name = "";

	while (it.Good()) {
		name = it.Name();
		if (name.length() > 0)
			this->getAllObjsBelowRecursor(this->currentFilePath + "/", name.c_str(), objList);
		++it;
	}

	return objList;
}


std::list<MinimalObject*>*
MinimalDatabase::getAllObjsBelow
(
	const std::string objectName
) {
	std::list<MinimalObject*>* objList = new std::list<MinimalObject*>();

	if (objectName.length() > 0)
		this->getAllObjsBelowRecursor(this->currentFilePath + "/", objectName.c_str(), objList);

	return objList;
}

void
MinimalDatabase::getAllObjsBelowRecursor
(
	const std::string currentPath,
	const char*     objectName,
	std::list<MinimalObject*>* objList
)  {
	bu_external* ext = NULL;
	MinimalObject* obj = NULL;

    if (m_rtip != 0) {
        if (!BU_SETJUMP) {
            if ((objectName != 0) && (strlen(objectName) > 0)) {
                directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISE);

                if (pDir != RT_DIR_NULL) {
                    rt_db_internal intern;
                    int            id = rt_db_get_internal(&intern, pDir, m_rtip->rti_dbip, 0, m_resp);

                    try {
						ext = buildExternal(pDir, m_rtip->rti_dbip);

						if (ext == NULL) {
							std::cout << "buildExternal FAILED\n";
						} else {
							obj = this->buildMinimalObject(currentPath, objectName, ext);
							if (ext == NULL) {
								std::cout << "buildMinimalObject FAILED\n";
							} else {

								/* Add to list */
								objList->push_back(obj);

								/* Recurse on combs */
								if (id == ID_COMBINATION) {
									MinimalCombination comb (m_resp, pDir, &intern, m_rtip->rti_dbip);
									std::string newPath = currentPath + "/" + objectName;

									treeNodeRecursor(comb.Tree(), newPath, objList);
								}
							}
						}
                    }
                    catch(...) {
                        BU_UNSETJUMP;
                        rt_db_free_internal(&intern);
                        throw;
                    }

                    rt_db_free_internal(&intern);
                }
            }
        }

        BU_UNSETJUMP;
    }
}


void
MinimalDatabase::treeNodeRecursor
(
		const BRLCAD::Combination::ConstTreeNode& node,
		const std::string currentPath,
		std::list<MinimalObject*>* objList
) {
    switch (node.Operation()) {
        case BRLCAD::Combination::ConstTreeNode::Union:
        case BRLCAD::Combination::ConstTreeNode::Intersection:
        case BRLCAD::Combination::ConstTreeNode::Subtraction:
        case BRLCAD::Combination::ConstTreeNode::ExclusiveOr:
        	treeNodeRecursor(node.LeftOperand(), currentPath, objList);
        	treeNodeRecursor(node.RightOperand(), currentPath, objList);
            break;

        case BRLCAD::Combination::ConstTreeNode::Not:
        	treeNodeRecursor(node.Operand(), currentPath, objList);
            break;

        case BRLCAD::Combination::ConstTreeNode::Leaf:
        	std::string nodeName = node.Name();
			this->getAllObjsBelowRecursor(currentPath, nodeName.c_str(), objList);
    }

}

struct bu_external*
MinimalDatabase::buildExternal(struct directory* pDir, struct db_i* dbip) {
	bu_external* ext = (bu_external*)bu_calloc(sizeof(bu_external),1,"GetExternal bu_external calloc");

	int rVal = db_get_external(ext, pDir, dbip);

	if (rVal < 0) {
		bu_free(ext, "Freeing bu_external due to error.");
		return NULL;
	}
	return ext;
}

MinimalObject*
MinimalDatabase::buildMinimalObject(std::string path, std::string objName, bu_external* ext)
{
	return new MinimalObject(path, objName, ext);
}

bu_external*
MinimalDatabase::GetExternal
(
    const char*     objectName
) {
	bu_external* ext = NULL;

    if (m_rtip != 0) {
        if (!BU_SETJUMP) {
            if ((objectName != 0) && (strlen(objectName) > 0)) {
                directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISE);
                if (pDir != RT_DIR_NULL)
                	ext = this->buildExternal(pDir, this->m_rtip->rti_dbip);
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
