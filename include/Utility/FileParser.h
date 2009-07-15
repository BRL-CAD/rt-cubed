/*
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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
 *	Description:
 *
 *	$HeadURL: $
 *	$Date$
 *	$Revision$
 *	$Author$ 
 *
 */

#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include <iostream>

namespace Utility {

  template < typename FileParserMethod, typename Container >
  class FileParser : public FileParserMethod
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


  template < typename FileParserMethod, typename Container >
  bool FileParser<FileParserMethod, Container>::load()
  {
    /*    _container->add(*parse(_filename)); */
  }


  template < typename FileParserMethod, typename Container >
  FileParser<FileParserMethod, Container>::FileParser(std::string filename) : FileParserMethod(filename)
  {
    _filename = filename;
    _container = new Container();
    load();
  }

  
  template < typename FileParserMethod, typename Container >
  FileParser<FileParserMethod, Container>::~FileParser()
  {
    _filename = "";
    delete _container;
  }


  template < typename FileParserMethod, typename Container >
  Container& FileParser<FileParserMethod, Container>::getContainer() const
  {
    return *_container;
  }

}


#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
