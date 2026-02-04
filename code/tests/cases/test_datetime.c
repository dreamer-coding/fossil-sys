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

// --- Date/Time API Tests ---

// ** Test fossil_sys_time_is_leap_year **
FOSSIL_TEST(c_test_time_is_leap_year) {
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2000)); // Divisible by 400
    ASSUME_ITS_FALSE(fossil_sys_time_is_leap_year(1900)); // Divisible by 100, not 400
    ASSUME_ITS_TRUE(fossil_sys_time_is_leap_year(2024)); // Divisible by 4, not 100
    ASSUME_ITS_FALSE(fossil_sys_time_is_leap_year(2023)); // Not divisible by 4
}

// ** Test fossil_sys_time_days_in_month **
FOSSIL_TEST(c_test_time_days_in_month) {
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_days_in_month(2024, 2), 29); // Leap year
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_days_in_month(2023, 2), 28); // Non-leap year
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_days_in_month(2023, 4), 30); // April
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_days_in_month(2023, 1), 31); // January
}

// ** Test fossil_sys_time_validate **
FOSSIL_TEST(c_test_time_validate) {
    fossil_sys_time_datetime_t dt = {2023, 2, 28, 12, 0, 0, 0};
    ASSUME_ITS_TRUE(fossil_sys_time_validate(&dt));
    dt.day = 29;
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&dt)); // 2023 is not leap year
    dt.year = 2024;
    ASSUME_ITS_TRUE(fossil_sys_time_validate(&dt)); // 2024 is leap year
    dt.month = 13;
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&dt)); // Invalid month
    dt.month = 2; dt.day = 30;
    ASSUME_ITS_FALSE(fossil_sys_time_validate(&dt)); // Invalid day
}

// ** Test fossil_sys_time_to_unix and fossil_sys_time_from_unix **
FOSSIL_TEST(c_test_time_unix_conversion) {
    fossil_sys_time_datetime_t dt = {1970, 1, 1, 0, 0, 0, 0};
    int64_t ts = fossil_sys_time_to_unix(&dt);
    ASSUME_ITS_EQUAL_I64(ts, 0);

    dt = (fossil_sys_time_datetime_t){2024, 1, 1, 0, 0, 0, 0};
    ts = fossil_sys_time_to_unix(&dt);

    fossil_sys_time_datetime_t dt2;
    fossil_sys_time_from_unix(ts, &dt2);
    ASSUME_ITS_EQUAL_I32(dt2.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt2.month, 1);
    ASSUME_ITS_EQUAL_I32(dt2.day, 1);
    ASSUME_ITS_EQUAL_I32(dt2.hour, 0);
    ASSUME_ITS_EQUAL_I32(dt2.minute, 0);
    ASSUME_ITS_EQUAL_I32(dt2.second, 0);
}

// ** Test fossil_sys_time_add_seconds and fossil_sys_time_normalize **
FOSSIL_TEST(c_test_time_add_seconds_and_normalize) {
    fossil_sys_time_datetime_t dt = {2023, 12, 31, 23, 59, 50, 0};
    fossil_sys_time_add_seconds(&dt, 15); // Should roll over to next year
    ASSUME_ITS_EQUAL_I32(dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt.month, 1);
    ASSUME_ITS_EQUAL_I32(dt.day, 1);
    ASSUME_ITS_EQUAL_I32(dt.hour, 0);
    ASSUME_ITS_EQUAL_I32(dt.minute, 0);
    ASSUME_ITS_EQUAL_I32(dt.second, 5);

    dt = (fossil_sys_time_datetime_t){2024, 1, 1, 0, 0, -10, 0};
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_EQUAL_I32(dt.year, 2023);
    ASSUME_ITS_EQUAL_I32(dt.month, 12);
    ASSUME_ITS_EQUAL_I32(dt.day, 31);
    ASSUME_ITS_EQUAL_I32(dt.hour, 23);
    ASSUME_ITS_EQUAL_I32(dt.minute, 59);
    ASSUME_ITS_EQUAL_I32(dt.second, 50);
}

// ** Test fossil_sys_time_diff_seconds **
FOSSIL_TEST(c_test_time_diff_seconds) {
    fossil_sys_time_datetime_t a = {2024, 1, 2, 0, 0, 0, 0};
    fossil_sys_time_datetime_t b = {2024, 1, 1, 0, 0, 0, 0};
    int64_t diff = fossil_sys_time_diff_seconds(&a, &b);
    ASSUME_ITS_EQUAL_I64(diff, 86400);

    diff = fossil_sys_time_diff_seconds(&b, &a);
    ASSUME_ITS_EQUAL_I64(diff, -86400);
}

