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
#include "fossil/sys/sandbox.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <psapi.h>

#else

#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>

/* Handle MAP_ANON vs MAP_ANONYMOUS portability */
#ifdef MAP_ANONYMOUS
#define MAP_ANON MAP_ANONYMOUS
#elif !defined(MAP_ANON)
#define MAP_ANON 0
#endif

#endif


/* ------------------------------------------------------
 * Internal helpers
 * ----------------------------------------------------- */

static char* fossil_strdup(const char* s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char* d = (char*)malloc(n);
    if (d) memcpy(d, s, n);
    return d;
}

/* ------------------------------------------------------
 * Create sandbox
 * ----------------------------------------------------- */
bool fossil_sys_sandbox_create(
    fossil_sys_sandbox_mode_t mode,
    const fossil_sys_sandbox_limits_t* limits,
    fossil_sys_sandbox_t* out_box)
{
    if (!out_box) return false;

    memset(out_box, 0, sizeof(*out_box));
    out_box->mode = mode;
    out_box->status = 0;

    if (limits)
        out_box->limits = *limits;

#if defined(_WIN32) || defined(_WIN64)

    if (mode == FOSSIL_SANDBOX_MODE_PROCESS ||
        mode == FOSSIL_SANDBOX_MODE_RESTRICTED)
    {
        HANDLE job = CreateJobObjectA(NULL, NULL);
        if (!job) return false;

        JOBOBJECT_EXTENDED_LIMIT_INFORMATION info;
        memset(&info, 0, sizeof(info));

        if (limits && limits->max_memory) {
            info.ProcessMemoryLimit = limits->max_memory;
            info.BasicLimitInformation.LimitFlags |=
                JOB_OBJECT_LIMIT_PROCESS_MEMORY;
        }

        SetInformationJobObject(job,
            JobObjectExtendedLimitInformation,
            &info,
            sizeof(info));

        out_box->vm_handle = job;
    }

#else

    /* POSIX: nothing to allocate yet */
    out_box->vm_handle = NULL;

#endif

    out_box->id = "sandbox";
    return true;
}


/* ------------------------------------------------------
 * Destroy sandbox
 * ----------------------------------------------------- */
bool fossil_sys_sandbox_destroy(fossil_sys_sandbox_t* box) {
    if (!box) return false;

#if defined(_WIN32) || defined(_WIN64)

    if (box->vm_handle) {
        CloseHandle((HANDLE)box->vm_handle);
        box->vm_handle = NULL;
    }

#endif

    box->status = 0;
    return true;
}


/* ------------------------------------------------------
 * Apply POSIX limits in child
 * ----------------------------------------------------- */
#if !defined(_WIN32) && !defined(_WIN64)
static void fossil_apply_limits(const fossil_sys_sandbox_limits_t* l) {
    if (!l) return;

    struct rlimit r;

    if (l->max_memory) {
        r.rlim_cur = r.rlim_max = l->max_memory;
        setrlimit(RLIMIT_AS, &r);
    }

    if (l->max_cpu_time) {
        r.rlim_cur = r.rlim_max = (l->max_cpu_time / 1000) + 1;
        setrlimit(RLIMIT_CPU, &r);
    }

    if (l->max_files) {
        r.rlim_cur = r.rlim_max = l->max_files;
        setrlimit(RLIMIT_NOFILE, &r);
    }
}
#endif


/* ------------------------------------------------------
 * Execute command inside sandbox
 * ----------------------------------------------------- */
bool fossil_sys_sandbox_exec(
    fossil_sys_sandbox_t* box,
    const char* command)
{
    if (!box || !command) return false;

#if defined(_WIN32) || defined(_WIN64)

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    char* cmd = fossil_strdup(command);
    if (!cmd) return false;

    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE,
                        CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        free(cmd);
        return false;
    }

    /* attach to job object if present */
    if (box->vm_handle)
        AssignProcessToJobObject((HANDLE)box->vm_handle, pi.hProcess);

    ResumeThread(pi.hThread);

    box->pid = pi.dwProcessId;
    box->status = 1;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    free(cmd);

