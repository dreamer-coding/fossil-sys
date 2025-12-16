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
#include "fossil/sys/gpu.h"
#include <string.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    /* No Metal headers here by design */
#else
    #include <unistd.h>
#endif

/* ============================================================
 * Internal Helpers
 * ============================================================ */

static void
fossil_sys_gpu_clear_info(fossil_sys_gpu_info_t *info)
{
    memset(info, 0, sizeof(*info));
    info->vendor = FOSSIL_GPU_VENDOR_UNKNOWN;
    info->type   = FOSSIL_GPU_TYPE_UNKNOWN;
}

/* ============================================================
 * Enumeration
 * ============================================================ */

uint32_t
fossil_sys_gpu_count(void)
{
#if defined(_WIN32)
    return 1; /* Best-effort default */
#elif defined(__APPLE__)
    return 1;
#elif defined(__linux__)
    /* Conservative: detect presence, not topology */
    return 1;
#else
    return 0;
#endif
}

bool
fossil_sys_gpu_query(uint32_t index, fossil_sys_gpu_info_t *info)
{
    if (!info)
        return false;

    if (index >= fossil_sys_gpu_count())
        return false;

    fossil_sys_gpu_clear_info(info);

#if defined(_WIN32)

    info->vendor       = FOSSIL_GPU_VENDOR_UNKNOWN;
    info->type         = FOSSIL_GPU_TYPE_DISCRETE;
    info->capabilities = FOSSIL_GPU_CAP_GRAPHICS | FOSSIL_GPU_CAP_COMPUTE;
    info->vram_bytes   = 0;
    info->device_id    = 0;
    strncpy(info->name, "Windows GPU", sizeof(info->name) - 1);

#elif defined(__APPLE__)

    info->vendor       = FOSSIL_GPU_VENDOR_APPLE;
    info->type         = FOSSIL_GPU_TYPE_INTEGRATED;
    info->capabilities = FOSSIL_GPU_CAP_GRAPHICS | FOSSIL_GPU_CAP_COMPUTE;
    info->vram_bytes   = 0;
    info->device_id    = 0;
    strncpy(info->name, "Apple GPU", sizeof(info->name) - 1);

#elif defined(__linux__)

    info->vendor       = FOSSIL_GPU_VENDOR_UNKNOWN;
    info->type         = FOSSIL_GPU_TYPE_UNKNOWN;
    info->capabilities = FOSSIL_GPU_CAP_GRAPHICS;
    info->vram_bytes   = 0;
    info->device_id    = 0;
    strncpy(info->name, "Linux GPU", sizeof(info->name) - 1);

#else
    return false;
#endif

    return true;
}

/* ============================================================
 * Capability Queries
 * ============================================================ */

bool
fossil_sys_gpu_has_capability(
    uint32_t index,
    fossil_sys_gpu_capability_t capability
)
{
    fossil_sys_gpu_info_t info;
    if (!fossil_sys_gpu_query(index, &info))
        return false;

    return (info.capabilities & capability) != 0;
}

/* ============================================================
 * Utilities
 * ============================================================ */

const char *
fossil_sys_gpu_vendor_string(fossil_sys_gpu_vendor_t vendor)
{
    switch (vendor) {
        case FOSSIL_GPU_VENDOR_NVIDIA:   return "NVIDIA";
        case FOSSIL_GPU_VENDOR_AMD:      return "AMD";
        case FOSSIL_GPU_VENDOR_INTEL:    return "Intel";
        case FOSSIL_GPU_VENDOR_APPLE:    return "Apple";
        case FOSSIL_GPU_VENDOR_QUALCOMM: return "Qualcomm";
        default:                         return "Unknown";
    }
}
