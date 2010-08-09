/*                    F I L E P A R S E R . H
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file FileParser.h
 *
 * Brief description
 *
 */

#ifndef __FILEPARSER_H__
#define __FILEPARSER_H__

#include <iostream>

template<typename FileParserMethod, typename Container>
class FileParser: public FileParserMethod
{
protected:
    std::string _filename;
    Container *_container;
public:
    bool load();

    FileParser(std::string filename);
    ~FileParser();

    Container& getContainer() const;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
