#ifndef _THREAD_WRAPPER_H_
#define _THREAD_WRAPPER_H_

#include "timer.h"
#include <string>
#include <thread>

static const int THREAD_WRAPPER_RUN_ABORT = -2;
static const int THREAD_WRAPPER_RUN_FAILURE = -1;
static const int THREAD_WRAPPER_RUN_NOOP = 0;
static const int THREAD_WRAPPER_RUN_SUCCESS = 1;

typedef struct THREAD_WRAPPER_RUN_DETAILS
{
    THREAD_WRAPPER_RUN_DETAILS();

    std::string id;
    Timer timer;
    int finish_state;
} THREAD_WRAPPER_RUN_DETAILS;

class ThreadWrapper
{
public:
    ThreadWrapper();
    ThreadWrapper(const ThreadWrapper& other);
    ~ThreadWrapper();

    virtual bool run();
    void wait();

    std::string& get_id();
    std::thread::id get_native_id();
    std::thread::native_handle_type get_native_handle();

protected:
    std::string id;
    std::unique_ptr<std::thread> thread_ptr;
};

#endif
