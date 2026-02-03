/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/pizza/framework.h>

#include "fossil/sys/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_time_suite);

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

FOSSIL_TEST(c_test_time_now) {
    fossil_sys_time_datetime_t dt;
    fossil_sys_time_now(&dt);
    ASSUME_ITS_TRUE(dt.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(dt.month >= 1 && dt.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(dt.day >= 1 && dt.day <= 31); // Ensure day is valid
}

FOSSIL_TEST(c_test_time_format) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 12, 0, 0, 0};
    char buffer[100];
    int len = fossil_sys_time_format(&dt, buffer, sizeof(buffer), "military");
    ASSUME_ITS_TRUE(len > 0); // Ensure formatting was successful
    ASSUME_ITS_TRUE(strcmp(buffer, "2024-01-01 12:00:00") == 0); // Ensure correct format
}

FOSSIL_TEST(c_test_time_is_leap_year) {
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2024) == 1); // 2024 is a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2023) == 0); // 2023 is not a leap year
}

FOSSIL_TEST(c_test_time_days_in_month) {
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 2) == 29); // February in a leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2023, 2) == 28); // February in a non-leap year
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 1) == 31); // January
}

FOSSIL_TEST(c_test_time_add_seconds) {
    fossil_sys_time_datetime_t dt = {2024, 12, 31, 23, 59, 50, 0};
    fossil_sys_time_add_seconds(&dt, 15); // Should roll into next year
    ASSUME_ITS_EQUAL_I32(dt.year, 2025);
    ASSUME_ITS_EQUAL_I32(dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt.second, 5);
}

FOSSIL_TEST(c_test_time_diff_seconds) {
    fossil_sys_time_datetime_t a = {2024, 1, 1, 0, 0, 10, 0};
    fossil_sys_time_datetime_t b = {2024, 1, 1, 0, 0, 0, 0};
    int64_t diff = fossil_sys_time_diff_seconds(&a, &b);
    ASSUME_ITS_EQUAL_I64(diff, 10);
}

FOSSIL_TEST(c_test_time_normalize) {
    fossil_sys_time_datetime_t dt = {2024, 1, 31, 23, 59, 70, 0};
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_EQUAL_I32(dt.month, 2);   // Rolled into February
    ASSUME_ITS_EQUAL_I32(dt.day, 1);     // Day overflow carried
    ASSUME_ITS_EQUAL_I32(dt.second, 10); // Seconds normalized
}

FOSSIL_TEST(c_test_time_validate) {
    fossil_sys_time_datetime_t good = {2024, 2, 29, 12, 30, 45, 0};
    fossil_sys_time_datetime_t bad = {2023, 2, 29, 12, 30, 45, 0}; // Invalid (not leap year)
    ASSUME_ITS_TRUE(fossil_sys_time_validate(&good));
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&bad));
}

FOSSIL_TEST(c_test_time_unix_conversion) {
    fossil_sys_time_datetime_t dt = {1970, 1, 1, 0, 0, 0, 0};
    int64_t ts = fossil_sys_time_to_unix(&dt);
    ASSUME_ITS_EQUAL_I64(ts, 0); // Epoch start
    fossil_sys_time_datetime_t dt2;
    fossil_sys_time_from_unix(0, &dt2);
    ASSUME_ITS_EQUAL_I32(dt2.year, 1970);
    ASSUME_ITS_EQUAL_I32(dt2.month, 1);
    ASSUME_ITS_EQUAL_I32(dt2.day, 1);
}

FOSSIL_TEST(c_test_time_monotonic_ns) {
    uint64_t t1 = fossil_sys_time_monotonic_ns();
    fossil_sys_time_sleep_ns(5000000ULL); // sleep 5ms
    uint64_t t2 = fossil_sys_time_monotonic_ns();
    ASSUME_ITS_TRUE(t2 > t1); // Monotonic time should move forward
}

FOSSIL_TEST(c_test_time_span) {
    fossil_sys_time_span_t span = fossil_sys_time_span_from_seconds(90061); // 1d 1h 1m 1s
    ASSUME_ITS_EQUAL_I64(span.days, 1);
    ASSUME_ITS_EQUAL_I64(span.hours, 1);
    ASSUME_ITS_EQUAL_I64(span.minutes, 1);
    ASSUME_ITS_EQUAL_I64(span.seconds, 1);

    int64_t total = fossil_sys_time_span_to_seconds(&span);
    ASSUME_ITS_EQUAL_I64(total, 90061);
}

FOSSIL_TEST(c_test_time_add_span) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 0, 0, 0, 0};
    fossil_sys_time_span_t span = {.days = 1, .hours = 2, .minutes = 30, .seconds = 15, .nanoseconds = 0};
    fossil_sys_time_add_span(&dt, &span);
    ASSUME_ITS_EQUAL_I32(dt.day, 2);
    ASSUME_ITS_EQUAL_I32(dt.hour, 2);
    ASSUME_ITS_EQUAL_I32(dt.minute, 30);
    ASSUME_ITS_EQUAL_I32(dt.second, 15);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_time_tests) {
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_now);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_is_leap_year);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_days_in_month);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_seconds);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_diff_seconds);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_normalize);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_validate);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_unix_conversion);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_monotonic_ns);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_span);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_span);

    FOSSIL_TEST_REGISTER(c_time_suite);
}
