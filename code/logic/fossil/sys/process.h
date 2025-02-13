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
#ifndef FOSSIL_SYS_PROCESS_H
#define FOSSIL_SYS_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE fossil_sys_process_t;
#else
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <errno.h>
    #include <signal.h>
    typedef pid_t fossil_sys_process_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Launches a new process.
 *
 * @param path The path to the executable.
 * @param args Null-terminated array of argument strings.
 * @return fossil_sys_process_t Handle to the created process, or NULL on failure.
 */
fossil_sys_process_t fossil_sys_process_create(const char *path, char *const args[]);

/**
 * @brief Waits for a process to exit and retrieves its status.
 *
 * @param process The process handle.
 * @param status Pointer to store the exit status.
 * @return int 0 on success, non-zero on failure.
 */
int fossil_sys_process_wait(fossil_sys_process_t process, int *status);

/**
 * @brief Terminates a running process.
 *
 * @param process The process handle.
 * @return int 0 on success, non-zero on failure.
 */
int fossil_sys_process_terminate(fossil_sys_process_t process);

/**
 * @brief Checks if a process is still running.
 *
 * @param process The process handle.
 * @return int 1 if running, 0 if not, -1 on error.
 */
int fossil_sys_process_is_running(fossil_sys_process_t process);

#ifdef __cplusplus
}

#include <string>
#include <vector>

/**
 * C++ wrapper for the process management API.
 */
namespace fossil {

    /**
     * Process management utilities.
     */
    namespace sys {
        /**
         * Process management class.
         */
        class Process {
        public:
            /**
             * Launches a new process.
             *
             * @param path The path to the executable.
             * @param args Null-terminated array of argument strings.
             * @return fossil_sys_process_t Handle to the created process, or NULL on failure.
             */
            fossil_sys_process_t spawn(const char *path, std::vector<std::string> args) {
                std::vector<char *> argv;
                for (const std::string &arg : args) {
                    argv.push_back(const_cast<char *>(arg.c_str()));
                }
                argv.push_back(nullptr);
                return fossil_sys_process_create(path, argv.data());
            }

            fossil_sys_process_t spawn(std::string path, std::vector<std::string> args) {
                return spawn(path.c_str(), args);
            }

            /**
             * Waits for a process to exit and retrieves its status.
             *
             * @param process The process handle.
             * @param status Pointer to store the exit status.
             * @return int 0 on success, non-zero on failure.
             */
            int wait(fossil_sys_process_t process, int *status) {
                return fossil_sys_process_wait(process, status);
            }

            /**
             * Terminates a running process.
             *
             * @param process The process handle.
             * @return int 0 on success, non-zero on failure.
             */
            int terminate(fossil_sys_process_t process) {
                return fossil_sys_process_terminate(process);
            }

            /**
             * Checks if a process is still running.
             *
             * @param process The process handle.
             * @return int 1 if running, 0 if not, -1 on error.
             */
            int is_running(fossil_sys_process_t process) {
                return fossil_sys_process_is_running(process);
            }

        };

    } // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_PROCESS_H */
