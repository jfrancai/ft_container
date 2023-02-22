#!/bin/bash

if [[ $1 = "all" ]]
then
	make retest && ./tests --gtest_also_run_disabled_tests
elif [[ $1 = "main" ]]
then
	clang++ -std=c++98 -Wall -Werror -Wextra -I include main.cpp && ./a.out speed
else
	make retest && ./tests
fi
