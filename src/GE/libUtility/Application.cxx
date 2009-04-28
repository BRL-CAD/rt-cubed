// interface header
#include "Utility/Application.h"

// implementation system headers
#include <time.h>
#include <algorithm>

// implementation headers
#include "../../date/buildStamp.h"

using namespace Utility;

Application::Application(int argc, char*argv[])
{
}


Application::~Application()
{
}


bool Application::run()
{
}


Date Application::buildDate() const
{
  return Date(std::string(::buildDate));
}


Time Application::buildTime() const
{
  return Time(std::string(::buildTime));
}


Date Application::runDate() const
{
  return _runDate;
}


Time Application::runTime() const
{
  return _runTime;
}


std::string Application::uptime() const
{
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8