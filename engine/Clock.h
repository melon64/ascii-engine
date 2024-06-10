#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>

class Clock {

    struct timespec tickPrev;

  public:
    Clock();
    virtual ~Clock();
    long int delta();
    long int split();

};

#endif
