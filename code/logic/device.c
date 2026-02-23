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
#include "fossil/sys/device.h"

#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
    #include <windows.h>
    #include <intrin.h>
#else
    #include <unistd.h>
    #include <sys/sysinfo.h>
#endif

/* ------------------------------------------------------
 * Internal storage
 * ----------------------------------------------------- */
#define FOSSIL_SYS_MAX_DEVICES 32
static fossil_sys_device_info_t g_devices[FOSSIL_SYS_MAX_DEVICES];
static size_t g_device_count = 0;

/* ------------------------------------------------------
 * Helpers
 * ----------------------------------------------------- */
static void fossil_sys_device_add(const char* id, fossil_sys_device_type_t type,
                                  const char* name, uint64_t memory_bytes, uint32_t cores) {
    if (g_device_count >= FOSSIL_SYS_MAX_DEVICES) return;
    g_devices[g_device_count].id = id;
    g_devices[g_device_count].type = type;
    g_devices[g_device_count].name = name;
    g_devices[g_device_count].memory_bytes = memory_bytes;
    g_devices[g_device_count].cores = cores;
    g_device_count++;
}

/* ------------------------------------------------------
 * Public API
 * ----------------------------------------------------- */

int fossil_sys_device_init(void) {
    g_device_count = 0;

    // CPU detection
#if defined(_WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    fossil_sys_device_add("cpu_0", FOSSIL_DEVICE_CPU, "CPU", 0, sysinfo.dwNumberOfProcessors);
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    fossil_sys_device_add("cpu_0", FOSSIL_DEVICE_CPU, "CPU", 0, (uint32_t)nprocs);
#endif

    // Memory info
#if defined(_WIN32)
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    if (GlobalMemoryStatusEx(&mem)) {
        g_devices[0].memory_bytes = mem.ullTotalPhys;
    }
#else
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        g_devices[0].memory_bytes = (uint64_t)info.totalram * info.mem_unit;
    }
#endif

    // TODO: Add GPU, Disk, Network, Sensors here
    fossil_sys_device_add("gpu_0", FOSSIL_DEVICE_GPU, "GPU", 0, 0);
    fossil_sys_device_add("disk_0", FOSSIL_DEVICE_DISK, "Disk", 0, 0);
    fossil_sys_device_add("net_0", FOSSIL_DEVICE_NETWORK, "Network", 0, 0);
    fossil_sys_device_add("sensor_0", FOSSIL_DEVICE_SENSOR, "Sensor", 0, 0);

    return 0;
}

int fossil_sys_device_enumerate(fossil_sys_device_info_t* devices, size_t max_devices) {
    size_t count = (max_devices < g_device_count) ? max_devices : g_device_count;
    for (size_t i = 0; i < count; i++) {
        devices[i] = g_devices[i];
    }
    return (int)count;
}

int fossil_sys_device_query(const char* id, fossil_sys_device_info_t* out_device) {
    if (!id || !out_device) return -1;
    for (size_t i = 0; i < g_device_count; i++) {
        if (strcmp(g_devices[i].id, id) == 0) {
            *out_device = g_devices[i];
            return 0;
        }
    }
    return -1; // not found
}

void fossil_sys_device_shutdown(void) {
    g_device_count = 0;
}