#else

    pid_t pid = fork();
    if (pid < 0) return false;

    if (pid == 0) {
        fossil_apply_limits(&box->limits);
        execl("/bin/sh", "sh", "-c", command, (char*)NULL);
        _exit(127);
    }

    box->pid = (uint32_t)pid;
    box->status = 1;

#endif

    return true;
}


/* ------------------------------------------------------
 * Execute raw code in VM mode
 * ----------------------------------------------------- */
bool fossil_sys_sandbox_exec_code(
    fossil_sys_sandbox_t* box,
    const void* code,
    size_t size)
{
    if (!box || !code || size == 0) return false;

    if (box->mode != FOSSIL_SANDBOX_MODE_VM)
        return false;

    /* Very lightweight VM: copy to executable memory */
#if defined(_WIN32) || defined(_WIN64)

    void* mem = VirtualAlloc(NULL, size,
                             MEM_COMMIT | MEM_RESERVE,
                             PAGE_EXECUTE_READWRITE);

#else

    void* mem = mmap(NULL, size,
                     PROT_READ|PROT_WRITE|PROT_EXEC,
                     MAP_PRIVATE|MAP_ANON, -1, 0);

#endif

    if (!mem) return false;

    memcpy(mem, code, size);

    typedef void (*vm_fn)(void);
    vm_fn fn = (vm_fn)mem;

    fn(); /* execute */

    box->vm_handle = mem;
    box->status = 1;
    return true;
}


/* ------------------------------------------------------
 * Stop sandbox execution
 * ----------------------------------------------------- */
bool fossil_sys_sandbox_stop(fossil_sys_sandbox_t* box) {
    if (!box) return false;

#if defined(_WIN32) || defined(_WIN64)

    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, box->pid);
    if (!h) return false;
    TerminateProcess(h, 1);
    CloseHandle(h);

#else

    kill((pid_t)box->pid, SIGKILL);

#endif

    box->status = 0;
    return true;
}


/* ------------------------------------------------------
 * Query status
 * ----------------------------------------------------- */
int fossil_sys_sandbox_status(const fossil_sys_sandbox_t* box) {
    if (!box) return -1;
    return box->status;
}


/* ------------------------------------------------------
 * Introspection: memory usage (best effort)
 * ----------------------------------------------------- */
uint64_t fossil_sys_sandbox_memory(const fossil_sys_sandbox_t* box) {
    if (!box || box->pid == 0) return 0;

#if defined(_WIN32) || defined(_WIN64)

    PROCESS_MEMORY_COUNTERS pmc;
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
                           FALSE, box->pid);
    if (!h) return 0;

    uint64_t mem = 0;
    if (GetProcessMemoryInfo(h, &pmc, sizeof(pmc)))
        mem = pmc.WorkingSetSize;

    CloseHandle(h);
    return mem;

#else
    /* minimal portable fallback */
    return 0;
#endif
}


/* ------------------------------------------------------
 * CPU time consumed
 * ----------------------------------------------------- */
uint64_t fossil_sys_sandbox_cpu_time(const fossil_sys_sandbox_t* box) {

#if defined(_WIN32) || defined(_WIN64)

    FILETIME create, exit, kernel, user;
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION,
                           FALSE, box->pid);
    if (!h) return 0;

    uint64_t time = 0;
    if (GetProcessTimes(h, &create, &exit, &kernel, &user)) {
        ULARGE_INTEGER k, u;
        k.LowPart = kernel.dwLowDateTime;
        k.HighPart = kernel.dwHighDateTime;
        u.LowPart = user.dwLowDateTime;
        u.HighPart = user.dwHighDateTime;
        time = (k.QuadPart + u.QuadPart) / 10000ULL;
    }

    CloseHandle(h);
    return time;

#else
    return 0;
#endif
}
