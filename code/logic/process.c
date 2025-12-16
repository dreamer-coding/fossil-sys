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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__linux__)
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void fossil_sys_zero(void *ptr, size_t size) {
    if (ptr) memset(ptr, 0, size);
}

uint32_t fossil_sys_process_get_pid(void) {
    return (uint32_t)getpid();
}

int fossil_sys_process_get_name(uint32_t pid, char *name, size_t name_len) {
    if (!name || name_len == 0) return -1;

    char path[256];
    snprintf(path, sizeof(path), "/proc/%u/comm", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) return -2;

    if (!fgets(name, name_len, fp)) {
        fclose(fp);
        return -3;
    }
    fclose(fp);

    size_t len = strlen(name);
    if (len > 0 && name[len-1] == '\n') name[len-1] = '\0';
    return 0;
}

int fossil_sys_process_get_info(uint32_t pid, fossil_sys_process_info_t *info) {
    if (!info) return -1;
    fossil_sys_zero(info, sizeof(*info));
    info->pid = pid;

    // Name
    if (fossil_sys_process_get_name(pid, info->name, sizeof(info->name)) != 0)
        strncpy(info->name, "unknown", sizeof(info->name));

    // Parent PID
    char path[256];
    snprintf(path, sizeof(path), "/proc/%u/stat", pid);
    FILE *fp = fopen(path, "r");
    if (fp) {
        int scanned = fscanf(fp, "%*d %*s %*c %u", &info->ppid);
        fclose(fp);
        if (scanned != 1) info->ppid = 0;
    }

    // Memory usage
    snprintf(path, sizeof(path), "/proc/%u/statm", pid);
    fp = fopen(path, "r");
    if (fp) {
        unsigned long size = 0, resident = 0;
        if (fscanf(fp, "%lu %lu", &size, &resident) == 2) {
            long page_size = sysconf(_SC_PAGESIZE);
            info->virtual_memory_bytes = (uint64_t)size * page_size;
            info->memory_bytes = (uint64_t)resident * page_size;
        }
        fclose(fp);
    }

    // Thread count
    snprintf(path, sizeof(path), "/proc/%u/status", pid);
    fp = fopen(path, "r");
    if (fp) {
        char line[512]; // increased size for safety
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "Threads: %u", &info->thread_count) == 1) break;
        }
        fclose(fp);
    }

    // CPU usage placeholder
    info->cpu_percent = 0.0f;

    return 0;
}

int fossil_sys_process_list(fossil_sys_process_list_t *plist) {
    if (!plist) return -1;
    plist->count = 0;

    DIR *dir = opendir("/proc");
    if (!dir) return -2;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        char *endptr;
        uint32_t pid = strtoul(entry->d_name, &endptr, 10);
        if (*endptr != '\0') continue;

        if (plist->count >= FOSSIL_SYS_PROCESS_MAX) break;
        fossil_sys_process_get_info(pid, &plist->list[plist->count++]);
    }

    closedir(dir);
    return 0;
}

int fossil_sys_process_terminate(uint32_t pid, int force) {
    int sig = force ? SIGKILL : SIGTERM;
    return (kill(pid, sig) == 0) ? 0 : -1;
}

int fossil_sys_process_get_environment(uint32_t pid, char *buffer, size_t buf_len) {
    if (!buffer || buf_len == 0) return -1;
    fossil_sys_zero(buffer, buf_len);

    char path[256];
    snprintf(path, sizeof(path), "/proc/%u/environ", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) return -2;

    size_t total_read = fread(buffer, 1, buf_len - 1, fp);
    fclose(fp);

    for (size_t i = 0; i < total_read; i++)
        if (buffer[i] == '\0') buffer[i] = ';';

    buffer[total_read] = '\0';
    return (int)total_read;
}

#elif defined(_WIN32)
#include <windows.h>
#include <winternl.h>
#include <string.h>
#include <wchar.h>
#include <tlhelp32.h>
#include <psapi.h>

uint32_t fossil_sys_process_get_pid(void) {
    return (uint32_t)GetCurrentProcessId();
}

