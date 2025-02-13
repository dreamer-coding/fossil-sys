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
FOSSIL_TEST_SUITE(cpp_time_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_time_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_time_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_time_now) {
    fossil_sys_time_datetime_t dt;
    fossil_sys_time_now(&dt);
    ASSUME_ITS_TRUE(dt.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(dt.month >= 1 && dt.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(dt.day >= 1 && dt.day <= 31); // Ensure day is valid
}

FOSSIL_TEST_CASE(cpp_test_time_format) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 12, 0, 0, 0};
    char buffer[100];
    int len = fossil_sys_time_format(&dt, buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", 1);
    ASSUME_ITS_TRUE(len > 0); // Ensure formatting was successful
    ASSUME_ITS_TRUE(strcmp(buffer, "2024-01-01 12:00:00") == 0); // Ensure correct format
}

FOSSIL_TEST_CASE(cpp_test_time_add) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 12, 0, 0, 0};
    fossil_sys_time_add(&dt, 60, 1); // Add 60 seconds
    ASSUME_ITS_TRUE(dt.minute == 1); // Ensure minute is incremented
}

FOSSIL_TEST_CASE(cpp_test_time_subtract) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 12, 1, 0, 0};
    fossil_sys_time_subtract(&dt, 60, 1); // Subtract 60 seconds
    ASSUME_ITS_TRUE(dt.minute == 0); // Ensure minute is decremented
}

FOSSIL_TEST_CASE(cpp_test_time_to_unix) {
    fossil_sys_time_datetime_t dt = {1970, 1, 1, 0, 0, 0, 0};
    int64_t timestamp = fossil_sys_time_to_unix(&dt);
    ASSUME_ITS_TRUE(timestamp == 0); // Ensure correct UNIX timestamp
}

FOSSIL_TEST_CASE(cpp_test_time_from_unix) {
    fossil_sys_time_datetime_t dt;
    fossil_sys_time_from_unix(&dt, 0);
    ASSUME_ITS_TRUE(dt.year == 1970); // Ensure correct year
    ASSUME_ITS_TRUE(dt.month == 1); // Ensure correct month
    ASSUME_ITS_TRUE(dt.day == 1); // Ensure correct day
}

FOSSIL_TEST_CASE(cpp_test_time_is_leap_year) {
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2024) == 1); // 2024 is a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2023) == 0); // 2023 is not a leap year
}

FOSSIL_TEST_CASE(cpp_test_time_days_in_month) {
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 2) == 29); // February in a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2023, 2) == 28); // February in a non-leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 1) == 31); // January
}

FOSSIL_TEST_CASE(cpp_test_datetime_constructor) {
    fossil::sys::DateTime dt;
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(datetime.month >= 1 && datetime.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(datetime.day >= 1 && datetime.day <= 31); // Ensure day is valid
}

FOSSIL_TEST_CASE(cpp_test_datetime_format) {
    fossil::sys::DateTime dt({2024, 1, 1, 12, 0, 0, 0});
    std::string formatted = dt.format("%Y-%m-%d %H:%M:%S", true);
    ASSUME_ITS_TRUE(formatted == "2024-01-01 12:00:00"); // Ensure correct format
}

FOSSIL_TEST_CASE(cpp_test_datetime_add) {
    fossil::sys::DateTime dt({2024, 1, 1, 12, 0, 0, 0});
    dt.add(60, 1); // Add 60 seconds
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.minute == 1); // Ensure minute is incremented
}

FOSSIL_TEST_CASE(cpp_test_datetime_subtract) {
    fossil::sys::DateTime dt({2024, 1, 1, 12, 1, 0, 0});
    dt.subtract(60, 1); // Subtract 60 seconds
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.minute == 0); // Ensure minute is decremented
}

FOSSIL_TEST_CASE(cpp_test_datetime_to_unix) {
    fossil::sys::DateTime dt({1970, 1, 1, 0, 0, 0, 0});
    int64_t timestamp = dt.to_unix();
    ASSUME_ITS_TRUE(timestamp == 0); // Ensure correct UNIX timestamp
}

FOSSIL_TEST_CASE(cpp_test_datetime_from_unix) {
    fossil::sys::DateTime dt;
    dt.from_unix(0);
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.year == 1970); // Ensure correct year
    ASSUME_ITS_TRUE(datetime.month == 1); // Ensure correct month
    ASSUME_ITS_TRUE(datetime.day == 1); // Ensure correct day
}

FOSSIL_TEST_CASE(cpp_test_calendar_constructor) {
    fossil::sys::Calendar cal(2024, 2, 29);
    auto calendar = cal.get();
    ASSUME_ITS_TRUE(calendar.year == 2024); // Ensure correct year
    ASSUME_ITS_TRUE(calendar.month == 2); // Ensure correct month
    ASSUME_ITS_TRUE(calendar.day == 29); // Ensure correct day
}

FOSSIL_TEST_CASE(cpp_test_calendar_is_leap_year) {
    fossil::sys::Calendar cal(2024, 1, 1);
    ASSUME_ITS_TRUE(cal.is_leap_year() == true); // 2024 is a leap year
}

FOSSIL_TEST_CASE(cpp_test_calendar_days_in_month) {
    fossil::sys::Calendar cal(2024, 2, 1);
    ASSUME_ITS_TRUE(cal.days_in_month() == 29); // February in a leap year
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_time_tests) {
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_now);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_add);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_subtract);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_to_unix);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_from_unix);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_is_leap_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_days_in_month);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_constructor);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_add);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_subtract);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_to_unix);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_from_unix);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_constructor);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_is_leap_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_days_in_month);

    FOSSIL_TEST_REGISTER(cpp_time_suite);
}
