#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_

#include "thread_driver.h"
#include <string>

class ThreadManager
{
public:
    ThreadManager();

    // Tests
    void runTest_promiseMatrixCalc();

    // Helpers
    std::string & get_finish_state_as_string(int finish_state, std::string & s);
    std::string & get_matrix_as_string(std::vector<std::vector<int>> &matrix, std::string & s);

private:
    ThreadDriver thread_driver;
};

#endif