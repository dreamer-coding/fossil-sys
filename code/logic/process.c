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
#include "fossil/sys/process.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <errno.h>
#endif

/* ============================================================
 * Internal Structure
 * ============================================================ */

struct fossil_sys_process {
    fossil_sys_process_config_t config;
    fossil_sys_process_state_t  state;
    fossil_pid_t                pid;

#if defined(_WIN32)
    PROCESS_INFORMATION         pi;
#else
    pid_t                       child_pid;
#endif
};

/* ============================================================
 * Helpers
 * ============================================================ */

static void
fossil_sys_process_init(
    fossil_sys_process_t *p,
    const fossil_sys_process_config_t *cfg)
{
    memset(p, 0, sizeof(*p));
    p->config = *cfg;
    p->state  = FOSSIL_PROCESS_CREATED;
}

/* ============================================================
 * Lifecycle
 * ============================================================ */

fossil_sys_process_t *
fossil_sys_process_create(const fossil_sys_process_config_t *config)
{
    if (!config || !config->path)
        return NULL;

    fossil_sys_process_t *p =
        (fossil_sys_process_t *)calloc(1, sizeof(*p));
    if (!p)
        return NULL;

    fossil_sys_process_init(p, config);
    return p;
}

bool
fossil_sys_process_start(fossil_sys_process_t *process)
{
    if (!process || process->state != FOSSIL_PROCESS_CREATED)
        return false;

#if defined(_WIN32)

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    BOOL ok = CreateProcessA(
        NULL,
        (LPSTR)process->config.path,
        NULL,
        NULL,
        FALSE,
        process->config.detached ? DETACHED_PROCESS : 0,
        NULL,
        process->config.workdir,
        &si,
        &process->pi
    );

    if (!ok) {
        process->state = FOSSIL_PROCESS_FAILED;
        return false;
    }

    process->pid   = (fossil_pid_t)process->pi.dwProcessId;
    process->state = FOSSIL_PROCESS_RUNNING;

#else /* POSIX */

    pid_t pid = fork();
    if (pid < 0) {
        process->state = FOSSIL_PROCESS_FAILED;
        return false;
    }

    if (pid == 0) {
        if (process->config.workdir)
            chdir(process->config.workdir);

        execve(
            process->config.path,
            process->config.argv,
            process->config.envp
        );
        _exit(127);
    }

    process->child_pid = pid;
    process->pid       = (fossil_pid_t)pid;
    process->state     = FOSSIL_PROCESS_RUNNING;

#endif

    return true;
}

bool
fossil_sys_process_wait(
    fossil_sys_process_t *process,
    uint32_t timeout_ms,
    fossil_sys_process_exit_t *exit_info)
{
    if (!process || process->state != FOSSIL_PROCESS_RUNNING)
        return false;

#if defined(_WIN32)

    DWORD wait_ms = (timeout_ms == 0) ? INFINITE : (DWORD)timeout_ms;
    DWORD res = WaitForSingleObject(process->pi.hProcess, wait_ms);

    if (res == WAIT_TIMEOUT)
        return false;

    if (res != WAIT_OBJECT_0)
        return false;

    DWORD code = 0;
    GetExitCodeProcess(process->pi.hProcess, &code);

    if (exit_info) {
        exit_info->exit_code = (int)code;
        exit_info->signaled  = false;
        exit_info->signal    = 0;
    }

    process->state = FOSSIL_PROCESS_EXITED;
    return true;

#else /* POSIX */

    const uint32_t poll_interval_ms = 10;
    uint32_t elapsed_ms = 0;

    for (;;) {
        int status = 0;
        pid_t r = waitpid(process->child_pid, &status, WNOHANG);

        if (r == process->child_pid) {
            if (exit_info) {
                if (WIFEXITED(status)) {
                    exit_info->exit_code = WEXITSTATUS(status);
                    exit_info->signaled  = false;
                    exit_info->signal    = 0;
                } else if (WIFSIGNALED(status)) {
                    exit_info->exit_code = -1;
                    exit_info->signaled  = true;
                    exit_info->signal    = WTERMSIG(status);
                }
            }

            process->state = FOSSIL_PROCESS_EXITED;
            return true;
        }

        if (r < 0)
            return false;

        if (timeout_ms != 0 && elapsed_ms >= timeout_ms)
            return false;

        struct timespec ts;
        ts.tv_sec  = 0;
        ts.tv_nsec = poll_interval_ms * 1000000UL;
        nanosleep(&ts, NULL);

        elapsed_ms += poll_interval_ms;
    }

#endif
}

bool
fossil_sys_process_terminate(fossil_sys_process_t *process)
{
    if (!process || process->state != FOSSIL_PROCESS_RUNNING)
        return false;

#if defined(_WIN32)
    TerminateProcess(process->pi.hProcess, 1);
#else
    kill(process->child_pid, SIGTERM);
#endif

    process->state = FOSSIL_PROCESS_STOPPED;
    return true;
}

bool
fossil_sys_process_kill(fossil_sys_process_t *process)
{
    if (!process || process->state != FOSSIL_PROCESS_RUNNING)
        return false;

#if defined(_WIN32)
    TerminateProcess(process->pi.hProcess, 9);
#else
    kill(process->child_pid, SIGKILL);
#endif

    process->state = FOSSIL_PROCESS_STOPPED;
    return true;
}

void
fossil_sys_process_destroy(fossil_sys_process_t *process)
{
    if (!process)
        return;

#if defined(_WIN32)
    CloseHandle(process->pi.hProcess);
    CloseHandle(process->pi.hThread);
#endif

    free(process);
}

/* ============================================================
 * Information
 * ============================================================ */

fossil_pid_t
fossil_sys_process_pid(const fossil_sys_process_t *process)
{
    return process ? process->pid : 0;
}

fossil_sys_process_state_t
fossil_sys_process_state(const fossil_sys_process_t *process)
{
    return process ? process->state : FOSSIL_PROCESS_INVALID;
}

bool
fossil_sys_process_is_alive(const fossil_sys_process_t *process)
{
    if (!process)
        return false;

    return process->state == FOSSIL_PROCESS_RUNNING;
}

/* ============================================================
 * Task Helpers
 * ============================================================ */

bool
fossil_sys_process_run_task(
    const fossil_sys_process_config_t *config,
    fossil_sys_process_exit_t *exit_info)
{
    fossil_sys_process_t *p = fossil_sys_process_create(config);
    if (!p)
        return false;

    if (!fossil_sys_process_start(p)) {
        fossil_sys_process_destroy(p);
        return false;
    }

    bool ok = fossil_sys_process_wait(p, 0, exit_info);
    fossil_sys_process_destroy(p);
    return ok;
}

fossil_sys_process_t *
fossil_sys_process_spawn_task(const fossil_sys_process_config_t *config)
{
    fossil_sys_process_t *p = fossil_sys_process_create(config);
    if (!p)
        return NULL;

    if (!fossil_sys_process_start(p)) {
        fossil_sys_process_destroy(p);
        return NULL;
    }

    return p;
}
