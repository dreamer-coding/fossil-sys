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

// formatting time

typedef struct {
    const char *id;
    const char *strftime_fmt;
} fossil_time_format_t;

static const fossil_time_format_t fossil_time_formats[] = {
    { "human",      "%B %d, %Y %I:%M %p" },   // January 31, 2026 03:45 PM
    { "short",      "%m/%d/%Y %I:%M %p" },   // 01/31/2026 03:45 PM
    { "date",       "%m/%d/%Y" },             // 01/31/2026
    { "time",       "%I:%M %p" },              // 03:45 PM
    { "time-sec",  "%I:%M:%S %p" },           // 03:45:12 PM
    { "military",  "%H:%M" },                  // 15:45
    { "iso",       "%Y-%m-%dT%H:%M:%S" },      // 2026-01-31T15:45:12
    { "rfc2822",   "%a, %d %b %Y %H:%M:%S" },  // Sat, 31 Jan 2026 15:45:12
};

static const char *lookup_time_format(const char *id) {
    if (!id || strcmp(id, "human") == 0) {
        return "%B %d, %Y %I:%M %p";
    }

    for (size_t i = 0; i < sizeof(fossil_time_formats) / sizeof(fossil_time_formats[0]); i++) {
        if (strcmp(fossil_time_formats[i].id, id) == 0) {
            return fossil_time_formats[i].strftime_fmt;
        }
    }

    return NULL;
}

