#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <vector>

class ThreadWrapper;

class ThreadDriver
{
public:
    ThreadDriver();
    ~ThreadDriver();

    void reserve(std::size_t num_threads);
    void add_thread_wrapper(ThreadWrapper*);
    ThreadWrapper* get_thread_wrapper(std::size_t index);
    void run();

private:
    std::vector<ThreadWrapper*> threads;
};

#endif
