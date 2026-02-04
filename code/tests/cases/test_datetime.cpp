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

// --- Date/Time API Tests ---

// ** Test Calendar leap year and days in month **
FOSSIL_TEST(cpp_test_calendar_leap_year_and_days_in_month) {
    fossil::sys::Calendar cal1(2000, 2, 1);
    ASSUME_ITS_TRUE(cal1.is_leap_year());
    ASSUME_ITS_EQUAL_I32(cal1.days_in_month(), 29);

    fossil::sys::Calendar cal2(1900, 2, 1);
    ASSUME_ITS_FALSE(cal2.is_leap_year());
    ASSUME_ITS_EQUAL_I32(cal2.days_in_month(), 28);

    fossil::sys::Calendar cal3(2023, 4, 1);
    ASSUME_ITS_EQUAL_I32(cal3.days_in_month(), 30);

    fossil::sys::Calendar cal4(2023, 1, 1);
    ASSUME_ITS_EQUAL_I32(cal4.days_in_month(), 31);
}

// ** Test TimeSpan from_seconds and to_seconds **
FOSSIL_TEST(cpp_test_timespan_from_and_to_seconds) {
    fossil::sys::TimeSpan span(90061); // 1 day, 1 hour, 1 minute, 1 second
    ASSUME_ITS_EQUAL_I64(span.span.days, 1);
    ASSUME_ITS_EQUAL_I64(span.span.hours, 1);
    ASSUME_ITS_EQUAL_I64(span.span.minutes, 1);
    ASSUME_ITS_EQUAL_I64(span.span.seconds, 1);
    ASSUME_ITS_EQUAL_I64(span.to_seconds(), 90061);

    auto span2 = fossil::sys::TimeSpan::from_seconds(3600);
    ASSUME_ITS_EQUAL_I64(span2.to_seconds(), 3600);
}

// ** Test DateTime validation **
FOSSIL_TEST(cpp_test_datetime_validate) {
    fossil::sys::DateTime dt({2023, 2, 28, 12, 0, 0, 0});
    ASSUME_ITS_TRUE(dt.is_valid());
    dt.dt.day = 29;
    ASSUME_ITS_FALSE(dt.is_valid());
    dt.dt.year = 2024;
    ASSUME_ITS_TRUE(dt.is_valid());
    dt.dt.month = 13;
    ASSUME_ITS_FALSE(dt.is_valid());
    dt.dt.month = 2; dt.dt.day = 30;
    ASSUME_ITS_FALSE(dt.is_valid());
}

// ** Test DateTime to_unix and from_unix **
FOSSIL_TEST(cpp_test_datetime_unix_conversion) {
    fossil::sys::DateTime dt({1970, 1, 1, 0, 0, 0, 0});
    int64_t ts = dt.to_unix();
    ASSUME_ITS_EQUAL_I64(ts, 0);

    fossil::sys::DateTime dt2({2024, 1, 1, 0, 0, 0, 0});
    ts = dt2.to_unix();
    fossil::sys::DateTime dt3 = fossil::sys::DateTime::from_unix(ts);
    ASSUME_ITS_EQUAL_I32(dt3.dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt3.dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt3.dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt3.dt.hour, 0);
    ASSUME_ITS_EQUAL_I32(dt3.dt.minute, 0);
    ASSUME_ITS_EQUAL_I32(dt3.dt.second, 0);
}

// ** Test DateTime add_seconds and normalize **
FOSSIL_TEST(cpp_test_datetime_add_seconds_and_normalize) {
    fossil::sys::DateTime dt({2023, 12, 31, 23, 59, 50, 0});
    dt.add_seconds(15);
    ASSUME_ITS_EQUAL_I32(dt.dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt.dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt.dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt.dt.hour, 0);
    ASSUME_ITS_EQUAL_I32(dt.dt.minute, 0);
    ASSUME_ITS_EQUAL_I32(dt.dt.second, 5);

    dt = fossil::sys::DateTime({2024, 1, 1, 0, 0, -10, 0});
    dt.normalize();
    ASSUME_ITS_EQUAL_I32(dt.dt.year, 2023);
    ASSUME_ITS_EQUAL_I32(dt.dt.month, 12);
    ASSUME_ITS_EQUAL_I32(dt.dt.day, 31);
    ASSUME_ITS_EQUAL_I32(dt.dt.hour, 23);
    ASSUME_ITS_EQUAL_I32(dt.dt.minute, 59);
    ASSUME_ITS_EQUAL_I32(dt.dt.second, 50);
}

