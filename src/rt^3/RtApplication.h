#ifndef __RTAPPLICATION_H__
#define __RTAPPLICATION_H__

#include "utility/Application.h"

class RtApplication : public Utility::Application
{
protected:
public:
  RtApplication(int argc=0, char*argv[]=0);
  ~RtApplication();

};

#endif  /* __RTAPPLICATION_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
