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
 * @brief Create a new process object based on the given configuration.
 *
 * This function allocates and initializes a process object using the
 * specified configuration. The process is not started until
 * fossil_sys_process_start() is called.
 *
 * @param config Pointer to the process configuration structure.
 * @return Pointer to the created process object, or NULL on failure.
 */
fossil_sys_process_t *
fossil_sys_process_create(const fossil_sys_process_config_t *config);

/**
 * @brief Start execution of the process.
 *
 * This function launches the process previously created with
 * fossil_sys_process_create(). On success, the process will begin
 * executing asynchronously.
 *
 * @param process Pointer to the process object.
 * @return true if the process was started successfully, false otherwise.
 */
bool
fossil_sys_process_start(fossil_sys_process_t *process);

/**
 * @brief Request graceful termination of the process.
 *
 * This function attempts to terminate the process by sending a termination
 * signal. The process may perform cleanup before exiting.
 *
 * @param process Pointer to the process object.
 * @return true if the termination request was sent successfully, false otherwise.
 */
bool
fossil_sys_process_terminate(fossil_sys_process_t *process);

/**
 * @brief Forcefully kill the process.
 *
 * This function immediately kills the process without allowing it to
 * perform cleanup. Use with caution.
 *
 * @param process Pointer to the process object.
 * @return true if the process was killed successfully, false otherwise.
 */
bool
fossil_sys_process_kill(fossil_sys_process_t *process);

/**
 * @brief Wait for the process to complete execution.
 *
 * This function blocks until the process exits or the specified timeout
 * elapses. If exit_info is not NULL, it will be populated with the
 * process's exit status.
 *
 * @param process     Pointer to the process object.
 * @param timeout_ms  Timeout in milliseconds (0 means wait indefinitely).
 * @param exit_info   Pointer to a structure to receive exit information, or NULL.
 * @return true if the process exited, false if the timeout was reached.
 */
bool
fossil_sys_process_wait(
    fossil_sys_process_t *process,
    uint32_t timeout_ms,
    fossil_sys_process_exit_t *exit_info
);

/**
 * @brief Destroy the process object and release all associated resources.
 *
 * This function cleans up the process object. If the process is still
 * running, it will not be terminated automatically.
 *
 * @param process Pointer to the process object to destroy.
 */
void
fossil_sys_process_destroy(fossil_sys_process_t *process);

/* ============================================================
 * Process Information
 * ============================================================ */

/**
 * @brief Retrieve the process identifier (PID).
 *
 * Returns the operating system process ID for the given process object.
 *
 * @param process Pointer to the process object.
 * @return The process ID, or 0 if unavailable.
 */
fossil_pid_t
fossil_sys_process_pid(const fossil_sys_process_t *process);

/**
 * @brief Get the current execution state of the process.
 *
 * Returns the state of the process, such as running, stopped, or exited.
 *
 * @param process Pointer to the process object.
 * @return The current process state.
 */
fossil_sys_process_state_t
fossil_sys_process_state(const fossil_sys_process_t *process);

/**
 * @brief Check if the process is currently running.
 *
 * Returns true if the process is still alive and executing.
 *
 * @param process Pointer to the process object.
 * @return true if the process is running, false otherwise.
 */
bool
fossil_sys_process_is_alive(const fossil_sys_process_t *process);

/* ============================================================
 * Task-Oriented Helpers
 * ============================================================ */

/**
 * @brief Run a process synchronously as a task.
 *
 * This helper function creates, starts, waits for, and destroys a process
 * in a single call. The function blocks until the process exits.
 *
 * @param config    Pointer to the process configuration.
 * @param exit_info Pointer to receive exit information, or NULL.
 * @return true if the process ran and exited successfully, false otherwise.
 */
bool
fossil_sys_process_run_task(
    const fossil_sys_process_config_t *config,
    fossil_sys_process_exit_t *exit_info
);