// ** Test DateTime diff_seconds **
FOSSIL_TEST(cpp_test_datetime_diff_seconds) {
    fossil::sys::DateTime a({2024, 1, 2, 0, 0, 0, 0});
    fossil::sys::DateTime b({2024, 1, 1, 0, 0, 0, 0});
    int64_t diff = a.diff_seconds(b);
    ASSUME_ITS_EQUAL_I64(diff, 86400);
    diff = b.diff_seconds(a);
    ASSUME_ITS_EQUAL_I64(diff, -86400);
}

// ** Test DateTime add_span **
FOSSIL_TEST(cpp_test_datetime_add_span) {
    fossil::sys::DateTime dt({2024, 2, 28, 23, 0, 0, 0});
    fossil::sys::TimeSpan span;
    span.span.days = 1;
    span.span.hours = 2;
    dt.add_span(span);
    ASSUME_ITS_EQUAL_I32(dt.dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt.dt.month, 2);
    ASSUME_ITS_EQUAL_I32(dt.dt.day, 29);
    ASSUME_ITS_EQUAL_I32(dt.dt.hour, 1);
}

// ** Test DateTime format **
FOSSIL_TEST(cpp_test_datetime_format) {
    fossil::sys::DateTime dt({2024, 3, 14, 15, 9, 26, 0});
    const char *formats[] = {
        nullptr, "human", "short", "date", "time", "time-sec", "military", "iso", "rfc2822"
    };
    for (size_t i = 0; i < sizeof(formats)/sizeof(formats[0]); ++i) {
        std::string result = dt.format(formats[i] ? formats[i] : "");
        ASSUME_ITS_TRUE(!result.empty());
    }
}

FOSSIL_TEST(cpp_test_datetime_get_season) {
    fossil::sys::DateTime dt({2024, 3, 21, 0, 0, 0, 0});
    ASSUME_ITS_EQUAL_I32(dt.season(true), FOSSIL_SYS_SEASON_SPRING);
    dt.dt.month = 7;
    ASSUME_ITS_EQUAL_I32(dt.season(true), FOSSIL_SYS_SEASON_SUMMER);
    dt.dt.month = 12;
    ASSUME_ITS_EQUAL_I32(dt.season(true), FOSSIL_SYS_SEASON_WINTER);
}

FOSSIL_TEST(cpp_test_datetime_get_holiday) {
    fossil::sys::DateTime dt({2024, 1, 1, 0, 0, 0, 0});
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_NEW_YEAR);
    dt.dt.month = 12; dt.dt.day = 25;
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_CHRISTMAS);
    dt.dt.month = 7; dt.dt.day = 4;
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_INDEPENDENCE);
    dt.dt.month = 2; dt.dt.day = 14;
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_VALENTINES);
    dt.dt.month = 3; dt.dt.day = 17;
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_ST_PATRICKS);
    dt.dt.month = 6; dt.dt.day = 15;
    ASSUME_ITS_EQUAL_I32(dt.holiday(), FOSSIL_SYS_HOLIDAY_NONE);
}

FOSSIL_TEST(cpp_test_datetime_is_weekend) {
    fossil::sys::DateTime dt({2024, 3, 16, 0, 0, 0, 0}); // Saturday
    ASSUME_ITS_TRUE(dt.is_weekend());
    dt.dt.day = 17; // Sunday
    ASSUME_ITS_TRUE(dt.is_weekend());
    dt.dt.day = 18; // Monday
    ASSUME_ITS_FALSE(dt.is_weekend());
}

