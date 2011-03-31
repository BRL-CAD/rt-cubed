/*               M I N I M A L O B J E C T . C X X
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
/** @file MinimalObject.cxx
 * MinimalObject.cxx
 *
 *  Created on: Mar 31, 2011
 *      Author: dloman
 */

#include "MinimalObject.h"
#include <iostream>

using namespace BRLCAD;

MinimalObject::MinimalObject(void) throw(bad_alloc) {
	this->ext = NULL;
	this->filePath = "";
	this->fileName = "";
	this->objName = "";
}

MinimalObject::~MinimalObject(void) throw() {

}

bu_external*
MinimalObject::getBuExternal()
{
	return this->ext;
}

std::string
MinimalObject::getFileName()
{
	return this->fileName;
}

std::string
MinimalObject::getFilePath()
{
	return this->filePath;
}

std::string
MinimalObject::getObjectName()
{
	return this->objName;
}

void
MinimalObject::printObjState()
{
	std::cout << "ext*: " << ((this->ext == NULL) ? "NULL" : "Set") << "\n";
	std::cout << "filePath: " << filePath << "\n";
	std::cout << "fileName: " << fileName << "\n";
	std::cout << "objName: " << objName << std::endl;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
