#include "thread_driver.h"
#include "event_logger.h"
#include "thread_wrapper.h"
#include <sstream>

ThreadDriver::ThreadDriver()
{
}

ThreadDriver::~ThreadDriver()
{
}

void ThreadDriver::reserve(size_t num_threads)
{
    // reserve space for the thread wrappers
    threads.reserve(num_threads);
}

void ThreadDriver::add_thread_wrapper(ThreadWrapper* thread_wrapper)
{
    // add the thread wrapper and set its event logger
    threads.push_back(thread_wrapper);
}

ThreadWrapper* ThreadDriver::get_thread_wrapper(size_t index)
{
    ThreadWrapper *pThreadWrapper = nullptr;
    if(index < threads.size())
    {
        pThreadWrapper = threads[index];
    }
    return pThreadWrapper;
}

void ThreadDriver::run()
{
    for(auto & t : threads)
    {
        // log the event
        std::stringstream ss;
        ss << "{\"event_type\":\"run\", \"event\":\"start\", \"object\":\"thread_wrapper\", \"id\":" << t->get_id() << "}";        
        std::string event = ss.str();
        pg_event_logger->send_event(event);

        t->run();
    }

    for(auto & t : threads)
    {
        t->wait();
    }

}
