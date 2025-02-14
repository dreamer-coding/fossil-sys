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
} fossil_sys_hostinfo_system_t;

// CPU information structure
typedef struct {
    char model[128];
    uint32_t cores;
    uint32_t threads;
    uint64_t frequency; // in Hz
} fossil_sys_hostinfo_cpu_t;

// Memory information structure
typedef struct {
    uint64_t total_memory; // in bytes
    uint64_t free_memory;  // in bytes
} fossil_sys_hostinfo_memory_t;

// GPU information structure
typedef struct {
    char model[128];
    uint64_t memory; // in bytes
} fossil_sys_hostinfo_gpu_t;

// Endianness information structure
typedef struct {
    int is_little_endian; // 1 if little-endian, 0 if big-endian
} fossil_sys_hostinfo_endianness_t;

/**
 * Retrieve system information.
 *
 * @param info A pointer to a structure that will be filled with system information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_system(fossil_sys_hostinfo_system_t *info);

/**
 * Retrieve CPU information.
 *
 * @param info A pointer to a structure that will be filled with CPU information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_cpu(fossil_sys_hostinfo_cpu_t *info);

/**
 * Retrieve memory information.
 *
 * @param info A pointer to a structure that will be filled with memory information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_memory(fossil_sys_hostinfo_memory_t *info);

/**
 * Retrieve GPU information.
 *
 * @param info A pointer to a structure that will be filled with GPU information.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_sys_hostinfo_get_gpu(fossil_sys_hostinfo_gpu_t *info);

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
         * Memory management class.
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
             * Get endianness information.
             *
             * @return A structure containing endianness information.
             */
            static fossil_sys_hostinfo_endianness_t get_endianness() {
                fossil_sys_hostinfo_endianness_t info;
                fossil_sys_hostinfo_get_endianness(&info);
                return info;
            }

        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
