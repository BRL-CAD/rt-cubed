#ifndef __TIMER_H__
#define __TIMER_H__

#include <ctime>

namespace Utility {

  /** Low-resolution (hundredth of a second) timer class
   */
  class Timer
  {
  protected:
    bool _running;
    bool _started;
    clock_t _start;
    double _accumulated;
    
    double elapsedSinceStart();

  public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

    void start();
    void stop();
    void reset();

    double elapsed();

    bool running();
  };

}


#endif  /* __TIMER_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
