#include "thread_wrapper_promiseMatrixCalc.h"

const std::size_t THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT = 3;
const std::size_t THREAD_WRAPPER_PROMISE_MATRIX_CALC_COL_COUNT = 3;
const int THREAD_WRAPPER_PROMISE_MATRIX_CALC_THREAD_COUNT = 9;

const std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_A = {
    {17, 37, 97},
    {26, 6, -6},
    {-8, 16, 64}
};

const std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_B = {
    {104, 119, -111},
    {15, 5, 95},
    {13, -13, 13}
};

std::vector<std::vector<int>> THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_C = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

void do_row_by_col_product(std::string id, std::size_t row, std::size_t col, std::promise<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL> promise)
{
    int val = 0;
    THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL value {row, col, val};
    value.run_details.id = id;
    value.run_details.timer.start();

    for(std::size_t j = 0; j < THREAD_WRAPPER_PROMISE_MATRIX_CALC_ROW_COUNT; j++)
    {
        val += THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_A[row][j] * THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_B[j][col];
    }

    value.val = val;
    value.run_details.finish_state = THREAD_WRAPPER_RUN_SUCCESS;
    value.run_details.timer.stop();
    promise.set_value(value); // Notify future
}

THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL::THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL(std::size_t r, std::size_t c, int v)
    : row{r}, col{c}, val{v}
{
}

ThreadWrapper_promiseMatrixCalc_Worker::ThreadWrapper_promiseMatrixCalc_Worker(
    std::size_t row,
    std::size_t col,
    std::promise<THREAD_WRAPPER_PROMISE_MATRIX_CALC_MATRIX_CELL>& promise)
        : m_row{row}, m_col{col}, m_promise{promise}
{
        id = "promiseMatrixCalc_Worker_";
        id += std::to_string(m_row);
        id += "_";
        id += std::to_string(m_col);
}

ThreadWrapper_promiseMatrixCalc_Worker::ThreadWrapper_promiseMatrixCalc_Worker(const ThreadWrapper_promiseMatrixCalc_Worker& other)
    : ThreadWrapper(other), m_row{other.m_row}, m_col{other.m_col}, m_promise{other.m_promise}
{
}

ThreadWrapper_promiseMatrixCalc_Worker::~ThreadWrapper_promiseMatrixCalc_Worker()
{
}

bool ThreadWrapper_promiseMatrixCalc_Worker::run()
{
    thread_ptr = std::make_unique<std::thread>(&do_row_by_col_product, id, m_row, m_col, std::move(m_promise));
    return thread_ptr ? true : false;  
}
