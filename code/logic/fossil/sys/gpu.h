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
#ifndef FOSSIL_SYS_GPU_H
#define FOSSIL_SYS_GPU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Fossil System GPU — Core Types
 * ============================================================ */

typedef enum fossil_sys_gpu_vendor {
    FOSSIL_GPU_VENDOR_UNKNOWN = 0,
    FOSSIL_GPU_VENDOR_NVIDIA,
    FOSSIL_GPU_VENDOR_AMD,
    FOSSIL_GPU_VENDOR_INTEL,
    FOSSIL_GPU_VENDOR_APPLE,
    FOSSIL_GPU_VENDOR_QUALCOMM
} fossil_sys_gpu_vendor_t;

typedef enum fossil_sys_gpu_type {
    FOSSIL_GPU_TYPE_UNKNOWN = 0,
    FOSSIL_GPU_TYPE_INTEGRATED,
    FOSSIL_GPU_TYPE_DISCRETE,
    FOSSIL_GPU_TYPE_VIRTUAL
} fossil_sys_gpu_type_t;

/**
 * @brief GPU capability flags.
 */
typedef enum fossil_sys_gpu_capability {
    FOSSIL_GPU_CAP_COMPUTE        = 1u << 0,
    FOSSIL_GPU_CAP_GRAPHICS       = 1u << 1,
    FOSSIL_GPU_CAP_VIDEO_DECODE   = 1u << 2,
    FOSSIL_GPU_CAP_VIDEO_ENCODE   = 1u << 3,
    FOSSIL_GPU_CAP_RAY_TRACING    = 1u << 4
} fossil_sys_gpu_capability_t;

/**
 * @brief GPU device information.
 */
typedef struct fossil_sys_gpu_info {
    fossil_sys_gpu_vendor_t vendor;
    fossil_sys_gpu_type_t   type;
    uint32_t                device_id;
    uint64_t                vram_bytes;
    uint32_t                capabilities;
    char                    name[128];
} fossil_sys_gpu_info_t;

/* ============================================================
 * Enumeration
 * ============================================================ */

/**
 * @brief Get number of available GPU devices.
 */
uint32_t
fossil_sys_gpu_count(void);

/**
 * @brief Query GPU device info by index.
 */
bool
fossil_sys_gpu_query(uint32_t index, fossil_sys_gpu_info_t *info);

/* ============================================================
 * Capability Queries
 * ============================================================ */

bool
fossil_sys_gpu_has_capability(
    uint32_t index,
    fossil_sys_gpu_capability_t capability
);

/* ============================================================
 * Utilities
 * ============================================================ */

/**
 * @brief Return human-readable vendor string.
 */
const char *
fossil_sys_gpu_vendor_string(fossil_sys_gpu_vendor_t vendor);

#ifdef __cplusplus
}

/**
 * Fossil namespace.
 */
namespace fossil {

    /**
     * System namespace.
     */
    namespace sys {



    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
