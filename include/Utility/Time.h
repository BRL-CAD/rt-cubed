#ifndef __TIME_H__
#define __TIME_H__

#include <string>

namespace Utility {

  /** Generic representation of time
   */
  class Time
  {
  protected:
  public:
    Time();
    Time(int hour, int minute, int second);
    Time(const Time& time);
    Time(const std::string time);
    ~Time();

    std::string string();

    Time& operator=(Time time);
    Time& operator+=(Time time);
    Time& operator-=(Time time);
  };

}


#endif  /* __TIME_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
