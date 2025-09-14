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
#include "fossil/sys/datetime.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <time.h>  // Windows-specific time utilities
#else
#include <sys/time.h>
#include <unistd.h>  // for nanosleep, POSIX sleep functions
#endif

static const int DAYS_IN_MONTH[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};


/**
 * @brief Helper: return 1 if leap year, else 0.
 */
static int is_leap_year_internal(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

/**
 * @brief Helper: return days in given month (1-12).
 */
static int days_in_month_internal(int year, int month) {
    if (month == 2)
        return DAYS_IN_MONTH[1] + is_leap_year_internal(year);
    return DAYS_IN_MONTH[month - 1];
}

#if defined(_WIN32) || defined(_WIN64)
/**
 * Windows replacement for timegm() using _mkgmtime().
 */
static inline time_t fossil_sys_timegm(struct tm *tm) {
    return _mkgmtime(tm);
}
#else
/**
 * Portable fallback for timegm().
 *
 * If timegm() is available (GNU, BSD, etc.), just use it.
 * Otherwise, emulate it using mktime() after forcing UTC.
 */
static inline time_t fossil_sys_timegm(struct tm *tm) {
    #if defined(__USE_BSD) || defined(__USE_GNU)
    return timegm(tm);
    #else
    /* Fallback: Temporarily set TZ to UTC, call mktime, restore TZ. */
    char *old_tz = getenv("TZ");
    setenv("TZ", "", 1);     // Force UTC
    tzset();

    time_t result = mktime(tm);

    if (old_tz)
        setenv("TZ", old_tz, 1);
    else
        unsetenv("TZ");

    tzset();
    return result;
    #endif
}
#endif



// main source code

void fossil_sys_time_now(fossil_sys_time_datetime_t *dt) {
    if (!dt) return;
    
    struct timespec ts;
    struct tm *t;
    #if defined(_WIN32) || defined(_WIN64)
        if (timespec_get(&ts, TIME_UTC) == 0) {
            fprintf(stderr, "Error getting current time\n");
            return;
        }
        t = localtime(&ts.tv_sec);
        if (!t) {
            fprintf(stderr, "Error converting time to local time\n");
            return;
        }
    #else
        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0) {
            perror("Error getting current time");
            return;
        }
        ts.tv_sec = tv.tv_sec;
        ts.tv_nsec = tv.tv_usec * 1000;
        t = localtime(&ts.tv_sec);
        if (!t) {
            perror("Error converting time to local time");
            return;
        }
    #endif
    
    dt->year = t->tm_year + 1900;
    dt->month = t->tm_mon + 1;
    dt->day = t->tm_mday;
    dt->hour = t->tm_hour;
    dt->minute = t->tm_min;
    dt->second = t->tm_sec;
    dt->nanosecond = ts.tv_nsec;
}

int fossil_sys_time_format(const fossil_sys_time_datetime_t *dt, char *buffer, size_t buffer_size, const char *format, int military_time) {
    if (!dt || !buffer || !format) return -1;
    
    struct tm t = {
        .tm_year = dt->year - 1900,
        .tm_mon = dt->month - 1,
        .tm_mday = dt->day,
        .tm_hour = dt->hour,
        .tm_min = dt->minute,
        .tm_sec = dt->second
    };
    
    if (!military_time && t.tm_hour > 12) {
        t.tm_hour -= 12;
    }
    
    size_t result = strftime(buffer, buffer_size, format, &t);
    if (result == 0) {
        fprintf(stderr, "Error formatting time\n");
        return -1;
    }
    return (int)result;
}

int fossil_sys_time_is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int fossil_sys_time_days_in_month(int year, int month) {
    static const int days_per_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month < 1 || month > 12) return -1;
    if (month == 2 && fossil_sys_time_is_leap_year(year)) return 29;
    return days_per_month[month - 1];
}

void fossil_sys_time_normalize(fossil_sys_time_datetime_t *dt) {
    if (!dt) return;

    // Normalize nanoseconds to [0, 1e9)
    while (dt->nanosecond >= 1000000000) {
        dt->second++;
        dt->nanosecond -= 1000000000;
    }
    while (dt->nanosecond < 0) {
        dt->second--;
        dt->nanosecond += 1000000000;
    }

    // Normalize seconds, minutes, hours
    while (dt->second >= 60) {
        dt->minute++;
        dt->second -= 60;
    }
    while (dt->second < 0) {
        dt->minute--;
        dt->second += 60;
    }

    while (dt->minute >= 60) {
        dt->hour++;
        dt->minute -= 60;
    }
    while (dt->minute < 0) {
        dt->hour--;
        dt->minute += 60;
    }

    while (dt->hour >= 24) {
        dt->day++;
        dt->hour -= 24;
    }
    while (dt->hour < 0) {
        dt->day--;
        dt->hour += 24;
    }

    // Normalize day/month/year
    while (dt->day > days_in_month_internal(dt->year, dt->month)) {
        dt->day -= days_in_month_internal(dt->year, dt->month);
        dt->month++;
        if (dt->month > 12) {
            dt->month = 1;
            dt->year++;
        }
    }

    while (dt->day <= 0) {
        dt->month--;
        if (dt->month <= 0) {
            dt->month = 12;
            dt->year--;
        }
        dt->day += days_in_month_internal(dt->year, dt->month);
    }
}

