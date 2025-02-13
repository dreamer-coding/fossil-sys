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

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int pid;
    int exit_code;
    int status;
} fossil_sys_process_t;

/**
 * Launches a new process.
 * @param path Path to the executable.
 * @param argv NULL-terminated argument list.
 * @param envp NULL-terminated environment variable list (optional, NULL for default).
 * @return Process ID (PID) on success, -1 on failure.
 */
int fossil_sys_process_spawn(const char *path, char *const argv[], char *const envp[]);

/**
 * Waits for a process to complete.
 * @param pid Process ID to wait for.
 * @param status Pointer to store exit status (optional, NULL to ignore).
 * @return 0 on success, -1 on failure.
 */
int fossil_sys_process_wait(int pid, int *status);

/**
 * Terminates a process forcefully.
 * @param pid Process ID to terminate.
 * @return 0 on success, -1 on failure.
 */
int fossil_sys_process_terminate(int pid);

/**
 * Checks if a process is still running.
 * @param pid Process ID to check.
 * @return 1 if running, 0 if not, -1 on error.
 */
int fossil_sys_process_is_running(int pid);

/**
 * Retrieves the exit code of a terminated process.
 * @param pid Process ID.
 * @return Exit code on success, -1 on failure.
 */
int fossil_sys_process_get_exit_code(int pid);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_SYS_PROCESS_H */
