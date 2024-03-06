#!/bin/sh

./build/thread-tester-engine-promises 50 > tests/output/runTest_promiseMatrixCalc_output.txt
./build/thread-tester-engine-promises 49 > tests/output/runTest_promiseWithException_output.txt