int fossil_sys_time_format(
    const fossil_sys_time_datetime_t *dt,
    char *buffer,
    size_t buffer_size,
    const char *format_id
) {
    if (!dt || !buffer || buffer_size == 0) {
        return -1;
    }

    struct tm t = {
        .tm_year = dt->year - 1900,
        .tm_mon  = dt->month - 1,
        .tm_mday = dt->day,
        .tm_hour = dt->hour,
        .tm_min  = dt->minute,
        .tm_sec  = dt->second
    };

    const char *fmt = lookup_time_format(format_id);

    /* If format_id is not a known ID, treat it as a raw strftime format */
    if (!fmt) {
        fmt = format_id;
    }

    size_t result = strftime(buffer, buffer_size, fmt, &t);
    if (result == 0) {
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

fossil_sys_season_t fossil_sys_time_get_season(const fossil_sys_time_datetime_t *dt, int northern_hemisphere) {
    if (!dt) return FOSSIL_SYS_SEASON_UNKNOWN;
    int month = dt->month;
    if (!northern_hemisphere) {
        // Swap NH seasons for SH
        if (month == 12 || month <= 2) return FOSSIL_SYS_SEASON_SUMMER;
        if (month >= 3 && month <= 5) return FOSSIL_SYS_SEASON_AUTUMN;
        if (month >= 6 && month <= 8) return FOSSIL_SYS_SEASON_WINTER;
        if (month >= 9 && month <= 11) return FOSSIL_SYS_SEASON_SPRING;
    } else {
        if (month == 12 || month <= 2) return FOSSIL_SYS_SEASON_WINTER;
        if (month >= 3 && month <= 5) return FOSSIL_SYS_SEASON_SPRING;
        if (month >= 6 && month <= 8) return FOSSIL_SYS_SEASON_SUMMER;
        if (month >= 9 && month <= 11) return FOSSIL_SYS_SEASON_AUTUMN;
    }
    return FOSSIL_SYS_SEASON_UNKNOWN;
}

int fossil_sys_time_is_weekend(const fossil_sys_time_datetime_t *dt) {
    // Zeller's Congruence to calculate day of week (0 = Saturday, 1 = Sunday, ... 6 = Friday)
    int y = dt->year;
    int m = dt->month;
    int d = dt->day;
    if (m < 3) { m += 12; y -= 1; }
    int K = y % 100;
    int J = y / 100;
    int f = d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J;
    int dow = f % 7;
    return (dow == 0 || dow == 1); // Saturday or Sunday
}

int fossil_sys_time_get_quarter(const fossil_sys_time_datetime_t *dt) {
    if (!dt) return 0;
    return (dt->month - 1) / 3 + 1;
}

// Helper: nth weekday of month (1-based)
static int nth_weekday_of_month(int year, int month, int weekday, int n) {
    // weekday: 0=Sunday ... 6=Saturday
    // n: 1=first, 2=second, etc.
    fossil_sys_time_datetime_t dt = {year, month, 1, 0,0,0,0};
    int dow;
    // Compute day of week for the 1st
    int y = dt.year;
    int m = dt.month;
    int d = dt.day;
    if (m < 3) { m += 12; y -= 1; }
    int K = y % 100;
    int J = y / 100;
    int f = d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J;
    dow = f % 7; // 0=Saturday, 1=Sunday, ..., 6=Friday
    int diff = (weekday - ((dow + 6) % 7) + 7) % 7; // shift so 0=Sunday
    return 1 + diff + (n-1)*7;
}

// Last weekday of month
static int last_weekday_of_month(int year, int month, int weekday) {
    int days = fossil_sys_time_days_in_month(year, month);
    for (int d = days; d >= 1; d--) {
        fossil_sys_time_datetime_t dt = {year, month, d, 0,0,0,0};
        if (fossil_sys_time_is_weekend(&dt) && weekday == 0) continue; // optional
        // Calculate day of week
        int y = dt.year;
        int m = dt.month;
        int f_d = dt.day;
        if (m < 3) { m += 12; y -= 1; }
        int K = y % 100;
        int J = y / 100;
        int f = f_d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J;
        int dow = f % 7; // 0=Saturday ... 6=Friday
        if (((dow + 6) % 7) == weekday) return d; // 0=Sunday
    }
    return 1;
}

fossil_sys_holiday_id_t fossil_sys_time_get_holiday(const fossil_sys_time_datetime_t *dt) {
    if (!dt) return FOSSIL_SYS_HOLIDAY_NONE;

    int m = dt->month, d = dt->day;
    int y = dt->year;

    // Fixed-date holidays
    if (m == 1 && d == 1) return FOSSIL_SYS_HOLIDAY_NEW_YEAR;
    if (m == 2 && d == 14) return FOSSIL_SYS_HOLIDAY_VALENTINES;
    if (m == 3 && d == 17) return FOSSIL_SYS_HOLIDAY_ST_PATRICKS;
    if (m == 7 && d == 4) return FOSSIL_SYS_HOLIDAY_INDEPENDENCE;
    if (m == 10 && d == 31) return FOSSIL_SYS_HOLIDAY_HALLOWEEN;
    if (m == 11 && d == 11) return FOSSIL_SYS_HOLIDAY_VETERANS_DAY;
    if (m == 12 && d == 25) return FOSSIL_SYS_HOLIDAY_CHRISTMAS;

    // Variable-date holidays
    if (m == 1 && d == nth_weekday_of_month(y,1,1,3)) return FOSSIL_SYS_HOLIDAY_ML_KING_DAY; // 3rd Monday Jan
    if (m == 2 && d == nth_weekday_of_month(y,2,1,3)) return FOSSIL_SYS_HOLIDAY_PRESIDENTS_DAY; // 3rd Monday Feb
    if (m == 5 && d == last_weekday_of_month(y,5,1)) return FOSSIL_SYS_HOLIDAY_MEMORIAL_DAY; // Last Monday May
    if (m == 9 && d == nth_weekday_of_month(y,9,1,1)) return FOSSIL_SYS_HOLIDAY_LABOR_DAY; // 1st Monday Sep
    if (m == 11 && d == nth_weekday_of_month(y,11,4,4)) return FOSSIL_SYS_HOLIDAY_THANKSGIVING; // 4th Thu Nov
    if (m == 2 && d == nth_weekday_of_month(y,2,0,1)) return FOSSIL_SYS_HOLIDAY_SUPER_BOWL; // first Sunday Feb
    if (m == 5 && d == nth_weekday_of_month(y,5,0,2)) return FOSSIL_SYS_HOLIDAY_MOTHERS_DAY; // 2nd Sun May
    if (m == 6 && d == nth_weekday_of_month(y,6,0,3)) return FOSSIL_SYS_HOLIDAY_FATHERS_DAY; // 3rd Sun June

    return FOSSIL_SYS_HOLIDAY_NONE;
}

static const char *weekday_name(const fossil_sys_time_datetime_t *dt) {
    static const char *names[] = {
        "Sunday","Monday","Tuesday","Wednesday",
        "Thursday","Friday","Saturday"
    };

    int y = dt->year;
    int m = dt->month;
    int d = dt->day;
    if (m < 3) { m += 12; y--; }
    int K = y % 100;
    int J = y / 100;
    int f = d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J;
    int dow = (f + 6) % 7; // 0 = Sunday
    return names[dow];
}

int fossil_sys_time_format_smart(
    const fossil_sys_time_datetime_t *dt,
    const fossil_sys_time_datetime_t *now,
    char *buffer,
    size_t buffer_size
) {
    if (!dt || !now || !buffer) return -1;

    int64_t diff = fossil_sys_time_diff_seconds(dt, now);
    int same_year = (dt->year == now->year);
    int same_day =
        dt->year  == now->year &&
        dt->month == now->month &&
        dt->day   == now->day;

    if (same_day) {
        return fossil_sys_time_format(dt, buffer, buffer_size, "time");
    }

    if (diff >= -86400 && diff < 0) {
        return snprintf(buffer, buffer_size,
            "Yesterday at %02d:%02d %s",
            (dt->hour % 12) ? (dt->hour % 12) : 12,
            dt->minute,
            dt->hour >= 12 ? "PM" : "AM"
        );
    }

    if (diff > 0 && diff <= 86400) {
        return snprintf(buffer, buffer_size,
            "Tomorrow at %02d:%02d %s",
            (dt->hour % 12) ? (dt->hour % 12) : 12,
            dt->minute,
            dt->hour >= 12 ? "PM" : "AM"
        );
    }

    if (llabs(diff) < 7 * 86400) {
        return snprintf(buffer, buffer_size,
            "%s at %02d:%02d %s",
            weekday_name(dt),
            (dt->hour % 12) ? (dt->hour % 12) : 12,
            dt->minute,
            dt->hour >= 12 ? "PM" : "AM"
        );
    }

    if (same_year) {
        return fossil_sys_time_format(dt, buffer, buffer_size, "%b %d");
    }

    return fossil_sys_time_format(dt, buffer, buffer_size, "date");
}

static void format_ampm(
    int hour, int minute,
    char *out, size_t out_size
) {
    int h = hour % 12;
    if (h == 0) h = 12;
    snprintf(out, out_size, "%d:%02d %s",
        h, minute, hour >= 12 ? "PM" : "AM");
}

static const char *weekday_name(const fossil_sys_time_datetime_t *dt) {
    static const char *names[] = {
        "Sunday","Monday","Tuesday","Wednesday",
        "Thursday","Friday","Saturday"
    };

    int y = dt->year;
    int m = dt->month;
    int d = dt->day;
    if (m < 3) { m += 12; y--; }
    int K = y % 100;
    int J = y / 100;
    int f = d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J;
    int dow = (f + 6) % 7; // 0=Sunday
    return names[dow];
}

int fossil_sys_time_format_relative(
    const fossil_sys_time_datetime_t *target,
    const fossil_sys_time_datetime_t *now,
    char *buffer,
    size_t buffer_size
) {
    if (!target || !now || !buffer) return -1;

    int64_t diff = fossil_sys_time_diff_seconds(target, now);
    int64_t adiff = llabs(diff);

    char timebuf[16];
    format_ampm(target->hour, target->minute, timebuf, sizeof(timebuf));

    /* Immediate past */
    if (adiff < 5)
        return snprintf(buffer, buffer_size, "just now");

    if (adiff < 60)
        return snprintf(buffer, buffer_size,
            "%lld seconds %s",
            (long long)adiff,
            diff < 0 ? "ago" : "from now");

    if (adiff < 3600)
        return snprintf(buffer, buffer_size,
            "%lld minutes %s",
            (long long)(adiff / 60),
            diff < 0 ? "ago" : "from now");

    /* Same calendar day */
    if (target->year == now->year &&
        target->month == now->month &&
        target->day == now->day) {
        return snprintf(buffer, buffer_size,
            "today at %s", timebuf);
    }

    /* Yesterday / Tomorrow */
    if (diff < 0 && adiff < 2 * 86400)
        return snprintf(buffer, buffer_size,
            "yesterday at %s", timebuf);

    if (diff > 0 && adiff < 2 * 86400)
        return snprintf(buffer, buffer_size,
            "tomorrow at %s", timebuf);

    /* Same week-ish */
    if (adiff < 7 * 86400) {
        return snprintf(buffer, buffer_size,
            "%s at %s",
            weekday_name(target), timebuf);
    }

    /* Same year */
    if (target->year == now->year) {
        return fossil_sys_time_format(
            target, buffer, buffer_size, "%b %d"
        );
    }

    /* Fallback */
    return fossil_sys_time_format(
        target, buffer, buffer_size, "date"
    );
}
