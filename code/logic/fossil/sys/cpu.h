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
#ifndef FOSSIL_SYS_CPU_H
#define FOSSIL_SYS_CPU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Fossil System CPU — Core Types
 * ============================================================ */

typedef struct fossil_sys_cpu_info {
    uint32_t logical_cores;
    uint32_t physical_cores;
    uint32_t packages;
    uint32_t numa_nodes;
    uint64_t frequency_hz;
} fossil_sys_cpu_info_t;

/**
 * @brief CPU feature flags (portable subset).
 */
typedef enum fossil_sys_cpu_feature {
    FOSSIL_CPU_FEATURE_SSE2      = 1u << 0,
    FOSSIL_CPU_FEATURE_AVX       = 1u << 1,
    FOSSIL_CPU_FEATURE_AVX2      = 1u << 2,
    FOSSIL_CPU_FEATURE_NEON      = 1u << 3,
    FOSSIL_CPU_FEATURE_RDTSC     = 1u << 4
} fossil_sys_cpu_feature_t;

/**
 * @brief CPU affinity mask (portable abstraction).
 */
typedef struct fossil_sys_cpu_affinity {
    uint64_t mask;
} fossil_sys_cpu_affinity_t;

/* ============================================================
 * Topology & Info
 * ============================================================ */

bool
fossil_sys_cpu_query_info(fossil_sys_cpu_info_t *info);

uint32_t
fossil_sys_cpu_logical_cores(void);

uint32_t
fossil_sys_cpu_physical_cores(void);

/* ============================================================
 * Affinity
 * ============================================================ */

bool
fossil_sys_cpu_get_affinity(fossil_sys_cpu_affinity_t *affinity);

bool
fossil_sys_cpu_set_affinity(const fossil_sys_cpu_affinity_t *affinity);

/* ============================================================
 * Feature Detection
 * ============================================================ */

bool
fossil_sys_cpu_has_feature(fossil_sys_cpu_feature_t feature);

/* ============================================================
 * Timing
 * ============================================================ */

/**
 * @brief Read a fast CPU timestamp if available.
 *
 * Returns 0 if unsupported.
 */
uint64_t
fossil_sys_cpu_timestamp(void);

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
