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
#ifndef FOSSIL_SYS_DEVICE_H
#define FOSSIL_SYS_DEVICE_H

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------
 * Device Types
 * ----------------------------------------------------- */
typedef enum {
    FOSSIL_DEVICE_UNKNOWN,
    FOSSIL_DEVICE_CPU,
    FOSSIL_DEVICE_GPU,
    FOSSIL_DEVICE_DISK,
    FOSSIL_DEVICE_NETWORK,
    FOSSIL_DEVICE_SENSOR
} fossil_sys_device_type_t;

/* ------------------------------------------------------
 * Device Information
 * ----------------------------------------------------- */
typedef struct {
    const char* id;                // string ID for AI/tracking
    fossil_sys_device_type_t type;
    const char* name;              // human-readable
    uint64_t memory_bytes;         // if applicable
    uint32_t cores;                // CPU/GPU cores
} fossil_sys_device_info_t;

/* ------------------------------------------------------
 * Device API
 * ----------------------------------------------------- */

// Initialize device subsystem
int fossil_sys_device_init(void);

// Enumerate all devices
int fossil_sys_device_enumerate(fossil_sys_device_info_t* devices, size_t max_devices);

// Query a single device by string ID
int fossil_sys_device_query(const char* id, fossil_sys_device_info_t* out_device);

// Shutdown device subsystem
void fossil_sys_device_shutdown(void);

#endif /* FOSSIL_SYS_DEVICE_H */