FOSSIL_TEST(cpp_test_datetime_get_quarter) {
    fossil::sys::DateTime dt({2024, 1, 1, 0, 0, 0, 0});
    ASSUME_ITS_EQUAL_I32(dt.quarter(), 1);
    dt.dt.month = 4;
    ASSUME_ITS_EQUAL_I32(dt.quarter(), 2);
    dt.dt.month = 7;
    ASSUME_ITS_EQUAL_I32(dt.quarter(), 3);
    dt.dt.month = 10;
    ASSUME_ITS_EQUAL_I32(dt.quarter(), 4);
}

FOSSIL_TEST(cpp_test_datetime_format_smart) {
    fossil::sys::DateTime now({2024, 3, 14, 15, 0, 0, 0});
    fossil::sys::DateTime dt = now;
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
}

FOSSIL_TEST(cpp_test_datetime_format_relative) {
    fossil::sys::DateTime now({2024, 3, 14, 15, 0, 0, 0});
    fossil::sys::DateTime dt = now;
    std::string result = dt.format_relative(now);
    ASSUME_ITS_TRUE(!result.empty());
    dt.dt.minute -= 5;
    dt.normalize();
    result = dt.format_relative(now);
    ASSUME_ITS_TRUE(!result.empty());
}

FOSSIL_TEST(cpp_test_datetime_matches_search) {
    fossil::sys::DateTime now({2024, 3, 14, 15, 0, 0, 0});
    fossil::sys::DateTime dt = now;
    ASSUME_ITS_TRUE(dt.matches(now, "today"));
    dt.dt.day -= 1;
    dt.normalize();
    ASSUME_ITS_FALSE(dt.matches(now, "today"));
}

// Additional tests for format_smart

FOSSIL_TEST(cpp_test_datetime_format_smart_same_day) {
    fossil::sys::DateTime now({2024, 5, 10, 14, 30, 0, 0});
    fossil::sys::DateTime dt({2024, 5, 10, 9, 15, 0, 0});
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
}

FOSSIL_TEST(cpp_test_datetime_format_smart_yesterday) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0});
    fossil::sys::DateTime dt({2024, 5, 9, 22, 45, 0, 0});
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
    ASSUME_ITS_TRUE(result.find("Yesterday") != std::string::npos);
}

FOSSIL_TEST(cpp_test_datetime_format_smart_tomorrow) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0});
    fossil::sys::DateTime dt({2024, 5, 11, 8, 0, 0, 0});
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
    ASSUME_ITS_TRUE(result.find("Tomorrow") != std::string::npos);
}

FOSSIL_TEST(cpp_test_datetime_format_smart_same_week) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0}); // Friday
    fossil::sys::DateTime dt({2024, 5, 8, 16, 0, 0, 0});   // Wednesday
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
    ASSUME_ITS_TRUE(result.find("Wednesday") != std::string::npos);
}

FOSSIL_TEST(cpp_test_datetime_format_smart_same_year) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0});
    fossil::sys::DateTime dt({2024, 2, 1, 12, 0, 0, 0});
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
}

FOSSIL_TEST(cpp_test_datetime_format_smart_different_year) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0});
    fossil::sys::DateTime dt({2023, 12, 25, 7, 0, 0, 0});
    std::string result = dt.format_smart(now);
    ASSUME_ITS_TRUE(!result.empty());
}

FOSSIL_TEST(cpp_test_datetime_format_smart_buffer_too_small) {
    fossil::sys::DateTime now({2024, 5, 10, 10, 0, 0, 0});
    fossil::sys::DateTime dt({2024, 5, 10, 10, 0, 0, 0});
    char buf[2];
    int n = fossil_sys_time_format_smart(&dt.dt, &now.dt, buf, sizeof(buf));
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(cpp_test_datetime_format_human) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("human");
    ASSUME_ITS_TRUE(result.find("January") != std::string::npos);
    ASSUME_ITS_TRUE(result.find("31") != std::string::npos);
    ASSUME_ITS_TRUE(result.find("03:45 PM") != std::string::npos);
}