int fossil_sys_process_get_name(uint32_t pid, char *name, size_t name_len) {
    if (!name || name_len == 0) return -1;
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!h) return -2;
    DWORD sz = (DWORD)name_len;
    if (!QueryFullProcessImageNameA(h, 0, name, &sz)) {
        CloseHandle(h);
        return -3;
    }
    CloseHandle(h);
    return 0;
}

// stubs for Windows
int fossil_sys_process_get_info(uint32_t pid, fossil_sys_process_info_t *info) {
    if (!info) return -1;
    memset(info, 0, sizeof(*info));
    info->pid = pid;
    return 0;
}

int fossil_sys_process_list(fossil_sys_process_list_t *plist) {
    if (!plist) return -1;
    plist->count = 0;
    return 0;
}

int fossil_sys_process_terminate(uint32_t pid, int force) {
    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!h) return -1;
    BOOL ok = TerminateProcess(h, force ? 1 : 0);
    CloseHandle(h);
    return ok ? 0 : -1;
}

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PVOID PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

typedef NTSTATUS (NTAPI *PFN_NtQueryInformationProcess)(
    HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG
);

// Convert UTF-16 environment block to UTF-8
static int utf16_env_to_utf8(WCHAR *env, char *buffer, size_t buf_len) {
    if (!env || !buffer || buf_len == 0) return -1;
    size_t total = 0;
    while (*env) {
        int len = WideCharToMultiByte(
            CP_UTF8, 0, env, -1, buffer + total, (int)(buf_len - total), NULL, NULL);
        if (len == 0) break;
        total += len - 1; // exclude null terminator
        buffer[total++] = ';'; // separate variables
        env += wcslen(env) + 1;
        if (total >= buf_len - 1) break;
    }
    buffer[total] = '\0';
    return (int)total;
}

int fossil_sys_process_get_environment(uint32_t pid, char *buffer, size_t buf_len) {
    if (!buffer || buf_len == 0) return -1;
    memset(buffer, 0, buf_len);

    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) return -2;

    PFN_NtQueryInformationProcess NtQueryInformationProcess =
        (PFN_NtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) return -3;

    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!hProc) return -4;

    PROCESS_BASIC_INFORMATION pbi;
    NTSTATUS status = NtQueryInformationProcess(hProc, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
    if (status != 0) {
        CloseHandle(hProc);
        return -5;
    }

    // Read PEB -> ProcessParameters -> Environment
    PEB peb;
    if (!ReadProcessMemory(hProc, pbi.PebBaseAddress, &peb, sizeof(peb), NULL)) {
        CloseHandle(hProc);
        return -6;
    }

    RTL_USER_PROCESS_PARAMETERS procParams;
    if (!ReadProcessMemory(hProc, peb.ProcessParameters, &procParams, sizeof(procParams), NULL)) {
        CloseHandle(hProc);
        return -7;
    }

    // Allocate buffer for environment block
    WCHAR *envBlock = (WCHAR *)malloc(procParams.EnvironmentSize);
    if (!envBlock) {
        CloseHandle(hProc);
        return -8;
    }

    if (!ReadProcessMemory(hProc, procParams.Environment, envBlock, procParams.EnvironmentSize, NULL)) {
        free(envBlock);
        CloseHandle(hProc);
        return -9;
    }

    // Convert UTF-16 to UTF-8
    int written = utf16_env_to_utf8(envBlock, buffer, buf_len);

    free(envBlock);
    CloseHandle(hProc);
    return written;
}

#else
// stubs for unsupported platforms
uint32_t fossil_sys_process_get_pid(void) { return 0; }
int fossil_sys_process_get_name(uint32_t pid, char *name, size_t name_len) { return -1; }
int fossil_sys_process_get_info(uint32_t pid, fossil_sys_process_info_t *info) { return -1; }
int fossil_sys_process_list(fossil_sys_process_list_t *plist) { return -1; }
int fossil_sys_process_terminate(uint32_t pid, int force) { return -1; }
int fossil_sys_process_get_environment(uint32_t pid, char *buffer, size_t buf_len) { return -1; }
#endif
