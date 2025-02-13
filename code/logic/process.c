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
#ifdef _WIN32
    #include <windows.h>
#else
    #include <errno.h>
    #include <signal.h>
#endif

fossil_sys_process_t fossil_sys_process_create(const char *path, char *const args[]) {
#ifdef _WIN32
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    // Construct the command line string
    char cmdline[1024] = {0};
    snprintf(cmdline, sizeof(cmdline), "\"%s\"", path);
    for (char *const *arg = args; *arg != NULL; ++arg) {
        strncat(cmdline, " ", sizeof(cmdline) - strlen(cmdline) - 1);
        strncat(cmdline, *arg, sizeof(cmdline) - strlen(cmdline) - 1);
    }

    if (!CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return NULL;
    }
    CloseHandle(pi.hThread);
    return pi.hProcess;
#else
    pid_t pid = fork();
    if (pid == 0) {
        execvp(path, args);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        return -1;
    }
    return pid;
#endif
}

int fossil_sys_process_wait(fossil_sys_process_t process, int *status) {
#ifdef _WIN32
    if (WaitForSingleObject(process, INFINITE) == WAIT_FAILED) {
        return -1;
    }
    DWORD exit_code;
    if (!GetExitCodeProcess(process, &exit_code)) {
        return -1;
    }
    *status = (int)exit_code;
    CloseHandle(process);
    return 0;
#else
    return waitpid(process, status, 0) == -1 ? -1 : 0;
#endif
}

int fossil_sys_process_terminate(fossil_sys_process_t process) {
#ifdef _WIN32
    return TerminateProcess(process, 1) ? 0 : -1;
#else
    return kill(process, SIGTERM);
#endif
}

int fossil_sys_process_is_running(fossil_sys_process_t process) {
#ifdef _WIN32
    DWORD exit_code;
    if (!GetExitCodeProcess(process, &exit_code)) {
        return -1;
    }
    return exit_code == STILL_ACTIVE ? 1 : 0;
#else
    return kill(process, 0) == 0 ? 1 : (errno == ESRCH ? 0 : -1);
#endif
}
