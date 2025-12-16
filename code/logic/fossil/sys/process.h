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
#ifndef FOSSIL_SYS_PROCESS_H
#define FOSSIL_SYS_PROCESS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FOSSIL_SYS_PROCESS_NAME_MAX 256
#define FOSSIL_SYS_PROCESS_ENV_MAX 1024

typedef struct {
    uint32_t pid;                      // Process ID
    uint32_t ppid;                     // Parent PID
    char name[FOSSIL_SYS_PROCESS_NAME_MAX];  // Process name
    uint64_t memory_bytes;             // Resident memory
    uint64_t virtual_memory_bytes;     // Virtual memory
    float cpu_percent;                 // CPU usage %
    uint32_t thread_count;             // Number of threads
} fossil_sys_process_info_t;

/**
 * Process list container
 */
#define FOSSIL_SYS_PROCESS_MAX 1024
typedef struct {
    size_t count;
    fossil_sys_process_info_t list[FOSSIL_SYS_PROCESS_MAX];
} fossil_sys_process_list_t;

/**
 * Get current process PID
 */
uint32_t fossil_sys_process_get_pid(void);

/**
 * Get process name by PID
 */
int fossil_sys_process_get_name(uint32_t pid, char *name, size_t name_len);

/**
 * Get process info by PID
 */
int fossil_sys_process_get_info(uint32_t pid, fossil_sys_process_info_t *info);

/**
 * Get list of all processes
 */
int fossil_sys_process_list(fossil_sys_process_list_t *plist);

/**
 * Terminate process by PID
 *
 * @param pid Process ID
 * @param force 1 = force kill, 0 = graceful
 */
int fossil_sys_process_terminate(uint32_t pid, int force);

/**
 * Retrieve environment variables of a process (best-effort)
 *
 * @param pid Process ID
 * @param buffer Preallocated buffer of length buf_len
 * @param buf_len Size of buffer
 * @return Number of bytes written, -1 on error
 */
int fossil_sys_process_get_environment(uint32_t pid, char *buffer, size_t buf_len);

#ifdef __cplusplus
}
#include <string>

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
