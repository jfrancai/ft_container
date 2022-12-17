#!/bin/bash

make retest && ./tests --gtest_also_run_disabled_tests
