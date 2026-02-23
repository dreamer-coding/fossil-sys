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
#include <stdint.h>

#if defined(_WIN32)
    #include <windows.h>
    #include <intrin.h>
#elif defined(__APPLE__)
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/sysctl.h>
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
 * Internal helper to add a device
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

// Initialize the device subsystem and detect CPU/memory
int fossil_sys_device_init(void) {
    g_device_count = 0;

    uint32_t cores = 0;
    uint64_t mem_bytes = 0;

#if defined(_WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    cores = sysinfo.dwNumberOfProcessors;

    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    if (GlobalMemoryStatusEx(&mem)) {
        mem_bytes = mem.ullTotalPhys;
    }

#elif defined(__APPLE__)
    int nm[2];
    int count = 0;
    size_t len = sizeof(count);

    // CPU cores
    nm[0] = CTL_HW;
    nm[1] = HW_NCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);
    cores = (uint32_t)count;

    // Total memory
    int64_t mem64 = 0;
    len = sizeof(mem64);
    nm[1] = HW_MEMSIZE;
    sysctl(nm, 2, &mem64, &len, NULL, 0);
    mem_bytes = (uint64_t)mem64;

#else // Linux/other POSIX
    cores = (uint32_t)sysconf(_SC_NPROCESSORS_ONLN);
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        mem_bytes = (uint64_t)info.totalram * info.mem_unit;
    }
#endif

    // Add CPU as first device
    fossil_sys_device_add("cpu_0", FOSSIL_DEVICE_CPU, "CPU", mem_bytes, cores);

    // Add stub devices for GPU, Disk, Network, Sensor
    fossil_sys_device_add("gpu_0", FOSSIL_DEVICE_GPU, "GPU", 0, 0);
    fossil_sys_device_add("disk_0", FOSSIL_DEVICE_DISK, "Disk", 0, 0);
    fossil_sys_device_add("net_0", FOSSIL_DEVICE_NETWORK, "Network", 0, 0);
    fossil_sys_device_add("sensor_0", FOSSIL_DEVICE_SENSOR, "Sensor", 0, 0);

    return 0;
}

// Enumerate all detected devices
int fossil_sys_device_enumerate(fossil_sys_device_info_t* devices, size_t max_devices) {
    if (!devices) return -1;
    size_t count = (max_devices < g_device_count) ? max_devices : g_device_count;
    for (size_t i = 0; i < count; i++) {
        devices[i] = g_devices[i];
    }
    return (int)count;
}

// Query a single device by string ID
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

// Shutdown device subsystem
void fossil_sys_device_shutdown(void) {
    g_device_count = 0;
}
