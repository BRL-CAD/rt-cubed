#ifndef __DATE_H__
#define __DATE_H__

#include <string>

namespace Utility {

  /** Generic representation of a date
   */
  class Date
  {
  protected:
  public:
    Date();
    Date(int year, unsigned month, unsigned day);
    Date(const Date& date);
    Date(const std::string date);
    ~Date();

    std::string string();
    Date& operator=(Date date);
    Date& operator+=(Date date);
    Date& operator-=(Date date);
  };

}


#endif  /* __DATE_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