FOSSIL_TEST(cpp_test_datetime_format_short) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("short");
    ASSUME_ITS_TRUE(result.find("01/31/2026") != std::string::npos);
    ASSUME_ITS_TRUE(result.find("03:45 PM") != std::string::npos);
}

FOSSIL_TEST(cpp_test_datetime_format_date) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("date");
    ASSUME_ITS_TRUE(result == "01/31/2026");
}

FOSSIL_TEST(cpp_test_datetime_format_time) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("time");
    ASSUME_ITS_TRUE(result == "03:45 PM");
}

FOSSIL_TEST(cpp_test_datetime_format_time_sec) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("time-sec");
    ASSUME_ITS_TRUE(result == "03:45:12 PM");
}

FOSSIL_TEST(cpp_test_datetime_format_military) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("military");
    ASSUME_ITS_TRUE(result == "15:45");
}

FOSSIL_TEST(cpp_test_time_format_iso) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("iso");
    ASSUME_ITS_TRUE(result.find("2026-01-31T15:45:12") != std::string::npos);
}

FOSSIL_TEST(cpp_test_time_format_rfc2822) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("rfc2822");
    ASSUME_ITS_TRUE(result.find("Sat, 31 Jan 2026 15:45:12") != std::string::npos);
}

FOSSIL_TEST(cpp_test_time_format_null_format_id) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("");
    ASSUME_ITS_TRUE(result.find("January") != std::string::npos);
}

FOSSIL_TEST(cpp_test_time_format_invalid_format_id) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    std::string result = dt.format("%Y/%m/%d %H-%M-%S");
    ASSUME_ITS_TRUE(result.find("2026/01/31") != std::string::npos);
    ASSUME_ITS_TRUE(result.find("15-45-12") != std::string::npos);
}

