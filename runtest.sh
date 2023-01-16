#!/bin/bash

if [[ $1 = "all" ]]
then
	make retest && ./tests --gtest_also_run_disabled_tests
elif [[ $1 = "main" ]]
then
	clang++ -std=c++98 -I include main.cpp && ./a.out
else
	make retest && valgrind ./tests
fi
