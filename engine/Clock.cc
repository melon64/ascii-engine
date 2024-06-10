#include <time.h>
#include "Clock.h"

Clock::Clock() {
    clock_gettime (CLOCK_REALTIME, &tickPrev);
}

Clock::~Clock() {
}

long int Clock::delta() {
    struct timespec tick;
    clock_gettime (CLOCK_REALTIME, &tick);
    long int delta = (tick.tv_sec - tickPrev.tv_sec) * 1000000000 + tick.tv_nsec - tickPrev.tv_nsec;
    tickPrev = tick; //reset the timer
    return delta;
}

long int Clock::split() {
    struct timespec tick;
    clock_gettime (CLOCK_REALTIME, &tick);
    long int delta = (tick.tv_sec - tickPrev.tv_sec) * 1000000000 + tick.tv_nsec - tickPrev.tv_nsec;
    return delta;
}

