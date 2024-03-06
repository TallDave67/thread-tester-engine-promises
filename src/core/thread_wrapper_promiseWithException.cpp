#include "thread_wrapper_promiseWithException.h"

const int THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_THREAD_COUNT = 9;

void do_work_that_could_throw_exception(std::string id, std::promise<THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT> promise)
{
    bool val = false;
    THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT value {val};
    value.run_details.id = id;
    value.run_details.timer.start();

    try
    {
        // code that may throw
        throw std::runtime_error("thread could not do its work");

        // if all goes well
        value.val = true;
        value.run_details.finish_state = THREAD_WRAPPER_RUN_SUCCESS;
        value.run_details.timer.stop();
        promise.set_value(value); // Notify future
    }
    catch (...)
    {
        try
        {
            // store anything thrown in the promise
            promise.set_exception(std::current_exception());
        }
        catch (...) {} // set_exception() may throw too
    }
}

THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT::THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT(bool v)
    : val{v}
{
}

ThreadWrapper_promiseWithException_Worker::ThreadWrapper_promiseWithException_Worker(
    std::promise<THREAD_WRAPPER_PROMISE_WITH_EXCEPTION_RESULT>& promise)
        :  m_promise{promise}
{
        id = "promiseWithException_Worker";
}

ThreadWrapper_promiseWithException_Worker::ThreadWrapper_promiseWithException_Worker(const ThreadWrapper_promiseWithException_Worker& other)
    : ThreadWrapper(other), m_promise{other.m_promise}
{
}

ThreadWrapper_promiseWithException_Worker::~ThreadWrapper_promiseWithException_Worker()
{
}

bool ThreadWrapper_promiseWithException_Worker::run()
{
    thread_ptr = std::make_unique<std::thread>(&do_work_that_could_throw_exception, id, std::move(m_promise));
    return thread_ptr ? true : false;  
}