// ** Test fossil_sys_time_span_from_seconds and fossil_sys_time_span_to_seconds **
FOSSIL_TEST(c_test_time_span_conversion) {
    fossil_sys_time_span_t span = fossil_sys_time_span_from_seconds(90061); // 1 day, 1 hour, 1 minute, 1 second
    ASSUME_ITS_EQUAL_I64(span.days, 1);
    ASSUME_ITS_EQUAL_I64(span.hours, 1);
    ASSUME_ITS_EQUAL_I64(span.minutes, 1);
    ASSUME_ITS_EQUAL_I64(span.seconds, 1);

    int64_t total = fossil_sys_time_span_to_seconds(&span);
    ASSUME_ITS_EQUAL_I64(total, 90061);
}

// ** Test fossil_sys_time_add_span **
FOSSIL_TEST(c_test_time_add_span) {
    fossil_sys_time_datetime_t dt = {2024, 2, 28, 23, 0, 0, 0};
    fossil_sys_time_span_t span = {1, 2, 0, 0, 0}; // 1 day, 2 hours
    fossil_sys_time_add_span(&dt, &span);
    ASSUME_ITS_EQUAL_I32(dt.year, 2024);
    ASSUME_ITS_EQUAL_I32(dt.month, 2);
    ASSUME_ITS_EQUAL_I32(dt.day, 29); // Leap year
    ASSUME_ITS_EQUAL_I32(dt.hour, 1);
}

// ** Test fossil_sys_time_format **
FOSSIL_TEST(c_test_time_format) {
    fossil_sys_time_datetime_t dt = {2024, 3, 14, 15, 9, 26, 0};
    char buf[64];
    const char *formats[] = {
        NULL, "human", "short", "date", "time", "time-sec", "military", "iso", "rfc2822"
    };
    for (size_t i = 0; i < sizeof(formats)/sizeof(formats[0]); ++i) {
        int n = fossil_sys_time_format(&dt, buf, sizeof(buf), formats[i]);
        ASSUME_ITS_MORE_THAN_I32(n, 0);
        ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    }
}

// ** Test fossil_sys_time_get_season **
FOSSIL_TEST(c_test_time_get_season) {
    fossil_sys_time_datetime_t dt = {2024, 3, 21, 0, 0, 0, 0};
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_season(&dt, 1), FOSSIL_SYS_SEASON_SPRING);
    dt.month = 7;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_season(&dt, 1), FOSSIL_SYS_SEASON_SUMMER);
    dt.month = 12;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_season(&dt, 1), FOSSIL_SYS_SEASON_WINTER);
}

// ** Test fossil_sys_time_get_holiday **
FOSSIL_TEST(c_test_time_get_holiday) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 0, 0, 0, 0};
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_NEW_YEAR);
    dt.month = 12; dt.day = 25;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_CHRISTMAS);
    dt.month = 7; dt.day = 4;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_INDEPENDENCE);
    dt.month = 2; dt.day = 14;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_VALENTINES);
    dt.month = 3; dt.day = 17;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_ST_PATRICKS);
    dt.month = 6; dt.day = 15;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_holiday(&dt), FOSSIL_SYS_HOLIDAY_NONE);
}

// ** Test fossil_sys_time_is_weekend **
FOSSIL_TEST(c_test_time_is_weekend) {
    fossil_sys_time_datetime_t dt = {2024, 3, 16, 0, 0, 0, 0}; // Saturday
    ASSUME_ITS_TRUE(fossil_sys_time_is_weekend(&dt));
    dt.day = 17; // Sunday
    ASSUME_ITS_TRUE(fossil_sys_time_is_weekend(&dt));
    dt.day = 18; // Monday
    ASSUME_ITS_FALSE(fossil_sys_time_is_weekend(&dt));
}

// ** Test fossil_sys_time_get_quarter **
FOSSIL_TEST(c_test_time_get_quarter) {
    fossil_sys_time_datetime_t dt = {2024, 1, 1, 0, 0, 0, 0};
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_quarter(&dt), 1);
    dt.month = 4;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_quarter(&dt), 2);
    dt.month = 7;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_quarter(&dt), 3);
    dt.month = 10;
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_get_quarter(&dt), 4);
}

// ** Test fossil_sys_time_format_smart **
FOSSIL_TEST(c_test_time_format_smart) {
    fossil_sys_time_datetime_t now = {2024, 3, 14, 15, 0, 0, 0};
    fossil_sys_time_datetime_t dt = now;
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
}

