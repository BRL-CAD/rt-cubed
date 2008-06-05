#ifndef __FILEPARSER_H__
#define __FILEPARSER_H__

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


#endif  /* __FILEPARSER_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
