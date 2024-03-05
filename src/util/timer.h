#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    std::chrono::_V2::system_clock::rep duration_in_nanoseconds() const;

private:
    std::chrono::_V2::system_clock::time_point startTimePoint;
    std::chrono::_V2::system_clock::time_point stopTimePoint;
    bool running;
};

#endif