// ** Test fossil_sys_time_format_relative **
FOSSIL_TEST(c_test_time_format_relative) {
    fossil_sys_time_datetime_t now = {2024, 3, 14, 15, 0, 0, 0};
    fossil_sys_time_datetime_t dt = now;
    char buf[64];
    int n = fossil_sys_time_format_relative(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    dt.minute -= 5;
    fossil_sys_time_normalize(&dt);
    n = fossil_sys_time_format_relative(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
}

// ** Test fossil_sys_time_search **
FOSSIL_TEST(c_test_time_search) {
    fossil_sys_time_datetime_t now = {2024, 3, 14, 15, 0, 0, 0};
    fossil_sys_time_datetime_t dt = now;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "today"));
    dt.day -= 1;
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "today"));
}

// Additional tests for fossil_sys_time_format_smart

FOSSIL_TEST(c_test_time_format_smart_same_day) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 14, 30, 0, 0};
    fossil_sys_time_datetime_t dt = {2024, 5, 10, 9, 15, 0, 0};
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    // Should be time-only format (e.g., "09:15 AM")
}

FOSSIL_TEST(c_test_time_format_smart_yesterday) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0};
    fossil_sys_time_datetime_t dt = {2024, 5, 9, 22, 45, 0, 0};
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    ASSUME_ITS_TRUE(strstr(buf, "Yesterday") != NULL);
}

FOSSIL_TEST(c_test_time_format_smart_tomorrow) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0};
    fossil_sys_time_datetime_t dt = {2024, 5, 11, 8, 0, 0, 0};
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    ASSUME_ITS_TRUE(strstr(buf, "Tomorrow") != NULL);
}

FOSSIL_TEST(c_test_time_format_smart_same_week) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0}; // Friday
    fossil_sys_time_datetime_t dt = {2024, 5, 8, 16, 0, 0, 0};   // Wednesday
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    ASSUME_ITS_TRUE(strstr(buf, "Wednesday") != NULL);
}

FOSSIL_TEST(c_test_time_format_smart_same_year) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0};
    fossil_sys_time_datetime_t dt = {2024, 2, 1, 12, 0, 0, 0};
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    // Should be month and day only (e.g., "Feb 01")
}

FOSSIL_TEST(c_test_time_format_smart_different_year) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0};
    fossil_sys_time_datetime_t dt = {2023, 12, 25, 7, 0, 0, 0};
    char buf[64];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_NOT_EQUAL_CHAR(buf[0], '\0');
    // Should be full date (e.g., "12/25/2023")
}

FOSSIL_TEST(c_test_time_format_smart_buffer_too_small) {
    fossil_sys_time_datetime_t now = {2024, 5, 10, 10, 0, 0, 0};
    fossil_sys_time_datetime_t dt = {2024, 5, 10, 10, 0, 0, 0};
    char buf[2];
    int n = fossil_sys_time_format_smart(&dt, &now, buf, sizeof(buf));
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(c_test_time_format_human) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[64];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "human");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "January") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "31") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "03:45 PM") != NULL);
}

FOSSIL_TEST(c_test_time_format_short) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[32];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "short");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "01/31/2026") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "03:45 PM") != NULL);
}

FOSSIL_TEST(c_test_time_format_date) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[16];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "date");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strcmp(buf, "01/31/2026") == 0);
}

FOSSIL_TEST(c_test_time_format_time) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[16];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "time");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strcmp(buf, "03:45 PM") == 0);
}

FOSSIL_TEST(c_test_time_format_time_sec) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[20];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "time-sec");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strcmp(buf, "03:45:12 PM") == 0);
}

FOSSIL_TEST(c_test_time_format_military) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[8];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "military");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strcmp(buf, "15:45") == 0);
}

FOSSIL_TEST(c_test_time_format_iso) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[32];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "iso");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "2026-01-31T15:45:12") != NULL);
}

FOSSIL_TEST(c_test_time_format_rfc2822) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[64];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "rfc2822");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "Sat, 31 Jan 2026 15:45:12") != NULL);
}

FOSSIL_TEST(c_test_time_format_null_format_id) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[64];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), NULL);
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "January") != NULL);
}

FOSSIL_TEST(c_test_time_format_invalid_format_id) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[64];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "%Y/%m/%d %H-%M-%S");
    ASSUME_ITS_MORE_THAN_I32(n, 0);
    ASSUME_ITS_TRUE(strstr(buf, "2026/01/31") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "15-45-12") != NULL);
}

