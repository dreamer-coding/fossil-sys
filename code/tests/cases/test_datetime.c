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
    int len = fossil_sys_time_format(&dt, buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", 1);
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

FOSSIL_TEST(c_test_time_now_edge_cases) {
    fossil_sys_time_datetime_t dt;
    fossil_sys_time_now(&dt);
    // Check for reasonable ranges
    ASSUME_ITS_TRUE(dt.year >= 1970); // Should not be before epoch
    ASSUME_ITS_TRUE(dt.month >= 1 && dt.month <= 12);
    ASSUME_ITS_TRUE(dt.day >= 1 && dt.day <= 31);
    ASSUME_ITS_TRUE(dt.hour >= 0 && dt.hour <= 23);
    ASSUME_ITS_TRUE(dt.minute >= 0 && dt.minute <= 59);
    ASSUME_ITS_TRUE(dt.second >= 0 && dt.second <= 60); // Allow leap second
}

FOSSIL_TEST(c_test_time_format_edge_cases) {
    fossil_sys_time_datetime_t dt = {9999, 12, 31, 23, 59, 59, 999999999};
    char buffer[10];
    int len = fossil_sys_time_format(&dt, buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", 1);
    ASSUME_ITS_TRUE(len < (int)sizeof(buffer)); // Buffer too small, should truncate or error
    fossil_sys_time_datetime_t dt2 = {2024, 2, 29, 0, 0, 0, 0};
    char buffer2[100];
    fossil_sys_time_format(&dt2, buffer2, sizeof(buffer2), "%Y-%m-%d", 1);
    ASSUME_ITS_TRUE(strcmp(buffer2, "2024-02-29") == 0); // Leap day format
}

FOSSIL_TEST(c_test_time_is_leap_year_edge_cases) {
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2000) == 1); // Divisible by 400
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(1900) == 0); // Divisible by 100, not 400
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2400) == 1); // Far future leap year
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2100) == 0); // Divisible by 100, not 400
}

FOSSIL_TEST(c_test_time_days_in_month_edge_cases) {
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 0) == 0); // Invalid month
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 13) == 0); // Invalid month
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 4) == 30); // April
    ASSUME_ITS_TRUE(fossil_sys_time_days_in_month(2024, 12) == 31); // December
}

FOSSIL_TEST(c_test_time_add_seconds_edge_cases) {
    fossil_sys_time_datetime_t dt = {2024, 2, 28, 23, 59, 59, 0};
    fossil_sys_time_add_seconds(&dt, 86400); // Add one day, should be Feb 29 (leap year)
    ASSUME_ITS_EQUAL_I32(dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt.month, 2);
    ASSUME_ITS_EQUAL_I32(dt.day, 29);
    dt = (fossil_sys_time_datetime_t){2023, 2, 28, 23, 59, 59, 0};
    fossil_sys_time_add_seconds(&dt, 86400); // Add one day, should be Mar 1 (not leap year)
    ASSUME_ITS_EQUAL_I32(dt.year, 2023);
    ASSUME_ITS_EQUAL_I32(dt.month, 3);
    ASSUME_ITS_EQUAL_I32(dt.day, 1);
}

FOSSIL_TEST(c_test_time_diff_seconds_edge_cases) {
    fossil_sys_time_datetime_t a = {2024, 1, 1, 0, 0, 0, 0};
    fossil_sys_time_datetime_t b = {2023, 1, 1, 0, 0, 0, 0};
    int64_t diff = fossil_sys_time_diff_seconds(&a, &b);
    ASSUME_ITS_TRUE(diff > 0); // Should be positive
    fossil_sys_time_datetime_t c = {2024, 1, 1, 0, 0, 0, 0};
    fossil_sys_time_datetime_t d = {2024, 1, 1, 0, 0, 0, 0};
    ASSUME_ITS_EQUAL_I64(fossil_sys_time_diff_seconds(&c, &d), 0); // Same time
}

FOSSIL_TEST(c_test_time_normalize_edge_cases) {
    fossil_sys_time_datetime_t dt = {2024, 12, 31, 23, 59, 120, 0};
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_EQUAL_I32(dt.year, 2025);
    ASSUME_ITS_EQUAL_I32(dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt.second, 0);
}

FOSSIL_TEST(c_test_time_validate_edge_cases) {
    fossil_sys_time_datetime_t invalid_month = {2024, 13, 1, 0, 0, 0, 0};
    fossil_sys_time_datetime_t invalid_day = {2024, 2, 30, 0, 0, 0, 0};
    fossil_sys_time_datetime_t invalid_hour = {2024, 1, 1, 24, 0, 0, 0};
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&invalid_month));
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&invalid_day));
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&invalid_hour));
}

FOSSIL_TEST(c_test_time_unix_conversion_edge_cases) {
    fossil_sys_time_datetime_t dt = {2038, 1, 19, 3, 14, 7, 0}; // 32-bit overflow
    int64_t ts = fossil_sys_time_to_unix(&dt);
    ASSUME_ITS_TRUE(ts > 0);
    fossil_sys_time_datetime_t dt2;
    fossil_sys_time_from_unix(ts, &dt2);
    ASSUME_ITS_EQUAL_I32(dt2.year, 2038);
    ASSUME_ITS_EQUAL_I32(dt2.month, 1);
    ASSUME_ITS_EQUAL_I32(dt2.day, 19);
}

FOSSIL_TEST(c_test_time_monotonic_ns_edge_cases) {
    uint64_t t1 = fossil_sys_time_monotonic_ns();
    fossil_sys_time_sleep_ns(0); // No sleep
    uint64_t t2 = fossil_sys_time_monotonic_ns();
    ASSUME_ITS_TRUE(t2 >= t1); // Should not go backwards
}

FOSSIL_TEST(c_test_time_span_edge_cases) {
    fossil_sys_time_span_t span = fossil_sys_time_span_from_seconds(-1); // Negative seconds
    ASSUME_ITS_TRUE(span.days <= 0);
    ASSUME_ITS_TRUE(span.hours <= 0);
    ASSUME_ITS_TRUE(span.minutes <= 0);
    ASSUME_ITS_TRUE(span.seconds <= 0);

    fossil_sys_time_span_t zero_span = fossil_sys_time_span_from_seconds(0);
    ASSUME_ITS_EQUAL_I64(zero_span.days, 0);
    ASSUME_ITS_EQUAL_I64(zero_span.hours, 0);
    ASSUME_ITS_EQUAL_I64(zero_span.minutes, 0);
    ASSUME_ITS_EQUAL_I64(zero_span.seconds, 0);
}

FOSSIL_TEST(c_test_time_add_span_edge_cases) {
    fossil_sys_time_datetime_t dt = {2024, 12, 31, 23, 59, 59, 0};
    fossil_sys_time_span_t span = {.days = 0, .hours = 0, .minutes = 0, .seconds = 2, .nanoseconds = 0};
    fossil_sys_time_add_span(&dt, &span);
    ASSUME_ITS_EQUAL_I32(dt.year, 2025);
    ASSUME_ITS_EQUAL_I32(dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt.hour, 0);
    ASSUME_ITS_EQUAL_I32(dt.minute, 0);
    ASSUME_ITS_EQUAL_I32(dt.second, 1);
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
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_now_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_is_leap_year_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_days_in_month_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_seconds_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_diff_seconds_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_normalize_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_validate_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_unix_conversion_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_monotonic_ns_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_span_edge_cases);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_span_edge_cases);

    FOSSIL_TEST_REGISTER(c_time_suite);
}
