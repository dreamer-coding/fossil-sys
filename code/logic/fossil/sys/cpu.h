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

/**
 * @brief Queries detailed information about the system's CPU.
 *
 * This function fills the provided `fossil_sys_cpu_info_t` structure with
 * information about the current CPU, such as vendor, model, features, and
 * other relevant data. The exact fields populated depend on the implementation
 * and platform.
 *
 * @param[out] info Pointer to a `fossil_sys_cpu_info_t` structure that will be
 *                  populated with CPU information.
 * @return true if the information was successfully queried and the structure
 *         was populated; false otherwise.
 */
bool
fossil_sys_cpu_query_info(fossil_sys_cpu_info_t *info);

/**
 * @brief Retrieves the number of logical CPU cores available on the system.
 *
 * Logical cores represent the total number of hardware threads that the CPU
 * can execute simultaneously, including those provided by technologies such as
 * Hyper-Threading or SMT (Simultaneous Multi-Threading).
 *
 * @return The number of logical CPU cores present on the system.
 */
uint32_t
fossil_sys_cpu_logical_cores(void);

/**
 * @brief Retrieves the number of physical CPU cores available on the system.
 *
 * Physical cores refer to the actual, physical processing units present in the
 * CPU, excluding additional logical cores provided by Hyper-Threading or SMT.
 *
 * @return The number of physical CPU cores present on the system.
 */
uint32_t
fossil_sys_cpu_physical_cores(void);

/* ============================================================
 * Affinity
 * ============================================================ */

/**
 * @brief Retrieves the current CPU affinity mask for the calling process or thread.
 *
 * This function fills the provided affinity structure with the current CPU affinity,
 * indicating the set of CPUs on which the process or thread is eligible to run.
 *
 * @param[out] affinity Pointer to a fossil_sys_cpu_affinity_t structure that will be
 *                      populated with the current CPU affinity mask.
 * @return true if the affinity was successfully retrieved; false otherwise.
 *         On failure, the contents of the affinity structure are undefined.
 */
bool
fossil_sys_cpu_get_affinity(fossil_sys_cpu_affinity_t *affinity);

/**
 * @brief Sets the CPU affinity mask for the calling process or thread.
 *
 * This function applies the specified CPU affinity, restricting the process or thread
 * to run only on the CPUs specified in the provided affinity structure.
 *
 * @param[in] affinity Pointer to a fossil_sys_cpu_affinity_t structure containing
 *                     the desired CPU affinity mask to be set.
 * @return true if the affinity was successfully set; false otherwise.
 *         On failure, the affinity of the process or thread remains unchanged.
 */
bool
fossil_sys_cpu_set_affinity(const fossil_sys_cpu_affinity_t *affinity);

/* ============================================================
 * Feature Detection
 * ============================================================ */

/**
 * @brief if if the current CPU supports a specific feature.
 *
 * @param[in] feature The CPU feature to check for support.
 * @return true if the CPU supports the specified feature; false otherwise.
 */
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

        /**
         * @class CPU
         * @brief Represents the central processing unit (CPU) abstraction for the system.
         *
         * This class encapsulates the core logic and state of a CPU within the system.
         * It is responsible for managing CPU-specific operations, such as instruction execution,
         * register management, and interaction with other system components.
         *
         * Usage:
         * - Instantiate the CPU class to simulate or control CPU behavior.
         * - Provides public methods to interact with and manipulate CPU state.
         *
         * Note:
         * - The detailed implementation and available methods should be referenced in the corresponding
         *   source file or extended documentation.
         */
        class CPU {
            public:
            /**
             * @brief Query detailed information about the system's CPU.
             *
             * Fills the provided fossil_sys_cpu_info_t structure with information
             * about the current CPU, such as core counts and frequency.
             *
             * @param info Pointer to a fossil_sys_cpu_info_t structure to populate.
             * @return true if the information was successfully queried; false otherwise.
             */
            static bool query_info(fossil_sys_cpu_info_t* info) {
                return fossil_sys_cpu_query_info(info);
            }

            /**
             * @brief Get the number of logical CPU cores.
             *
             * Returns the total number of hardware threads available, including
             * those provided by Hyper-Threading or SMT.
             *
             * @return Number of logical CPU cores.
             */
            static uint32_t logical_cores() {
                return fossil_sys_cpu_logical_cores();
            }

            /**
             * @brief Get the number of physical CPU cores.
             *
             * Returns the number of actual physical processing units, excluding
             * additional logical cores from Hyper-Threading or SMT.
             *
             * @return Number of physical CPU cores.
             */
            static uint32_t physical_cores() {
                return fossil_sys_cpu_physical_cores();
            }

            /**
             * @brief Retrieve the current CPU affinity mask.
             *
             * Fills the provided affinity structure with the current CPU affinity,
             * indicating the set of CPUs on which the process or thread can run.
             *
             * @param affinity Pointer to a fossil_sys_cpu_affinity_t structure to populate.
             * @return true if the affinity was successfully retrieved; false otherwise.
             */
            static bool get_affinity(fossil_sys_cpu_affinity_t* affinity) {
                return fossil_sys_cpu_get_affinity(affinity);
            }

            /**
             * @brief Set the CPU affinity mask.
             *
             * Applies the specified CPU affinity, restricting the process or thread
             * to run only on the CPUs specified in the provided affinity structure.
             *
             * @param affinity Pointer to a fossil_sys_cpu_affinity_t structure containing the mask.
             * @return true if the affinity was successfully set; false otherwise.
             */
            static bool set_affinity(const fossil_sys_cpu_affinity_t* affinity) {
                return fossil_sys_cpu_set_affinity(affinity);
            }

            /**
             * @brief Check if the CPU supports a specific feature.
             *
             * Determines if the current CPU supports the specified feature flag.
             *
             * @param feature The CPU feature to check.
             * @return true if the CPU supports the feature; false otherwise.
             */
            static bool has_feature(fossil_sys_cpu_feature_t feature) {
                return fossil_sys_cpu_has_feature(feature);
            }

            /**
             * @brief Read a fast CPU timestamp if available.
             *
             * Returns a high-resolution timestamp from the CPU, or 0 if unsupported.
             *
             * @return CPU timestamp value, or 0 if not available.
             */
            static uint64_t timestamp() {
                return fossil_sys_cpu_timestamp();
            }

        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