FOSSIL_TEST(c_test_time_format_buffer_too_small) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[2];
    int n = fossil_sys_time_format(&dt, buf, sizeof(buf), "human");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(c_test_time_format_null_dt) {
    char buf[32];
    int n = fossil_sys_time_format(NULL, buf, sizeof(buf), "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(c_test_time_format_null_buffer) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    int n = fossil_sys_time_format(&dt, NULL, 32, "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(c_test_time_format_zero_buffer_size) {
    fossil_sys_time_datetime_t dt = {2026, 1, 31, 15, 45, 12, 0};
    char buf[32];
    int n = fossil_sys_time_format(&dt, buf, 0, "date");
    ASSUME_ITS_EQUAL_I32(n, -1);
}

FOSSIL_TEST(c_test_time_search_today) {
    fossil_sys_time_datetime_t now = {2024, 6, 1, 12, 0, 0, 0};
    fossil_sys_time_datetime_t dt = now;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "today"));
    dt.day = 2;
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "today"));
}

FOSSIL_TEST(c_test_time_search_weekend_and_weekday) {
    fossil_sys_time_datetime_t dt = {2024, 6, 1, 0, 0, 0, 0}; // Saturday
    fossil_sys_time_datetime_t now = dt;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "weekend"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "weekday"));
    dt.day = 3; // Monday
    fossil_sys_time_normalize(&dt);
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "weekend"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "weekday"));
}

FOSSIL_TEST(c_test_time_search_holiday) {
    fossil_sys_time_datetime_t dt = {2024, 12, 25, 0, 0, 0, 0}; // Christmas
    fossil_sys_time_datetime_t now = dt;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "holiday"));
    dt.month = 6; dt.day = 15; // Not a holiday
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "holiday"));
}

FOSSIL_TEST(c_test_time_search_quarters) {
    fossil_sys_time_datetime_t dt = {2024, 2, 1, 0, 0, 0, 0};
    fossil_sys_time_datetime_t now = dt;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "Q1"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "Q2"));
    dt.month = 5;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "Q2"));
    dt.month = 8;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "Q3"));
    dt.month = 11;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "Q4"));
}

FOSSIL_TEST(c_test_time_search_comparisons) {
    fossil_sys_time_datetime_t dt = {2024, 6, 15, 0, 0, 0, 0};
    fossil_sys_time_datetime_t now = dt;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "> 2024-06-01"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, ">= 2024-06-15"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "> 2024-06-15"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "< 2024-07-01"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "<= 2024-06-15"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "< 2024-06-15"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "= 2024-06-15"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "= 2024-06-14"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "!= 2024-06-14"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "!= 2024-06-15"));
}

FOSSIL_TEST(c_test_time_search_whitespace_and_invalid) {
    fossil_sys_time_datetime_t dt = {2024, 6, 15, 0, 0, 0, 0};
    fossil_sys_time_datetime_t now = dt;
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "   today"));
    ASSUME_ITS_TRUE(fossil_sys_time_search(&dt, &now, "   >=   2024-06-15"));
    ASSUME_ITS_FALSE(fossil_sys_time_search(&dt, &now, "   <   2024-06-15"));
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, &now, ""), 0);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(NULL, &now, "today"), -1);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, NULL, "today"), -1);
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, &now, NULL), -1);
}

FOSSIL_TEST(c_test_time_search_invalid_operator_and_format) {
    fossil_sys_time_datetime_t dt = {2024, 6, 15, 0, 0, 0, 0};
    fossil_sys_time_datetime_t now = dt;
    // Invalid operator
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, &now, ">> 2024-06-15"), 0);
    // Invalid date format
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, &now, "> 2024/06/15"), 0);
    // Unknown keyword
    ASSUME_ITS_EQUAL_I32(fossil_sys_time_search(&dt, &now, "nonsense"), 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_time_tests) {
    // --- Date/Time API Tests ---
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_is_leap_year);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_days_in_month);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_validate);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_unix_conversion);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_seconds_and_normalize);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_diff_seconds);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_span_conversion);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_add_span);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_get_season);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_get_holiday);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_is_weekend);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_get_quarter);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_relative);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search);

    // tests for fossil_sys_time_format_smart
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_same_day);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_yesterday);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_tomorrow);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_same_week);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_same_year);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_different_year);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_smart_buffer_too_small);

    // format tests
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_human);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_short);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_date);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_time);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_time_sec);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_military);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_iso);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_rfc2822);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_null_format_id);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_invalid_format_id);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_buffer_too_small);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_null_dt);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_null_buffer);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_format_zero_buffer_size);

    // search tests
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_today);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_weekend_and_weekday);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_holiday);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_quarters);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_comparisons);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_whitespace_and_invalid);
    FOSSIL_TEST_ADD(c_time_suite, c_test_time_search_invalid_operator_and_format);

    FOSSIL_TEST_REGISTER(c_time_suite);
}
