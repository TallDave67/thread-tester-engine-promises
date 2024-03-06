#ifndef _THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_H_
#define _THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_H_

#include "thread_wrapper.h"
#include <future>

extern const int THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_THREAD_COUNT;

typedef struct THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT
{
    THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT(bool v);

    bool val;
    THREAD_WRAPPER_RUN_DETAILS run_details;
    
} THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT;

class ThreadWrapper_promiseWithException_Worker : public ThreadWrapper
{
public:
    ThreadWrapper_promiseWithException_Worker(std::promise<THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT>& promise);
    ThreadWrapper_promiseWithException_Worker(const ThreadWrapper_promiseWithException_Worker& other);
    ~ThreadWrapper_promiseWithException_Worker();

    bool run() override;

private:
    std::promise<THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT>& m_promise;
};

#endif