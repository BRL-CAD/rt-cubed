#include "RtApplication.h"

#include <iostream>


RtApplication::RtApplication(int argc, char *argv[]) : Utility::Application(argc, argv)
{
  std::cout << "starting the rtapplication" << std::endl;
}


RtApplication::~RtApplication() 
{
  std::cout << "destroying the rtapplication" << std::endl;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
