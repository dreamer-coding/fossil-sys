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
#include "fossil/sys/hostinfo.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

int fossil_sys_hostinfo_get_system(fossil_sys_hostinfo_system_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osvi)) return -1;
    snprintf(info->os_name, sizeof(info->os_name), "Windows");
    snprintf(info->os_version, sizeof(info->os_version), "%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion);
    snprintf(info->kernel_version, sizeof(info->kernel_version), "%lu", osvi.dwBuildNumber);
#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
#endif
    return 0;
}

int fossil_sys_hostinfo_get_cpu(fossil_sys_hostinfo_cpu_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    info->cores = sysinfo.dwNumberOfProcessors;
    info->threads = sysinfo.dwNumberOfProcessors;
    snprintf(info->model, sizeof(info->model), "Unknown");
    info->frequency = 0;
#else
    info->cores = sysconf(_SC_NPROCESSORS_ONLN);
    info->threads = sysconf(_SC_NPROCESSORS_CONF);
    snprintf(info->model, sizeof(info->model), "Generic CPU");
    info->frequency = 0;
#endif
    return 0;
}

int fossil_sys_hostinfo_get_memory(fossil_sys_hostinfo_memory_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (!GlobalMemoryStatusEx(&statex)) return -1;
    info->total_memory = statex.ullTotalPhys;
    info->free_memory = statex.ullAvailPhys;
#else
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) return -1;
    info->total_memory = sys_info.totalram;
    info->free_memory = sys_info.freeram;
#endif
    return 0;
}

int fossil_sys_hostinfo_get_gpu(fossil_sys_hostinfo_gpu_t *info) {
    if (!info) return -1;
    snprintf(info->model, sizeof(info->model), "Unknown GPU");
    info->memory = 0;
    return 0;
}

int fossil_sys_hostinfo_get_endianness(fossil_sys_hostinfo_endianness_t *info) {
    if (!info) return -1;
    uint16_t test = 0x0001;
    info->is_little_endian = (*(uint8_t*)&test) ? 1 : 0;
    return 0;
}
