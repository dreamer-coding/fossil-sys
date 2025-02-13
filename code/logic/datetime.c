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
#include "fossil/sys/datetime.h"
#include <stdio.h>
#include <time.h>

#ifdef __WIN32
    #include <windows.h>
#else
#include <sys/time.h>
#include <linux/time.h>
#endif


void fossil_sys_time_now(fossil_sys_time_datetime_t *dt) {
    if (!dt) return;
    
    struct timespec ts;
    struct tm t;
    #if defined(_WIN32) || defined(_WIN64)
        timespec_get(&ts, TIME_UTC);
        localtime_s(&t, &ts.tv_sec);
    #else
        clock_gettime(CLOCK_REALTIME, &ts);
        localtime_r(&ts.tv_sec, &t);
    #endif
    
    dt->year = t.tm_year + 1900;
    dt->month = t.tm_mon + 1;
    dt->day = t.tm_mday;
    dt->hour = t.tm_hour;
    dt->minute = t.tm_min;
    dt->second = t.tm_sec;
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
    
    #if defined(_WIN32) || defined(_WIN64)
        return (int)strftime_s(buffer, buffer_size, format, &t);
    #else
        return (int)strftime(buffer, buffer_size, format, &t);
    #endif
}

void fossil_sys_time_add(fossil_sys_time_datetime_t *dt, int64_t amount, uint64_t unit) {
    if (!dt) return;
    
    int64_t total_nanoseconds = amount * unit;
    dt->nanosecond += total_nanoseconds;
    while (dt->nanosecond >= 1000000000) {
        dt->nanosecond -= 1000000000;
        dt->second++;
    }
}

void fossil_sys_time_subtract(fossil_sys_time_datetime_t *dt, int64_t amount, uint64_t unit) {
    if (!dt) return;
    
    int64_t total_nanoseconds = amount * unit;
    dt->nanosecond -= total_nanoseconds;
    while (dt->nanosecond < 0) {
        dt->nanosecond += 1000000000;
        dt->second--;
    }
}

int64_t fossil_sys_time_to_unix(const fossil_sys_time_datetime_t *dt) {
    if (!dt) return -1;
    
    struct tm t = {
        .tm_year = dt->year - 1900,
        .tm_mon = dt->month - 1,
        .tm_mday = dt->day,
        .tm_hour = dt->hour,
        .tm_min = dt->minute,
        .tm_sec = dt->second
    };
    
    return (int64_t) mktime(&t);
}

void fossil_sys_time_from_unix(fossil_sys_time_datetime_t *dt, int64_t timestamp) {
    if (!dt) return;
    
    struct tm t;
    time_t ts = (time_t) timestamp;
    #if defined(_WIN32) || defined(_WIN64)
        localtime_s(&t, &ts);
    #else
        localtime_r(&ts, &t);
    #endif
    
    dt->year = t.tm_year + 1900;
    dt->month = t.tm_mon + 1;
    dt->day = t.tm_mday;
    dt->hour = t.tm_hour;
    dt->minute = t.tm_min;
    dt->second = t.tm_sec;
    dt->nanosecond = 0;
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
