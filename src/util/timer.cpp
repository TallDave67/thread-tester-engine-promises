#include "timer.h"

Timer::Timer()
    : running(false)
{

}

void Timer::start()
{
    startTimePoint = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    stopTimePoint = std::chrono::high_resolution_clock::now();
    running = false;
}

std::chrono::_V2::system_clock::rep Timer::duration_in_nanoseconds() const
{
    if (running) {
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTimePoint);
        return duration.count();
    } else {
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTimePoint - startTimePoint);
        return duration.count();
    }
}
