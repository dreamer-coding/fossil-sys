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
FOSSIL_SUITE(cpp_time_suite);

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

FOSSIL_TEST(cpp_test_time_now) {
    fossil::sys::DateTime dt;
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(datetime.month >= 1 && datetime.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(datetime.day >= 1 && datetime.day <= 31); // Ensure day is valid
}

FOSSIL_TEST(cpp_test_time_format) {
    fossil::sys::DateTime dt({2024, 1, 1, 12, 0, 0, 0});
    std::string formatted = dt.format("%Y-%m-%d %H:%M:%S", "military");
    ASSUME_ITS_TRUE(formatted == "2024-01-01 12:00:00"); // Ensure correct format
}

FOSSIL_TEST(cpp_test_time_is_leap_year) {
    ASSUME_ITS_TRUE(fossil::sys::Calendar(2024, 1, 1).is_leap_year() == true); // 2024 is a leap year
    ASSUME_ITS_TRUE(fossil::sys::Calendar(2023, 1, 1).is_leap_year() == false); // 2023 is not a leap year
}

FOSSIL_TEST(cpp_test_time_days_in_month) {
    ASSUME_ITS_TRUE(fossil::sys::Calendar(2024, 2, 1).days_in_month() == 29); // February in a leap year
    ASSUME_ITS_TRUE(fossil::sys::Calendar(2023, 2, 1).days_in_month() == 28); // February in a non-leap year
    ASSUME_ITS_TRUE(fossil::sys::Calendar(2024, 1, 1).days_in_month() == 31); // January
}

FOSSIL_TEST(cpp_test_datetime_constructor) {
    fossil::sys::DateTime dt;
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.year > 0); // Ensure year is valid
    ASSUME_ITS_TRUE(datetime.month >= 1 && datetime.month <= 12); // Ensure month is valid
    ASSUME_ITS_TRUE(datetime.day >= 1 && datetime.day <= 31); // Ensure day is valid
}

FOSSIL_TEST(cpp_test_datetime_format) {
    fossil::sys::DateTime dt({2024, 1, 1, 12, 0, 0, 0});
    std::string formatted = dt.format("%Y-%m-%d %H:%M:%S", "military");
    ASSUME_ITS_TRUE(formatted == "2024-01-01 12:00:00"); // Ensure correct format
}

FOSSIL_TEST(cpp_test_calendar_constructor) {
    fossil::sys::Calendar cal(2024, 2, 29);
    auto calendar = cal.get();
    ASSUME_ITS_TRUE(calendar.year == 2024); // Ensure correct year
    ASSUME_ITS_TRUE(calendar.month == 2); // Ensure correct month
    ASSUME_ITS_TRUE(calendar.day == 29); // Ensure correct day
}

FOSSIL_TEST(cpp_test_calendar_is_leap_year) {
    fossil::sys::Calendar cal(2024, 1, 1);
    ASSUME_ITS_TRUE(cal.is_leap_year() == true); // 2024 is a leap year
}

FOSSIL_TEST(cpp_test_calendar_days_in_month) {
    fossil::sys::Calendar cal(2024, 2, 1);
    ASSUME_ITS_TRUE(cal.days_in_month() == 29); // February in a leap year
}

FOSSIL_TEST(cpp_test_datetime_add_seconds) {
    fossil::sys::DateTime dt({2024, 1, 1, 0, 0, 0, 0});
    dt.add_seconds(3600); // Add 1 hour
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.hour == 1);
    dt.add_seconds(-3600); // Subtract 1 hour
    datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.hour == 0);
}

FOSSIL_TEST(cpp_test_datetime_diff_seconds) {
    fossil::sys::DateTime dt1({2024, 1, 1, 0, 0, 0, 0});
    fossil::sys::DateTime dt2({2024, 1, 1, 1, 0, 0, 0});
    int64_t diff = dt2.diff_seconds(dt1);
    ASSUME_ITS_TRUE(diff == 3600);
}

FOSSIL_TEST(cpp_test_datetime_normalize_validate) {
    fossil::sys::DateTime dt({2024, 1, 32, 0, 0, 0, 0}); // Invalid day
    ASSUME_ITS_TRUE(!dt.validate());
    dt.normalize();
    ASSUME_ITS_TRUE(dt.validate());
}

FOSSIL_TEST(cpp_test_datetime_unix_conversion) {
    fossil::sys::DateTime dt({1970, 1, 1, 0, 0, 0, 0});
    int64_t unix_ts = dt.to_unix();
    ASSUME_ITS_TRUE(unix_ts == 0);
    dt.from_unix(3600);
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.hour == 1);
}

FOSSIL_TEST(cpp_test_datetime_add_span) {
    fossil::sys::DateTime dt({2024, 1, 1, 0, 0, 0, 0});
    fossil::sys::TimeSpan span(0, 2, 0, 0, 0); // 2 hours
    dt.add_span(span.get());
    auto datetime = dt.get();
    ASSUME_ITS_TRUE(datetime.hour == 2);
}

FOSSIL_TEST(cpp_test_timespan_constructors_and_conversion) {
    fossil::sys::TimeSpan span1(86400); // 1 day in seconds
    ASSUME_ITS_TRUE(span1.get().days == 1);
    fossil::sys::TimeSpan span2(1, 2, 3, 4, 5);
    ASSUME_ITS_TRUE(span2.get().days == 1 && span2.get().hours == 2);
    ASSUME_ITS_TRUE(span2.to_seconds() == (1*86400 + 2*3600 + 3*60 + 4));
}

FOSSIL_TEST(cpp_test_monotonic_ns_and_sleep_ns) {
    uint64_t t1 = fossil::sys::monotonic_ns();
    fossil::sys::sleep_ns(1000000); // Sleep 1 ms
    uint64_t t2 = fossil::sys::monotonic_ns();
    ASSUME_ITS_TRUE(t2 > t1);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_time_tests) {
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_now);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_is_leap_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_days_in_month);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_constructor);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_constructor);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_is_leap_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_days_in_month);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_add_seconds);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_diff_seconds);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_normalize_validate);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_unix_conversion);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_add_span);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_timespan_constructors_and_conversion);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_monotonic_ns_and_sleep_ns);

    FOSSIL_TEST_REGISTER(cpp_time_suite);
}
