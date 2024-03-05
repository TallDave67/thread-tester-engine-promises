#include "thread_manager.h"
#include "event_logger.h"
#include "thread_wrapper.h"
#include "thread_wrapper_promiseMatrixCalc.h"
#include <sstream>

ThreadManager::ThreadManager()
{
}

// Tests
void ThreadManager::runTest_promiseMatrixCalc()
{
    // log the event
    std::string event;
    event = "{\"event_type\":\"run\", \"event\":\"start\", \"object\":\"test\", \"id\":\"promiseMatrixCalc\"}";
    pg_event_logger->send_event(event);

    // create the promises
    std::vector<std::vector<std::promise<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL>>> promises;
    for(std::size_t i = 0; i < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; i++)
    {
        promises.push_back({});
        for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT; j++)
        {
            promises[i].push_back({});
        }
    }

    // create the futures, one per promise
    std::vector<std::vector<std::future<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL>>> futures;
    for(std::size_t i = 0; i < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; i++)
    {
        futures.push_back({});
        for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT; j++)
        {
            futures[i].push_back(promises[i][j].get_future());
        }
    }

    // create the worker_thread_wrappers
    std::vector<std::vector<ThreadWrapper_promiseMatrixCalc_Worker>> worker_thread_wrappers;
    for(std::size_t i = 0; i < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; i++)
    {
        worker_thread_wrappers.push_back({});
        for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT; j++)
        {
            worker_thread_wrappers[i].push_back({
                i,
                j,
                promises[i][j]});
        }
    }

    // add our thread wrappers to our thread driver
    thread_driver.reserve(THREAD_WRAPPER_PROMISE_MATRIX_CALC_THREAD_COUNT);
    for(std::size_t i = 0; i < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; i++)
    {
        for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT; j++)
        {
            thread_driver.add_thread_wrapper(&(worker_thread_wrappers[i][j]));
        }
    }

    // tell the driver to run the threads
    thread_driver.run();

    // wait for the futures
    for(std::size_t i = 0; i < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; i++)
    {
        for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT; j++)
        {
            const auto & val_info = futures[i][j].get();
            THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_C[val_info.row][val_info.col] = val_info.val;

            // log the events
            {
                std::stringstream ss;
                ss << "{\"event_type\":\"run\", \"event\":\"finish\", \"object\":\"thread_wrapper\", \"id\":\"" << val_info.run_details.id <<  "\", \"duration_in_nanoseconds\":" << val_info.run_details.timer.duration_in_nanoseconds() << "}";
                std::string event = ss.str();
                pg_event_logger->send_event(event);
            }
            {
                // log the event
                std::stringstream ss;
                std::string finish_state_as_string;
                ss << "{\"event_type\":\"run\", \"event\":\"finish\", \"object\":\"thread_wrapper\", \"id\":" << val_info.run_details.id << ", \"state\":\"" << get_finish_state_as_string(val_info.run_details.finish_state, finish_state_as_string) << "\"}";        
                std::string event = ss.str();
                pg_event_logger->send_event(event);
            }
        }
    }

    // log the events
    {
        std::string event;
        event = "{\"event_type\":\"run\", \"event\":\"finish\", \"object\":\"test\", \"id\":\"promiseMatrixCalc\"}";
        pg_event_logger->send_event(event);
    }
    {
        // Get the matrix output
        std::string output;
        std::string event;
        event = "{\"event_type\":\"output\", \"event\":\"";
        event += get_matrix_as_string(THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_C, output);
        event += "\", \"object\":\"test\", \"id\":\"promiseMatrixCalc\"}";
        pg_event_logger->send_event(event);
    }
}

// Helpers
std::string & ThreadManager::get_finish_state_as_string(int finish_state, std::string & s)
{
    switch(finish_state)
    {
    case THREAD_WRAPPER_RUN_ABORT:
        s = "ABORT";
        break;
    case THREAD_WRAPPER_RUN_FAILURE:
        s = "FAILURE";
        break;
    case THREAD_WRAPPER_RUN_NOOP:
        s = "NOOP";
        break;
    case THREAD_WRAPPER_RUN_SUCCESS:
        s = "SUCCESS";
        break;
    }
    return s;
}

std::string & ThreadManager::get_matrix_as_string(std::vector<std::vector<int>> &matrix, std::string & s)
{
    s = "[";
    bool first_row = true;
    for(std::size_t i = 0; i < matrix.size(); i++)
    {
        if(first_row)
        {
            first_row = false;
        }
        else
        {
            s += ",";
        }
        s += "[";
        //
        bool first_col = true;
        for(std::size_t j = 0; j < matrix[i].size(); j++)
        {
            if(first_col)
            {
                first_col = false;
            }
            else
            {
                s += ",";
            }
            s += std::to_string(matrix[i][j]);

        }
        s += "]";
    }
    s += "]";
    return s;
}
