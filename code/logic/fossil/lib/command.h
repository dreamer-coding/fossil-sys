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
#ifndef FOSSIL_SYS_COMMAND_H
#define FOSSIL_SYS_COMMAND_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute a system command.
 * @param command The command to execute.
 * @return 0 on success, nonzero on failure.
 */
int fossil_sys_command_exec(const char *command);

/**
 * Duplicate a file descriptor.
 * @param oldfd The original file descriptor.
 * @return The new file descriptor, or -1 on error.
 */
int fossil_sys_command_dup(int oldfd);

/**
 * Get system uptime in seconds.
 * @return The uptime in seconds, or -1 on failure.
 */
int64_t fossil_sys_command_uptime(void);

/**
 * Get available memory in bytes.
 * @return The available memory in bytes, or -1 on failure.
 */
int64_t fossil_sys_command_meminfo(void);

#ifdef __cplusplus
}

#include <string>

namespace fossil {

    namespace sys {

        /**
         * Command class to wrap C functions for command execution.
         */
        class Command {

        public:
            /**
             * Execute a system command.
             * @param command The command to execute.
             * @return 0 on success, nonzero on failure.
             */
            static int exec(const std::string &command) {
                return fossil_sys_command_exec(command.c_str());
            }

            /**
             * Duplicate a file descriptor.
             * @param oldfd The original file descriptor.
             * @return The new file descriptor, or -1 on error.
             */
            static int exec(const char *command) {
                return fossil_sys_command_exec(command);
            }

            /**
             * Duplicate a file descriptor.
             * @param oldfd The original file descriptor.
             * @return The new file descriptor, or -1 on error.
             */
            static int dup(int oldfd) {
                return fossil_sys_command_dup(oldfd);
            }

            /**
             * Get system uptime in seconds.
             * @return The uptime in seconds, or -1 on failure.
             */
            static int64_t uptime(void) {
                return fossil_sys_command_uptime();
            }

            /**
             * Get available memory in bytes.
             * @return The available memory in bytes, or -1 on failure.
             */
            static int64_t meminfo(void) {
                return fossil_sys_command_meminfo();
            }

        };
    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
