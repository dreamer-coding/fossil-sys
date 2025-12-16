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
#ifndef FOSSIL_SYS_HOSTINFO_H
#define FOSSIL_SYS_HOSTINFO_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// System information structure
typedef struct {
    char os_name[128];
    char os_version[128];
    char kernel_version[128];
    char hostname[128];
    char username[128];
    char domain_name[128];
    char machine_type[128];
    char platform[128];
} fossil_sys_hostinfo_system_t;

// Architecture information structure
typedef struct {
    char architecture[128];
    char cpu[128];
    char cpu_cores[128];
    char cpu_threads[128];
    char cpu_frequency[128];
    char cpu_architecture[128];
} fossil_sys_hostinfo_architecture_t;

// Memory information structure
typedef struct {
    uint64_t total_memory;    // in bytes
    uint64_t free_memory;     // in bytes
    uint64_t used_memory;     // in bytes
    uint64_t available_memory;// in bytes
    uint64_t total_swap;      // in bytes
    uint64_t free_swap;       // in bytes
    uint64_t used_swap;       // in bytes
} fossil_sys_hostinfo_memory_t;

// Endianness information structure
typedef struct {
    int is_little_endian; // 1 if little-endian, 0 if big-endian
} fossil_sys_hostinfo_endianness_t;

/**
 * Power information structure
 */
typedef struct {
    int on_ac_power;         // 1 if on AC power, 0 otherwise
    int battery_present;     // 1 if battery is present, 0 otherwise
    int battery_charging;    // 1 if battery is charging, 0 otherwise
    int battery_percentage;  // Battery charge percentage (0-100), -1 if unknown
    int battery_seconds_left;// Estimated seconds left, -1 if unknown
} fossil_sys_hostinfo_power_t;

/**
 * CPU information structure
 */
typedef struct {
    char model[128];
    char vendor[128];
    int cores;
    int threads;
    float frequency_ghz;
    char features[256];
} fossil_sys_hostinfo_cpu_t;

/**
 * GPU information structure
 */
typedef struct {
    char name[128];
    char vendor[128];
    char driver_version[64];
    uint64_t memory_total;
    uint64_t memory_free;
    int compute_capability_major;
    int compute_capability_minor;
} fossil_sys_hostinfo_gpu_t;

/**
 * Storage information structure
 */
typedef struct {
    char device_name[128];
    char mount_point[128];
    uint64_t total_space;    // in bytes
    uint64_t free_space;     // in bytes
    uint64_t used_space;     // in bytes
    char filesystem_type[64];
} fossil_sys_hostinfo_storage_t;

/**
 * Environment information structure
 */
typedef struct {
    char shell[128];
    char home_dir[256];
    char lang[64];
    char path[1024];
    char _term[64];
    char user[128];
} fossil_sys_hostinfo_environment_t;

typedef struct {
    int is_virtual_machine;     // 1 if VM detected
    int is_container;           // 1 if running in container
    char hypervisor[128];       // e.g. "KVM", "VMware", "Hyper-V"
    char container_type[64];    // e.g. "docker", "podman", "lxc"
} fossil_sys_hostinfo_virtualization_t;

typedef struct {
    uint64_t uptime_seconds;
    uint64_t boot_time_epoch; // seconds since Unix epoch, 0 if unknown
} fossil_sys_hostinfo_uptime_t;

int fossil_sys_hostinfo_get_uptime(fossil_sys_hostinfo_uptime_t *info);

int fossil_sys_hostinfo_get_virtualization(
    fossil_sys_hostinfo_virtualization_t *info
);

/**
 * Retrieve storage information.
 *
 * @param info A pointer to a structure that will be filled with storage information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_storage(fossil_sys_hostinfo_storage_t *info);

/**
 * Retrieve environment information.
 *
 * @param info A pointer to a structure that will be filled with environment information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_environment(fossil_sys_hostinfo_environment_t *info);

/**
 * Retrieve CPU information.
 *
 * @param info A pointer to a structure that will be filled with CPU information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_cpu(fossil_sys_hostinfo_cpu_t *info);

/**
 * Retrieve GPU information.
 *
 * @param info A pointer to a structure that will be filled with GPU information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_gpu(fossil_sys_hostinfo_gpu_t *info);

/**
 * Retrieve power information.
 *
 * @param info A pointer to a structure that will be filled with power information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_power(fossil_sys_hostinfo_power_t *info);

/**
 * Retrieve system information.
 *
 * @param info A pointer to a structure that will be filled with system information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_system(fossil_sys_hostinfo_system_t *info);

/**
 * Retrieve architecture information.
 *
 * @param info A pointer to a structure that will be filled with architecture information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_architecture(fossil_sys_hostinfo_architecture_t *info);

/**
 * Retrieve memory information.
 *
 * @param info A pointer to a structure that will be filled with memory information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_memory(fossil_sys_hostinfo_memory_t *info);

/**
 * Retrieve endianness information.
 *
 * @param info A pointer to a structure that will be filled with endianness information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_endianness(fossil_sys_hostinfo_endianness_t *info);

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
         * Hostinfo management class.
         */
        class Hostinfo {
        public:

            /**
             * Get system information.
             *
             * @return A structure containing system information.
             */
            static fossil_sys_hostinfo_system_t get_system() {
                fossil_sys_hostinfo_system_t info;
                fossil_sys_hostinfo_get_system(&info);
                return info;
            }

            /**
             * Get architecture information.
             *
             * @return A structure containing architecture information.
             */
            static fossil_sys_hostinfo_architecture_t get_architecture() {
                fossil_sys_hostinfo_architecture_t info;
                fossil_sys_hostinfo_get_architecture(&info);
                return info;
            }

            /**
             * Get memory information.
             *
             * @return A structure containing memory information.
             */
            static fossil_sys_hostinfo_memory_t get_memory() {
                fossil_sys_hostinfo_memory_t info;
                fossil_sys_hostinfo_get_memory(&info);
                return info;
            }

            /**
             * Get endianness information.
             *
             * @return A structure containing endianness information.
             */
            static fossil_sys_hostinfo_endianness_t get_endianness() {
                fossil_sys_hostinfo_endianness_t info;
                fossil_sys_hostinfo_get_endianness(&info);
                return info;
            }

            /**
             * Get CPU information.
             *
             * @return A structure containing CPU information.
             */
            static fossil_sys_hostinfo_cpu_t get_cpu() {
                fossil_sys_hostinfo_cpu_t info;
                fossil_sys_hostinfo_get_cpu(&info);
                return info;
            }

            /**
             * Get GPU information.
             *
             * @return A structure containing GPU information.
             */
            static fossil_sys_hostinfo_gpu_t get_gpu() {
                fossil_sys_hostinfo_gpu_t info;
                fossil_sys_hostinfo_get_gpu(&info);
                return info;
            }

            /**
             * Get power information.
             *
             * @return A structure containing power information.
             */
            static fossil_sys_hostinfo_power_t get_power() {
                fossil_sys_hostinfo_power_t info;
                fossil_sys_hostinfo_get_power(&info);
                return info;
            }

            /**
             * Get storage information.
             *
             * @return A structure containing storage information.
             */
            static fossil_sys_hostinfo_storage_t get_storage() {
                fossil_sys_hostinfo_storage_t info;
                fossil_sys_hostinfo_get_storage(&info);
                return info;
            }

            /**
             * Get environment information.
             *
             * @return A structure containing environment information.
             */
            static fossil_sys_hostinfo_environment_t get_environment() {
                fossil_sys_hostinfo_environment_t info;
                fossil_sys_hostinfo_get_environment(&info);
                return info;
            }

        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