/**
 * @brief Run a process asynchronously as a task.
 *
 * This helper function creates and starts a process, returning the process
 * object for further management. The process runs asynchronously.
 *
 * @param config Pointer to the process configuration.
 * @return Pointer to the process object, or NULL on failure.
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

        /**
         * @brief C++ RAII wrapper for Fossil system process management.
         *
         * This class encapsulates the lifecycle and management of a system process,
         * providing a safe and convenient C++ interface over the C API.
         */
        class Process
        {
        public:
            using pid_type = ::fossil_pid_t;
            using state_type = ::fossil_sys_process_state_t;
            using exit_info_type = ::fossil_sys_process_exit_t;
            using config_type = ::fossil_sys_process_config_t;

            /**
             * @brief Construct a Process from a configuration (does not start).
             *
             * @param config Process configuration.
             * @throws std::runtime_error if creation fails.
             */
            explicit Process(const config_type& config)
            : handle_(::fossil_sys_process_create(&config))
            {
            if (!handle_)
                throw std::runtime_error("Failed to create process");
            }

            /**
             * @brief Construct a Process from an existing handle (for spawn_task).
             *
             * @param handle Existing process handle.
             * @throws std::runtime_error if handle is null.
             */
            explicit Process(::fossil_sys_process_t* handle)
            : handle_(handle)
            {
            if (!handle_)
                throw std::runtime_error("Invalid process handle");
            }

            // Non-copyable
            Process(const Process&) = delete;
            Process& operator=(const Process&) = delete;

            /**
             * @brief Move constructor.
             *
             * Transfers ownership of the process handle.
             */
            Process(Process&& other) noexcept : handle_(other.handle_)
            {
            other.handle_ = nullptr;
            }

            /**
             * @brief Move assignment operator.
             *
             * Cleans up current handle and takes ownership from other.
             */
            Process& operator=(Process&& other) noexcept
            {
            if (this != &other) {
                cleanup();
                handle_ = other.handle_;
                other.handle_ = nullptr;
            }
            return *this;
            }

            /**
             * @brief Destructor.
             *
             * Cleans up the process handle and associated resources.
             */
            ~Process()
            {
            cleanup();
            }

            /**
             * @brief Start the process.
             *
             * @return true if started successfully, false otherwise.
             */
            bool start()
            {
            return ::fossil_sys_process_start(handle_);
            }

            /**
             * @brief Request graceful termination of the process.
             *
             * @return true if termination request was sent, false otherwise.
             */
            bool terminate()
            {
            return ::fossil_sys_process_terminate(handle_);
            }

            /**
             * @brief Forcefully kill the process.
             *
             * @return true if the process was killed, false otherwise.
             */
            bool kill()
            {
            return ::fossil_sys_process_kill(handle_);
            }

            /**
             * @brief Wait for the process to exit.
             *
             * @param timeout_ms Timeout in milliseconds (0 = infinite).
             * @param info Optional pointer to receive exit information.
             * @return true if the process exited, false if timeout reached.
             */
            bool wait(uint32_t timeout_ms = 0, exit_info_type* info = nullptr)
            {
            return ::fossil_sys_process_wait(handle_, timeout_ms, info);
            }

            /**
             * @brief Get the process ID (PID).
             *
             * @return The process ID, or 0 if unavailable.
             */
            pid_type pid() const
            {
            return ::fossil_sys_process_pid(handle_);
            }

            /**
             * @brief Get the current execution state of the process.
             *
             * @return The current process state.
             */
            state_type state() const
            {
            return ::fossil_sys_process_state(handle_);
            }

            /**
             * @brief Check if the process is currently running.
             *
             * @return true if the process is alive, false otherwise.
             */
            bool is_alive() const
            {
            return ::fossil_sys_process_is_alive(handle_);
            }

            /**
             * @brief Access the underlying process handle.
             *
             * @return Pointer to the native process handle.
             */
            ::fossil_sys_process_t* native_handle() { return handle_; }

            /**
             * @brief Access the underlying process handle (const).
             *
             * @return Const pointer to the native process handle.
             */
            const ::fossil_sys_process_t* native_handle() const { return handle_; }

            /**
             * @brief Run a process synchronously as a task.
             *
             * @param config Process configuration.
             * @param info Optional pointer to receive exit information.
             * @return true if the process ran and exited successfully, false otherwise.
             */
            static bool run_task(const config_type& config, exit_info_type* info = nullptr)
            {
            return ::fossil_sys_process_run_task(&config, info);
            }

            /**
             * @brief Spawn a process asynchronously as a task.
             *
             * @param config Process configuration.
             * @return Process object managing the spawned process.
             * @throws std::runtime_error if spawning fails.
             */
            static Process spawn_task(const config_type& config)
            {
            ::fossil_sys_process_t* h = ::fossil_sys_process_spawn_task(&config);
            if (!h)
                throw std::runtime_error("Failed to spawn process");
            return Process(h);
            }

        private:
            ::fossil_sys_process_t* handle_ = nullptr;

            /**
             * @brief Cleanup helper to destroy the process handle.
             */
            void cleanup() {
                if (handle_) {
                    ::fossil_sys_process_destroy(handle_);
                    handle_ = nullptr;
                }
            }
        };

    } // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
