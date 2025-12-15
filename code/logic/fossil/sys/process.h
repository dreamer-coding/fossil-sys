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
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Fossil System Process — Core Types
 * ============================================================ */

typedef uint64_t fossil_pid_t;

/**
 * @brief Process execution state.
 */
typedef enum fossil_sys_process_state {
    FOSSIL_PROCESS_INVALID = 0,
    FOSSIL_PROCESS_CREATED,
    FOSSIL_PROCESS_RUNNING,
    FOSSIL_PROCESS_STOPPED,
    FOSSIL_PROCESS_EXITED,
    FOSSIL_PROCESS_FAILED
} fossil_sys_process_state_t;

/**
 * @brief Process exit information.
 */
typedef struct fossil_sys_process_exit {
    int     exit_code;
    bool    signaled;
    int     signal;
} fossil_sys_process_exit_t;

/**
 * @brief Process creation configuration.
 */
typedef struct fossil_sys_process_config {
    const char  *path;          /* Executable path */
    char *const *argv;          /* Argument vector */
    char *const *envp;          /* Environment (NULL = inherit) */
    const char  *workdir;       /* Working directory */
    bool         detached;      /* Run independently */
    bool         redirect_stdio;
} fossil_sys_process_config_t;

/**
 * @brief Opaque process handle.
 */
typedef struct fossil_sys_process fossil_sys_process_t;

/* ============================================================
 * Process Lifecycle
 * ============================================================ */

/**
 * @brief Create a process object (does not start execution).
 */
fossil_sys_process_t *
fossil_sys_process_create(const fossil_sys_process_config_t *config);

/**
 * @brief Start the process.
 */
bool
fossil_sys_process_start(fossil_sys_process_t *process);

/**
 * @brief Terminate the process.
 */
bool
fossil_sys_process_terminate(fossil_sys_process_t *process);

/**
 * @brief Force kill the process.
 */
bool
fossil_sys_process_kill(fossil_sys_process_t *process);

/**
 * @brief Wait for process completion.
 *
 * @param timeout_ms  Timeout in milliseconds (0 = infinite)
 */
bool
fossil_sys_process_wait(
    fossil_sys_process_t *process,
    uint32_t timeout_ms,
    fossil_sys_process_exit_t *exit_info
);

/**
 * @brief Destroy process object and release resources.
 */
void
fossil_sys_process_destroy(fossil_sys_process_t *process);

/* ============================================================
 * Process Information
 * ============================================================ */

fossil_pid_t
fossil_sys_process_pid(const fossil_sys_process_t *process);

fossil_sys_process_state_t
fossil_sys_process_state(const fossil_sys_process_t *process);

/**
 * @brief Check if process is still running.
 */
bool
fossil_sys_process_is_alive(const fossil_sys_process_t *process);

/* ============================================================
 * Task-Oriented Helpers
 * ============================================================ */

/**
 * @brief Run a process synchronously as a task.
 */
bool
fossil_sys_process_run_task(
    const fossil_sys_process_config_t *config,
    fossil_sys_process_exit_t *exit_info
);

/**
 * @brief Run a process asynchronously as a task.
 */
fossil_sys_process_t *
fossil_sys_process_spawn_task(const fossil_sys_process_config_t *config);

#ifdef __cplusplus
}

#include <string>
#include <stdexcept>

/**
 * Fossil namespace.
 */
namespace fossil {

    /**
     * System namespace.
     *
     * Contains helpers for working with tables of bitwise flags.
     * The functions in this namespace act as a thin C++ wrapper around the
     * underlying C API for bitmask parsing, formatting, validation, and lookup.
     */
    namespace sys {



    } // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
