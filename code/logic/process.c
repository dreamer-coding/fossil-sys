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
#include "fossil/sys/process.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#endif


int fossil_sys_process_spawn(const char *path, char *const argv[], char *const envp[]) {
    if (!path || !argv) {
        fprintf(stderr, "Error: fossil_sys_process_spawn() - Invalid path or argument list.\n");
        return -1;
    }

#ifdef _WIN32
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(path, argv[0], NULL, NULL, FALSE, 0, envp, NULL, &si, &pi)) {
        fprintf(stderr, "Error: fossil_sys_process_spawn() - Failed to create process.\n");
        return -1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return pi.dwProcessId;
#else
    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error: fossil_sys_process_spawn() - Failed to fork process.\n");
        return -1;
    }

    if (pid == 0) {
        execve(path, argv, envp);
        fprintf(stderr, "Error: fossil_sys_process_spawn() - Failed to execute process.\n");
        exit(EXIT_FAILURE);
    }

    return pid;
#endif
}

int fossil_sys_process_wait(int pid, int *status) {
    if (pid <= 0) {
        fprintf(stderr, "Error: fossil_sys_process_wait() - Invalid process ID.\n");
        return -1;
    }

#ifdef _WIN32
    HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (hProcess == NULL) {
        fprintf(stderr, "Error: fossil_sys_process_wait() - Failed to open process.\n");
        return -1;
    }

    WaitForSingleObject(hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(hProcess, &exitCode)) {
        fprintf(stderr, "Error: fossil_sys_process_wait() - Failed to get exit code.\n");
        CloseHandle(hProcess);
        return -1;
    }

    if (status) {
        *status = exitCode;
    }

    CloseHandle(hProcess);
    return 0;
#else
    int stat_loc;
    int ret = waitpid(pid, &stat_loc, 0);
    if (ret == -1) {
        fprintf(stderr, "Error: fossil_sys_process_wait() - Failed to wait for process.\n");
        return -1;
    }

    if (status) {
        *status = WEXITSTATUS(stat_loc);
    }

    return 0;
#endif
}

int fossil_sys_process_terminate(int pid) {
    if (pid <= 0) {
        fprintf(stderr, "Error: fossil_sys_process_terminate() - Invalid process ID.\n");
        return -1;
    }

#ifdef _WIN32
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        fprintf(stderr, "Error: fossil_sys_process_terminate() - Failed to open process.\n");
        return -1;
    }

    if (!TerminateProcess(hProcess, 1)) {
        fprintf(stderr, "Error: fossil_sys_process_terminate() - Failed to terminate process.\n");
        CloseHandle(hProcess);
        return -1;
    }

    CloseHandle(hProcess);
    return 0;
#else
    int ret = kill(pid, SIGKILL);
    if (ret == -1) {
        fprintf(stderr, "Error: fossil_sys_process_terminate() - Failed to terminate process.\n");
        return -1;
    }

    return 0;
#endif
}

int fossil_sys_process_is_running(int pid) {
    if (pid <= 0) {
        fprintf(stderr, "Error: fossil_sys_process_is_running() - Invalid process ID.\n");
        return -1;
    }

#ifdef _WIN32
    HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (hProcess == NULL) {
        if (GetLastError() == ERROR_INVALID_PARAMETER) {
            return 0;
        }

        fprintf(stderr, "Error: fossil_sys_process_is_running() - Failed to open process.\n");
        return -1;
    }

    DWORD ret = WaitForSingleObject(hProcess, 0);
    CloseHandle(hProcess);

    if (ret == WAIT_TIMEOUT) {
        return 1;
    }

    return 0;
#else
    int ret = kill(pid, 0);
    if (ret == -1) {
        if (errno == ESRCH) {
            return 0;
        }

        fprintf(stderr, "Error: fossil_sys_process_is_running() - Failed to check process.\n");
        return -1;
    }

    return 1;
#endif
}

int fossil_sys_process_get_exit_code(int pid) {
    if (pid <= 0) {
        fprintf(stderr, "Error: fossil_sys_process_get_exit_code() - Invalid process ID.\n");
        return -1;
    }

#ifdef _WIN32
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hProcess == NULL) {
        fprintf(stderr, "Error: fossil_sys_process_get_exit_code() - Failed to open process.\n");
        return -1;
    }

    DWORD exitCode;
    if (!GetExitCodeProcess(hProcess, &exitCode)) {
        fprintf(stderr, "Error: fossil_sys_process_get_exit_code() - Failed to get exit code.\n");
        CloseHandle(hProcess);
        return -1;
    }

    CloseHandle(hProcess);
    return exitCode;
#else
    int stat_loc;
    int ret = waitpid(pid, &stat_loc, WNOHANG);
    if (ret == -1) {
        fprintf(stderr, "Error: fossil_sys_process_get_exit_code() - Failed to retrieve exit code.\n");
        return -1;
    }

    if (ret == 0) {
        return -1;  // Process is still running
    }

    return WEXITSTATUS(stat_loc);
#endif
}
