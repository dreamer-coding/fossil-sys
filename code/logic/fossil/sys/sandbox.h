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
#ifndef FOSSIL_SYS_SANDBOX_H
#define FOSSIL_SYS_SANDBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------
 * Sandbox Types
 * ----------------------------------------------------- */

/* Execution mode */
typedef enum {
    FOSSIL_SANDBOX_MODE_NONE = 0,
    FOSSIL_SANDBOX_MODE_PROCESS,   /* isolated process */
    FOSSIL_SANDBOX_MODE_VM,        /* virtual machine */
    FOSSIL_SANDBOX_MODE_RESTRICTED /* syscall / resource limited */
} fossil_sys_sandbox_mode_t;

/* Resource limits */
typedef struct {
    uint64_t max_memory;      /* bytes */
    uint64_t max_cpu_time;    /* milliseconds */
    uint32_t max_files;
    uint32_t max_processes;
} fossil_sys_sandbox_limits_t;

/* Sandbox descriptor */
typedef struct {
    const char* id; /* string ID for AI/meta tracking */

    fossil_sys_sandbox_mode_t mode;
    fossil_sys_sandbox_limits_t limits;

    uint32_t pid;       /* host PID if applicable */
    void*    vm_handle; /* internal VM handle */
    int      status;    /* running / stopped / error */

} fossil_sys_sandbox_t;


/* ------------------------------------------------------
 * Lifecycle
 * ----------------------------------------------------- */

/* Create a sandbox instance */
bool fossil_sys_sandbox_create(
    fossil_sys_sandbox_mode_t mode,
    const fossil_sys_sandbox_limits_t* limits,
    fossil_sys_sandbox_t* out_box);

/* Destroy sandbox and release resources */
bool fossil_sys_sandbox_destroy(
    fossil_sys_sandbox_t* box);


/* ------------------------------------------------------
 * Execution
 * ----------------------------------------------------- */

/* Execute a command inside sandbox */
bool fossil_sys_sandbox_exec(
    fossil_sys_sandbox_t* box,
    const char* command);

/* Execute raw machine code inside sandbox VM */
bool fossil_sys_sandbox_exec_code(
    fossil_sys_sandbox_t* box,
    const void* code,
    size_t size);


/* ------------------------------------------------------
 * Control
 * ----------------------------------------------------- */

/* Stop sandbox execution */
bool fossil_sys_sandbox_stop(
    fossil_sys_sandbox_t* box);

/* Query sandbox status */
int fossil_sys_sandbox_status(
    const fossil_sys_sandbox_t* box);


/* ------------------------------------------------------
 * Introspection (AI / audit friendly)
 * ----------------------------------------------------- */

/* Get current memory usage */
uint64_t fossil_sys_sandbox_memory(
    const fossil_sys_sandbox_t* box);

/* Get CPU time consumed */
uint64_t fossil_sys_sandbox_cpu_time(
    const fossil_sys_sandbox_t* box);


#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_SYS_SANDBOX_H */
