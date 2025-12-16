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
#include "fossil/sys/cpu.h"

#include <string.h>

#if defined(_WIN32)
    #include <windows.h>
    #include <intrin.h>
#else
    #include <unistd.h>
    #include <errno.h>
    #if defined(__linux__)
        #include <sched.h>
    #endif
#endif

/* ============================================================
 * Topology & Info
 * ============================================================ */

bool
fossil_sys_cpu_query_info(fossil_sys_cpu_info_t *info)
{
    if (!info)
        return false;

    memset(info, 0, sizeof(*info));

#if defined(_WIN32)

    SYSTEM_INFO si;
    GetSystemInfo(&si);

    info->logical_cores  = (uint32_t)si.dwNumberOfProcessors;
    info->physical_cores = info->logical_cores;
    info->packages       = 1;
    info->numa_nodes     = 1;
    info->frequency_hz   = 0;

    return true;

#else /* POSIX */

    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n <= 0)
        return false;

    info->logical_cores  = (uint32_t)n;
    info->physical_cores = (uint32_t)n;
    info->packages       = 1;
    info->numa_nodes     = 1;
    info->frequency_hz   = 0;

    return true;

#endif
}

uint32_t
fossil_sys_cpu_logical_cores(void)
{
    fossil_sys_cpu_info_t info;
    if (!fossil_sys_cpu_query_info(&info))
        return 0;
    return info.logical_cores;
}

uint32_t
fossil_sys_cpu_physical_cores(void)
{
    fossil_sys_cpu_info_t info;
    if (!fossil_sys_cpu_query_info(&info))
        return 0;
    return info.physical_cores;
}

/* ============================================================
 * Affinity
 * ============================================================ */

bool
fossil_sys_cpu_get_affinity(fossil_sys_cpu_affinity_t *affinity)
{
    if (!affinity)
        return false;

#if defined(_WIN32)

    DWORD_PTR process_mask = 0;
    DWORD_PTR system_mask  = 0;

    if (!GetProcessAffinityMask(
            GetCurrentProcess(),
            &process_mask,
            &system_mask))
        return false;

    affinity->mask = (uint64_t)process_mask;
    return true;

#elif defined(__linux__)

    cpu_set_t set;
    if (sched_getaffinity(0, sizeof(set), &set) != 0)
        return false;

    uint64_t mask = 0;
    for (int i = 0; i < 64; ++i) {
        if (CPU_ISSET(i, &set))
            mask |= (1ULL << i);
    }

    affinity->mask = mask;
    return true;

#else
    (void)affinity;
    return false;
#endif
}

bool
fossil_sys_cpu_set_affinity(const fossil_sys_cpu_affinity_t *affinity)
{
    if (!affinity)
        return false;

#if defined(_WIN32)

    if (!SetProcessAffinityMask(
            GetCurrentProcess(),
            (DWORD_PTR)affinity->mask))
        return false;

    return true;

#elif defined(__linux__)

    cpu_set_t set;
    CPU_ZERO(&set);

    for (int i = 0; i < 64; ++i) {
        if (affinity->mask & (1ULL << i))
            CPU_SET(i, &set);
    }

    if (sched_setaffinity(0, sizeof(set), &set) != 0)
        return false;

    return true;

#else
    (void)affinity;
    return false;
#endif
}

/* ============================================================
 * Feature Detection
 * ============================================================ */

bool
fossil_sys_cpu_has_feature(fossil_sys_cpu_feature_t feature)
{
#if defined(_WIN32) && (defined(_M_X64) || defined(_M_IX86))

    int info[4] = {0};
    __cpuid(info, 1);

    if (feature == FOSSIL_CPU_FEATURE_SSE2)
        return (info[3] & (1 << 26)) != 0;

    if (feature == FOSSIL_CPU_FEATURE_AVX)
        return (info[2] & (1 << 28)) != 0;

    return false;

#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))

    if (feature == FOSSIL_CPU_FEATURE_SSE2)
        return __builtin_cpu_supports("sse2");

    if (feature == FOSSIL_CPU_FEATURE_AVX)
        return __builtin_cpu_supports("avx");

    if (feature == FOSSIL_CPU_FEATURE_AVX2)
        return __builtin_cpu_supports("avx2");

    return false;

#elif defined(__ARM_NEON)

    return feature == FOSSIL_CPU_FEATURE_NEON;

#else
    (void)feature;
    return false;
#endif
}

/* ============================================================
 * Timing
 * ============================================================ */

uint64_t
fossil_sys_cpu_timestamp(void)
{
#if defined(_WIN32) && (defined(_M_X64) || defined(_M_IX86))
    return (uint64_t)__rdtsc();

#elif defined(__GNUC__) && defined(__x86_64__)
    unsigned int lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;

#else
    return 0;
#endif
}
