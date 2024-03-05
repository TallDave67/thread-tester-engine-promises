#include "event_logger.h"
#include <iostream>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

EventLogger* pg_event_logger = nullptr;
std::mutex g_mutex_send;

EventLogger::EventLogger()
{
}
    
void EventLogger::send_event(std::string & event)
{
    // Acquire the lock on the send mutex using std::lock_guard
    std::lock_guard<std::mutex> lock(g_mutex_send);    
    
    std::cout << "[" << getCurrentTimestamp() << "] " << event << std::endl;
}

std::string EventLogger::getCurrentTimestamp() 
{
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a tm struct
    std::tm timeStruct = *std::localtime(&currentTime);

    // Get the microseconds component separately
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1000000;

    // Format the timestamp
    std::ostringstream oss;
    oss << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S"); // Format: "YYYY-MM-DD hh::mm::ss"
    oss << "::" << std::setw(6) << std::setfill('0') << microseconds; // Append microseconds
    return oss.str();
}
