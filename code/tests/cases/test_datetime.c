/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/test/framework.h>

#include "fossil/sys/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(c_time_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_time_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_time_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_time_now) {
    fossil_sys_time_datetime_t dt;
    fossil_sys_time_now(&dt);
    ASSUME_ITS_TRUE(dt.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(dt.month >= 1 && dt.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(dt.day >= 1 && dt.day <= 31); // Ensure day is valid
}

FOSSIL_TEST_CASE(c_test_time_format) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 12, 0, 0, 0};
    char buffer[100];
    int len = fossil_sys_time_format(&dt, buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", 1);
    ASSUME_ITS_TRUE(len > 0); // Ensure formatting was successful
    ASSUME_ITS_TRUE(strcmp(buffer, "2024-01-01 12:00:00") == 0); // Ensure correct format
}

FOSSIL_TEST_CASE(c_test_time_is_leap_year) {
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2024) == 1); // 2024 is a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2023) == 0); // 2023 is not a leap year
}

FOSSIL_TEST_CASE(c_test_time_days_in_month) {
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 2) == 29); // February in a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2023, 2) == 28); // February in a non-leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 1) == 31); // January
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_time_tests) {
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_now);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_is_leap_year);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_days_in_month);

    FOSSIL_TEST_REGISTER(c_time_suite);
}