FOSSIL_TEST(cpp_test_time_format_buffer_too_small) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    char buf[2];
    int n = fossil_sys_time_format(&dt.dt, buf, sizeof(buf), "human");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(cpp_test_time_format_null_dt) {
    char buf[32];
    int n = fossil_sys_time_format(nullptr, buf, sizeof(buf), "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(cpp_test_time_format_null_buffer) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    int n = fossil_sys_time_format(&dt.dt, nullptr, 32, "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(cpp_test_time_format_zero_buffer_size) {
    fossil::sys::DateTime dt({2026, 1, 31, 15, 45, 12, 0});
    char buf[32];
    int n = fossil_sys_time_format(&dt.dt, buf, 0, "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(cpp_test_time_search_today) {
    fossil::sys::DateTime now({2024, 6, 1, 12, 0, 0, 0});
    fossil::sys::DateTime dt = now;
    ASSUME_ITS_TRUE(dt.matches(now, "today"));
    dt.dt.day = 2;
    dt.normalize();
    ASSUME_ITS_FALSE(dt.matches(now, "today"));
}

FOSSIL_TEST(cpp_test_time_search_weekend_and_weekday) {
    fossil::sys::DateTime dt({2024, 6, 1, 0, 0, 0, 0}); // Saturday
    fossil::sys::DateTime now = dt;
    ASSUME_ITS_TRUE(dt.matches(now, "weekend"));
    ASSUME_ITS_FALSE(dt.matches(now, "weekday"));
    dt.dt.day = 3; // Monday
    dt.normalize();
    ASSUME_ITS_FALSE(dt.matches(now, "weekend"));
    ASSUME_ITS_TRUE(dt.matches(now, "weekday"));
}

FOSSIL_TEST(cpp_test_time_search_holiday) {
    fossil::sys::DateTime dt({2024, 12, 25, 0, 0, 0, 0}); // Christmas
    fossil::sys::DateTime now = dt;
    ASSUME_ITS_TRUE(dt.matches(now, "holiday"));
    dt.dt.month = 6; dt.dt.day = 15; // Not a holiday
    ASSUME_ITS_FALSE(dt.matches(now, "holiday"));
}

FOSSIL_TEST(cpp_test_time_search_quarters) {
    fossil::sys::DateTime dt({2024, 2, 1, 0, 0, 0, 0});
    fossil::sys::DateTime now = dt;
    ASSUME_ITS_TRUE(dt.matches(now, "Q1"));
    ASSUME_ITS_FALSE(dt.matches(now, "Q2"));
    dt.dt.month = 5;
    ASSUME_ITS_TRUE(dt.matches(now, "Q2"));
    dt.dt.month = 8;
    ASSUME_ITS_TRUE(dt.matches(now, "Q3"));
    dt.dt.month = 11;
    ASSUME_ITS_TRUE(dt.matches(now, "Q4"));
}

FOSSIL_TEST(cpp_test_time_search_comparisons) {
    fossil::sys::DateTime dt({2024, 6, 15, 0, 0, 0, 0});
    fossil::sys::DateTime now = dt;
    ASSUME_ITS_TRUE(dt.matches(now, "> 2024-06-01"));
    ASSUME_ITS_TRUE(dt.matches(now, ">= 2024-06-15"));
    ASSUME_ITS_FALSE(dt.matches(now, "> 2024-06-15"));
    ASSUME_ITS_TRUE(dt.matches(now, "< 2024-07-01"));
    ASSUME_ITS_TRUE(dt.matches(now, "<= 2024-06-15"));
    ASSUME_ITS_FALSE(dt.matches(now, "< 2024-06-15"));
    ASSUME_ITS_TRUE(dt.matches(now, "= 2024-06-15"));
    ASSUME_ITS_FALSE(dt.matches(now, "= 2024-06-14"));
    ASSUME_ITS_TRUE(dt.matches(now, "!= 2024-06-14"));
    ASSUME_ITS_FALSE(dt.matches(now, "!= 2024-06-15"));
}

FOSSIL_TEST(cpp_test_time_search_whitespace_and_invalid) {
    fossil::sys::DateTime dt({2024, 6, 15, 0, 0, 0, 0});
    fossil::sys::DateTime now = dt;
    ASSUME_ITS_TRUE(dt.matches(now, "   today"));
    ASSUME_ITS_TRUE(dt.matches(now, "   >=   2024-06-15"));
    ASSUME_ITS_FALSE(dt.matches(now, "   <   2024-06-15"));
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, &now.dt, ""), 0);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(nullptr, &now.dt, "today"), -1);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, nullptr, "today"), -1);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, &now.dt, nullptr), -1);
}

FOSSIL_TEST(cpp_test_time_search_invalid_operator_and_format) {
    fossil::sys::DateTime dt({2024, 6, 15, 0, 0, 0, 0});
    fossil::sys::DateTime now = dt;
    // Invalid operator
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, &now.dt, ">> 2024-06-15"), 0);
    // Invalid date format
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, &now.dt, "> 2024/06/15"), 0);
    // Unknown keyword
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt.dt, &now.dt, "nonsense"), 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_time_tests) {
    // --- Date/Time API Tests ---
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_calendar_leap_year_and_days_in_month);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_timespan_from_and_to_seconds);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_validate);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_unix_conversion);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_add_seconds_and_normalize);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_diff_seconds);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_add_span);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_get_season);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_get_holiday);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_is_weekend);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_get_quarter);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_relative);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_matches_search);

    // tests for fossil_sys_time_format_smart
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_same_day);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_yesterday);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_tomorrow);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_same_week);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_same_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_different_year);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_smart_buffer_too_small);

    // format tests
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_human);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_short);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_date);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_time);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_time_sec);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_datetime_format_military);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_iso);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_rfc2822);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_null_format_id);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_invalid_format_id);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_buffer_too_small);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_null_dt);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_null_buffer);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_format_zero_buffer_size);

    // search tests
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_today);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_weekend_and_weekday);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_holiday);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_quarters);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_comparisons);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_whitespace_and_invalid);
    FOSSIL_TEST_ADD(cpp_time_suite, cpp_test_time_search_invalid_operator_and_format);

    FOSSIL_TEST_REGISTER(cpp_time_suite);
}
