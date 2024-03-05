#include "thread_wrapper.h"

THREAD_WRAPPER_RUN_DETAILS::THREAD_WRAPPER_RUN_DETAILS()
    : finish_state(THREAD_WRAPPER_RUN_NOOP)
{

}

ThreadWrapper::ThreadWrapper()
    : thread_ptr(nullptr)
{
}

ThreadWrapper::ThreadWrapper(const ThreadWrapper& other)
{
    id = other.id;
}

ThreadWrapper::~ThreadWrapper()
{
}

bool ThreadWrapper::run()
{
    return false;
}

void ThreadWrapper::wait()
{
    if(thread_ptr) thread_ptr->join();
}

std::string& ThreadWrapper::get_id()
{
    return id;
}

std::thread::id ThreadWrapper::get_native_id()
{
    std::thread::id tid;
    if(thread_ptr) tid = thread_ptr->get_id();
    return tid;
}

std::thread::native_handle_type ThreadWrapper::get_native_handle()
{
    std::thread::native_handle_type hid;
    if(thread_ptr) hid = thread_ptr->native_handle();
    return hid;
}