int fossil_sys_time_validate(const fossil_sys_time_datetime_t *dt) {
    if (!dt) return 0;
    if (dt->month < 1 || dt->month > 12) return 0;
    if (dt->day < 1 || dt->day > days_in_month_internal(dt->year, dt->month)) return 0;
    if (dt->hour < 0 || dt->hour > 23) return 0;
    if (dt->minute < 0 || dt->minute > 59) return 0;
    if (dt->second < 0 || dt->second > 59) return 0;
    if (dt->nanosecond < 0 || dt->nanosecond >= 1000000000) return 0;
    return 1;
}

void fossil_sys_time_add_seconds(fossil_sys_time_datetime_t *dt, int64_t seconds) {
    if (!dt) return;
    dt->second += (int)seconds;
    fossil_sys_time_normalize(dt);
}

int64_t fossil_sys_time_to_unix(const fossil_sys_time_datetime_t *dt) {
    if (!dt) return 0;
    struct tm t = {0};
    t.tm_year = dt->year - 1900;
    t.tm_mon  = dt->month - 1;
    t.tm_mday = dt->day;
    t.tm_hour = dt->hour;
    t.tm_min  = dt->minute;
    t.tm_sec  = dt->second;
    time_t result = fossil_sys_timegm(&t); // UTC-safe variant of mktime
    return (int64_t)result;
}

void fossil_sys_time_from_unix(int64_t timestamp, fossil_sys_time_datetime_t *dt) {
    if (!dt) return;
    time_t t = (time_t)timestamp;
    struct tm out;
    gmtime_r(&t, &out);
    dt->year = out.tm_year + 1900;
    dt->month = out.tm_mon + 1;
    dt->day = out.tm_mday;
    dt->hour = out.tm_hour;
    dt->minute = out.tm_min;
    dt->second = out.tm_sec;
    dt->nanosecond = 0;
}

int64_t fossil_sys_time_diff_seconds(const fossil_sys_time_datetime_t *a,
                                     const fossil_sys_time_datetime_t *b) {
    return fossil_sys_time_to_unix(a) - fossil_sys_time_to_unix(b);
}

uint64_t fossil_sys_time_monotonic_ns(void) {
#if defined(CLOCK_MONOTONIC)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64_t)ts.tv_sec * 1000000000ULL) + (uint64_t)ts.tv_nsec;
#else
    // Fallback: use wall clock (less precise)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ((uint64_t)ts.tv_sec * 1000000000ULL) + (uint64_t)ts.tv_nsec;
#endif
}

void fossil_sys_time_sleep_ns(uint64_t nanoseconds) {
    struct timespec req, rem;
    req.tv_sec = nanoseconds / 1000000000ULL;
    req.tv_nsec = nanoseconds % 1000000000ULL;
    while (nanosleep(&req, &rem) == -1 && errno == EINTR) {
        req = rem; // resume sleeping
    }
}

fossil_sys_time_span_t fossil_sys_time_span_from_seconds(int64_t seconds) {
    fossil_sys_time_span_t span = {0};
    span.days = seconds / 86400;
    seconds %= 86400;
    span.hours = seconds / 3600;
    seconds %= 3600;
    span.minutes = seconds / 60;
    span.seconds = seconds % 60;
    return span;
}

int64_t fossil_sys_time_span_to_seconds(const fossil_sys_time_span_t *span) {
    if (!span) return 0;
    return span->days * 86400 +
           span->hours * 3600 +
           span->minutes * 60 +
           span->seconds;
}

void fossil_sys_time_add_span(fossil_sys_time_datetime_t *dt,
                              const fossil_sys_time_span_t *span) {
    if (!dt || !span) return;
    dt->day    += (int)span->days;
    dt->hour   += (int)span->hours;
    dt->minute += (int)span->minutes;
    dt->second += (int)span->seconds;
    dt->nanosecond += span->nanoseconds;
    fossil_sys_time_normalize(dt);
}
