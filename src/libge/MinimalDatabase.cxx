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

using namespace BRLCAD;

MinimalDatabase::MinimalDatabase(void) throw(bad_alloc) {
}

MinimalDatabase::~MinimalDatabase(void) throw() {
}

MinimalObject*
MinimalDatabase::getObjectByName(std::string name) {
	return NULL;
}

std::list<MinimalObject*>*
MinimalDatabase::getAllObjectsBelow(std::string name) {
	return NULL;
}

std::list<MinimalObject*>*
MinimalDatabase::getAllObjects() {
	return NULL;
}

std::list<MinimalObject*>*
MinimalDatabase::getAllTopObjects() {
	return NULL;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
