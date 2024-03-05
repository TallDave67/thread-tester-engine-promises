#ifndef _THREAD_WRAPPER_PROMISE_MATRIX_CALC_H_
#define _THREAD_WRAPPER_PROMISE_MATRIX_CALC_H_

#include "thread_wrapper.h"
#include <vector>
#include <future>

extern const std::size_t THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT;
extern const std::size_t THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT;
extern const int THREAD_WRAPPER_PROMISE_MATRIX_CALC_THREAD_COUNT;

extern const std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_A;
extern const std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_B;
extern std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_C;

typedef struct THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL
{
    THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL(std::size_t r, std::size_t c, int v);

    std::size_t row;
    std::size_t col;
    int val;
    THREAD_WRAPPER_RUN_DETAILS run_details;
    
} THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL;

class ThreadWrapper_promiseMatrixCalc_Worker : public ThreadWrapper
{
public:
    ThreadWrapper_promiseMatrixCalc_Worker(
        std::size_t row,
        std::size_t col,
        std::promise<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL>& promise);
    ThreadWrapper_promiseMatrixCalc_Worker(const ThreadWrapper_promiseMatrixCalc_Worker& other);
    ~ThreadWrapper_promiseMatrixCalc_Worker();

    bool run() override;

private:
    std::size_t m_row;
    std::size_t m_col;
    std::promise<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL>& m_promise;
};

#endif