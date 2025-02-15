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

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

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
