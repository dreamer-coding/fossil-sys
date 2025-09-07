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
#include "fossil/sys/hostinfo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__APPLE__)
    #define _DARWIN_C_SOURCE
    #include <sys/utsname.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/sysctl.h>
#else
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <netdb.h> // for gethostname
#endif

int fossil_sys_hostinfo_get_system(fossil_sys_hostinfo_system_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osvi)) return -1;
    snprintf(info->os_name, sizeof(info->os_name), "Windows");
    snprintf(info->os_version, sizeof(info->os_version), "%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion);
    snprintf(info->kernel_version, sizeof(info->kernel_version), "%lu", osvi.dwBuildNumber);

    DWORD size = sizeof(info->hostname);
    GetComputerNameA(info->hostname, &size);

    size = sizeof(info->username);
    GetUserNameA(info->username, &size);

    // Domain name
    size = sizeof(info->domain_name);
    if (!GetEnvironmentVariableA("USERDOMAIN", info->domain_name, size)) {
        strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
        info->domain_name[sizeof(info->domain_name) - 1] = '\0';
    }

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    snprintf(info->machine_type, sizeof(info->machine_type), "%u", sysinfo.wProcessorArchitecture);
    snprintf(info->platform, sizeof(info->platform), "Win32");

#elif defined(__APPLE__)
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (gethostname(info->hostname, sizeof(info->hostname)) != 0)
        strncpy(info->hostname, "Unknown", sizeof(info->hostname) - 1);
    info->hostname[sizeof(info->hostname) - 1] = '\0';

    const char *user = getenv("USER");
    if (user)
        strncpy(info->username, user, sizeof(info->username) - 1);
    else
        strncpy(info->username, "Unknown", sizeof(info->username) - 1);
    info->username[sizeof(info->username) - 1] = '\0';

    strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
    info->domain_name[sizeof(info->domain_name) - 1] = '\0';

    strncpy(info->machine_type, sysinfo.machine, sizeof(info->machine_type) - 1);
    info->machine_type[sizeof(info->machine_type) - 1] = '\0';

    strncpy(info->platform, "Apple", sizeof(info->platform) - 1);
    info->platform[sizeof(info->platform) - 1] = '\0';

#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (gethostname(info->hostname, sizeof(info->hostname)) != 0)
        strncpy(info->hostname, "Unknown", sizeof(info->hostname) - 1);
    info->hostname[sizeof(info->hostname) - 1] = '\0';

    const char *user = getenv("USER");
    if (user)
        strncpy(info->username, user, sizeof(info->username) - 1);
    else
        strncpy(info->username, "Unknown", sizeof(info->username) - 1);
    info->username[sizeof(info->username) - 1] = '\0';

    const char *domain = getenv("DOMAINNAME");
    if (domain)
        strncpy(info->domain_name, domain, sizeof(info->domain_name) - 1);
    else
        strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
    info->domain_name[sizeof(info->domain_name) - 1] = '\0';

    strncpy(info->machine_type, sysinfo.machine, sizeof(info->machine_type) - 1);
    info->machine_type[sizeof(info->machine_type) - 1] = '\0';

    strncpy(info->platform, "Unix", sizeof(info->platform) - 1);
    info->platform[sizeof(info->platform) - 1] = '\0';

#endif
    return 0;
}

