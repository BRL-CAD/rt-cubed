#include "main.h"

int main(int argc, char *argv[])
{
  std::cout << "Testing" << std::endl;

  Utility::init();
  std::cout << "Build date is " << buildDate << std::endl;
  std::cout << "Build time is " << buildTime << std::endl;

  return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
