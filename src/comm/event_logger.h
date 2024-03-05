#ifndef _EVENT_LOGGER_H_
#define _EVENT_LOGGER_H_

#include <string>

class EventLogger
{
public:
    EventLogger();
    
    void send_event(std::string & event);
    std::string getCurrentTimestamp();
};

extern EventLogger* pg_event_logger;

#endif