int fossil_sys_hostinfo_get_architecture(fossil_sys_hostinfo_architecture_t *info) {
    if (!info) return -1;

#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    // Architecture
    switch (sysinfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            strncpy(info->architecture, "x86_64", sizeof(info->architecture) - 1);
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            strncpy(info->architecture, "x86", sizeof(info->architecture) - 1);
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            strncpy(info->architecture, "ARM", sizeof(info->architecture) - 1);
            break;
        default:
            strncpy(info->architecture, "Unknown", sizeof(info->architecture) - 1);
            break;
    }
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    // CPU info (limited on Windows)
    strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
    info->cpu[sizeof(info->cpu) - 1] = '\0';

    snprintf(info->cpu_cores, sizeof(info->cpu_cores), "%lu", sysinfo.dwNumberOfProcessors);
    strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
    strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';

#elif defined(__APPLE__)
    size_t size = sizeof(info->architecture);
    if (sysctlbyname("hw.machine", info->architecture, &size, NULL, 0) != 0)
        strncpy(info->architecture, "Unknown", sizeof(info->architecture) - 1);
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    size = sizeof(info->cpu);
    if (sysctlbyname("machdep.cpu.brand_string", info->cpu, &size, NULL, 0) != 0)
        strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
    info->cpu[sizeof(info->cpu) - 1] = '\0';

    int cores = 0;
    size = sizeof(cores);
    if (sysctlbyname("hw.physicalcpu", &cores, &size, NULL, 0) == 0)
        snprintf(info->cpu_cores, sizeof(info->cpu_cores), "%d", cores);
    else
        strncpy(info->cpu_cores, "Unknown", sizeof(info->cpu_cores) - 1);
    info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';

    int threads = 0;
    size = sizeof(threads);
    if (sysctlbyname("hw.logicalcpu", &threads, &size, NULL, 0) == 0)
        snprintf(info->cpu_threads, sizeof(info->cpu_threads), "%d", threads);
    else
        strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';

    uint64_t freq = 0;
    size = sizeof(freq);
    if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) == 0)
        snprintf(info->cpu_frequency, sizeof(info->cpu_frequency), "%llu", (unsigned long long)freq);
    else
        strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';

    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';

#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;

    strncpy(info->architecture, sysinfo.machine, sizeof(info->architecture) - 1);
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "model name", 10) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu, colon, sizeof(info->cpu) - 1);
                    info->cpu[sizeof(info->cpu) - 1] = '\0';
                }
            } else if (strncmp(line, "cpu cores", 9) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_cores, colon, sizeof(info->cpu_cores) - 1);
                    info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';
                }
            } else if (strncmp(line, "siblings", 8) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_threads, colon, sizeof(info->cpu_threads) - 1);
                    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
                }
            } else if (strncmp(line, "cpu MHz", 7) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_frequency, colon, sizeof(info->cpu_frequency) - 1);
                    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
                }
            }
        }
        fclose(fp);
    } else {
        strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
        info->cpu[sizeof(info->cpu) - 1] = '\0';
        strncpy(info->cpu_cores, "Unknown", sizeof(info->cpu_cores) - 1);
        info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';
        strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
        info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
        strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
        info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
    }

    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';
#endif

    return 0;
}

int fossil_sys_hostinfo_get_memory(fossil_sys_hostinfo_memory_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (!GlobalMemoryStatusEx(&statex)) return -1;
    info->total_memory = statex.ullTotalPhys;
    info->free_memory = statex.ullAvailPhys;
    info->used_memory = statex.ullTotalPhys - statex.ullAvailPhys;
    info->available_memory = statex.ullAvailPhys;
    info->total_swap = statex.ullTotalPageFile;
    info->free_swap = statex.ullAvailPageFile;
    info->used_swap = statex.ullTotalPageFile - statex.ullAvailPageFile;
#elif defined(__APPLE__)
    int64_t memsize;
    size_t len = sizeof(memsize);
    if (sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0) return -1;
    info->total_memory = memsize;
    info->free_memory = 0; // macOS does not provide free memory info in the same way
    info->used_memory = 0;
    info->available_memory = 0;
    info->total_swap = 0;
    info->free_swap = 0;
    info->used_swap = 0;
#else
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) return -1;
    info->total_memory = sys_info.totalram * sys_info.mem_unit;
    info->free_memory = sys_info.freeram * sys_info.mem_unit;
    info->used_memory = (sys_info.totalram - sys_info.freeram) * sys_info.mem_unit;
    info->available_memory = sys_info.freeram * sys_info.mem_unit;
    info->total_swap = sys_info.totalswap * sys_info.mem_unit;
    info->free_swap = sys_info.freeswap * sys_info.mem_unit;
    info->used_swap = (sys_info.totalswap - sys_info.freeswap) * sys_info.mem_unit;
#endif
    return 0;
}

int fossil_sys_hostinfo_get_endianness(fossil_sys_hostinfo_endianness_t *info) {
    if (!info) return -1;
    uint16_t test = 0x0001;
    info->is_little_endian = (*(uint8_t*)&test) ? 1 : 0;
    return 0;
}
