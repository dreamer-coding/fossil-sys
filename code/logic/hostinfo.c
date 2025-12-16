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

//
int fossil_sys_hostinfo_get_storage(fossil_sys_hostinfo_storage_t *info) {
    if (!info) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    // Use GetDiskFreeSpaceEx for C:
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    if (GetDiskFreeSpaceExA("C:\\", &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        strncpy(info->device_name, "C:", sizeof(info->device_name) - 1);
        strncpy(info->mount_point, "C:\\", sizeof(info->mount_point) - 1);
        info->total_space = totalNumberOfBytes.QuadPart;
        info->free_space = totalNumberOfFreeBytes.QuadPart;
        info->used_space = info->total_space - info->free_space;
        strncpy(info->filesystem_type, "NTFS", sizeof(info->filesystem_type) - 1); // Guess
    } else {
        strncpy(info->device_name, "Unknown", sizeof(info->device_name) - 1);
        strncpy(info->mount_point, "Unknown", sizeof(info->mount_point) - 1);
        info->total_space = 0;
        info->free_space = 0;
        info->used_space = 0;
        strncpy(info->filesystem_type, "Unknown", sizeof(info->filesystem_type) - 1);
        return -1;
    }
#elif defined(__APPLE__) || defined(__unix__) || defined(__linux__)
    // Use statvfs for "/"
    #include <sys/statvfs.h>
    struct statvfs vfs;
    if (statvfs("/", &vfs) == 0) {
        strncpy(info->device_name, "/", sizeof(info->device_name) - 1);
        strncpy(info->mount_point, "/", sizeof(info->mount_point) - 1);
        info->total_space = (uint64_t)vfs.f_frsize * vfs.f_blocks;
        info->free_space = (uint64_t)vfs.f_frsize * vfs.f_bfree;
        info->used_space = info->total_space - info->free_space;
        // Try to get filesystem type (Linux only)
#if defined(__linux__)
        FILE *fp = fopen("/proc/mounts", "r");
        if (fp) {
            char line[512];
            while (fgets(line, sizeof(line), fp)) {
                char dev[128], mnt[128], fstype[64];
                if (sscanf(line, "%127s %127s %63s", dev, mnt, fstype) == 3) {
                    if (strcmp(mnt, "/") == 0) {
                        snprintf(info->filesystem_type, sizeof(info->filesystem_type), "%s", fstype);
                        break;
                    }
                }
            }
            fclose(fp);
        }
        if (info->filesystem_type[0] == '\0')
            strncpy(info->filesystem_type, "Unknown", sizeof(info->filesystem_type) - 1);
#else
        strncpy(info->filesystem_type, "Unknown", sizeof(info->filesystem_type) - 1);
#endif
    } else {
        strncpy(info->device_name, "Unknown", sizeof(info->device_name) - 1);
        strncpy(info->mount_point, "Unknown", sizeof(info->mount_point) - 1);
        info->total_space = 0;
        info->free_space = 0;
        info->used_space = 0;
        strncpy(info->filesystem_type, "Unknown", sizeof(info->filesystem_type) - 1);
        return -1;
    }
#else
    strncpy(info->device_name, "Unknown", sizeof(info->device_name) - 1);
    strncpy(info->mount_point, "Unknown", sizeof(info->mount_point) - 1);
    info->total_space = 0;
    info->free_space = 0;
    info->used_space = 0;
    strncpy(info->filesystem_type, "Unknown", sizeof(info->filesystem_type) - 1);
    return -1;
#endif
    return 0;
}

int fossil_sys_hostinfo_get_environment(fossil_sys_hostinfo_environment_t *info) {
    if (!info) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    // Get environment variables
    DWORD len;
    len = GetEnvironmentVariableA("COMSPEC", info->shell, sizeof(info->shell));
    if (len == 0) strncpy(info->shell, "Unknown", sizeof(info->shell) - 1);

    len = GetEnvironmentVariableA("USERPROFILE", info->home_dir, sizeof(info->home_dir));
    if (len == 0) strncpy(info->home_dir, "Unknown", sizeof(info->home_dir) - 1);

    len = GetEnvironmentVariableA("LANG", info->lang, sizeof(info->lang));
    if (len == 0) strncpy(info->lang, "Unknown", sizeof(info->lang) - 1);

    len = GetEnvironmentVariableA("PATH", info->path, sizeof(info->path));
    if (len == 0) strncpy(info->path, "Unknown", sizeof(info->path) - 1);

    len = GetEnvironmentVariableA("TERM", info->_term, sizeof(info->_term));
    if (len == 0) strncpy(info->_term, "Unknown", sizeof(info->_term) - 1);

    len = GetEnvironmentVariableA("USERNAME", info->user, sizeof(info->user));
    if (len == 0) strncpy(info->user, "Unknown", sizeof(info->user) - 1);

#elif defined(__APPLE__) || defined(__unix__) || defined(__linux__)
    const char *val;
    val = getenv("SHELL");
    if (val) strncpy(info->shell, val, sizeof(info->shell) - 1);
    else strncpy(info->shell, "Unknown", sizeof(info->shell) - 1);

    val = getenv("HOME");
    if (val) strncpy(info->home_dir, val, sizeof(info->home_dir) - 1);
    else strncpy(info->home_dir, "Unknown", sizeof(info->home_dir) - 1);

    val = getenv("LANG");
    if (val) strncpy(info->lang, val, sizeof(info->lang) - 1);
    else strncpy(info->lang, "Unknown", sizeof(info->lang) - 1);

    val = getenv("PATH");
    if (val) strncpy(info->path, val, sizeof(info->path) - 1);
    else strncpy(info->path, "Unknown", sizeof(info->path) - 1);

    val = getenv("TERM");
    if (val) strncpy(info->_term, val, sizeof(info->_term) - 1);
    else strncpy(info->_term, "Unknown", sizeof(info->_term) - 1);

    val = getenv("USER");
    if (val) strncpy(info->user, val, sizeof(info->user) - 1);
    else strncpy(info->user, "Unknown", sizeof(info->user) - 1);
#else
    strncpy(info->shell, "Unknown", sizeof(info->shell) - 1);
    strncpy(info->home_dir, "Unknown", sizeof(info->home_dir) - 1);
    strncpy(info->lang, "Unknown", sizeof(info->lang) - 1);
    strncpy(info->path, "Unknown", sizeof(info->path) - 1);
    strncpy(info->_term, "Unknown", sizeof(info->_term) - 1);
    strncpy(info->user, "Unknown", sizeof(info->user) - 1);
#endif
    return 0;
}

int fossil_sys_hostinfo_get_cpu(fossil_sys_hostinfo_cpu_t *info) {
    if (!info) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    // Windows: limited info
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    info->cores = sysinfo.dwNumberOfProcessors;
    info->threads = sysinfo.dwNumberOfProcessors;
    strncpy(info->model, "Unknown", sizeof(info->model) - 1);
    strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);
    info->frequency_ghz = 0.0f;
    strncpy(info->features, "Unknown", sizeof(info->features) - 1);
#elif defined(__APPLE__)
    size_t size;
    // Model
    size = sizeof(info->model);
    if (sysctlbyname("machdep.cpu.brand_string", info->model, &size, NULL, 0) != 0)
        strncpy(info->model, "Unknown", sizeof(info->model) - 1);
    info->model[sizeof(info->model) - 1] = '\0';
    // Vendor
    size = sizeof(info->vendor);
    if (sysctlbyname("machdep.cpu.vendor", info->vendor, &size, NULL, 0) != 0)
        strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);
    info->vendor[sizeof(info->vendor) - 1] = '\0';
    // Cores
    int cores = 0;
    size = sizeof(cores);
    if (sysctlbyname("hw.physicalcpu", &cores, &size, NULL, 0) == 0)
        info->cores = cores;
    else
        info->cores = 0;
    // Threads
    int threads = 0;
    size = sizeof(threads);
    if (sysctlbyname("hw.logicalcpu", &threads, &size, NULL, 0) == 0)
        info->threads = threads;
    else
        info->threads = 0;
    // Frequency
    uint64_t freq = 0;
    size = sizeof(freq);
    if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) == 0)
        info->frequency_ghz = (float)freq / 1e9f;
    else
        info->frequency_ghz = 0.0f;
    // Features
    size = sizeof(info->features);
    if (sysctlbyname("machdep.cpu.features", info->features, &size, NULL, 0) != 0)
        strncpy(info->features, "Unknown", sizeof(info->features) - 1);
    info->features[sizeof(info->features) - 1] = '\0';
#else
    // Linux
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return -1;
    char line[256];
    info->cores = 0;
    info->threads = 0;
    info->frequency_ghz = 0.0f;
    info->model[0] = info->vendor[0] = info->features[0] = '\0';
    int found_model = 0, found_vendor = 0, found_freq = 0, found_flags = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (!found_model && strncmp(line, "model name", 10) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                strncpy(info->model, colon, sizeof(info->model) - 1);
                info->model[sizeof(info->model) - 1] = '\0';
                found_model = 1;
            }
        } else if (!found_vendor && strncmp(line, "vendor_id", 9) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                strncpy(info->vendor, colon, sizeof(info->vendor) - 1);
                info->vendor[sizeof(info->vendor) - 1] = '\0';
                found_vendor = 1;
            }
        } else if (!found_freq && strncmp(line, "cpu MHz", 7) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                float mhz = strtof(colon, NULL);
                info->frequency_ghz = mhz / 1000.0f;
                found_freq = 1;
            }
        } else if (!found_flags && strncmp(line, "flags", 5) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                strncpy(info->features, colon, sizeof(info->features) - 1);
                info->features[sizeof(info->features) - 1] = '\0';
                found_flags = 1;
            }
        } else if (strncmp(line, "processor", 9) == 0) {
            info->threads++;
        } else if (strncmp(line, "cpu cores", 9) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                info->cores = atoi(colon);
            }
        }
    }
    fclose(fp);
    if (info->cores == 0) info->cores = info->threads ? info->threads : 1;
    if (info->threads == 0) info->threads = info->cores;
    if (!found_model) strncpy(info->model, "Unknown", sizeof(info->model) - 1);
    if (!found_vendor) strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);
    if (!found_freq) info->frequency_ghz = 0.0f;
    if (!found_flags) strncpy(info->features, "Unknown", sizeof(info->features) - 1);
#endif
    return 0;
}

int fossil_sys_hostinfo_get_gpu(fossil_sys_hostinfo_gpu_t *info) {
    if (!info) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    // Windows: Use WMI or DX APIs for real info; fallback to unknown
    strncpy(info->name, "Unknown", sizeof(info->name) - 1);
    strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);
    strncpy(info->driver_version, "Unknown", sizeof(info->driver_version) - 1);
    info->memory_total = 0;
    info->memory_free = 0;
#elif defined(__APPLE__)
    // macOS: Use IOKit for real info; fallback to unknown
    strncpy(info->name, "Unknown", sizeof(info->name) - 1);
    strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);
    strncpy(info->driver_version, "Unknown", sizeof(info->driver_version) - 1);
    info->memory_total = 0;
    info->memory_free = 0;
#else
    // Linux: Try to parse lspci and glxinfo output if available
    FILE *fp = popen("lspci -mm | grep VGA", "r");
    if (fp) {
        char line[512];
        if (fgets(line, sizeof(line), fp)) {
            // Example: 00:02.0 "VGA compatible controller" "Intel Corporation" "HD Graphics 620" ...
            char *vendor = strchr(line, '"');
            if (vendor) {
                vendor++;
                vendor = strchr(vendor, '"');
                if (vendor) {
                    vendor++;
                    vendor = strchr(vendor, '"');
                    if (vendor) {
                        vendor++;
                        char *vendor_end = strchr(vendor, '"');
                        if (vendor_end && vendor_end - vendor < (int)sizeof(info->vendor)) {
                            strncpy(info->vendor, vendor, vendor_end - vendor);
                            info->vendor[vendor_end - vendor] = '\0';
                        }
                        char *name = strchr(vendor_end + 1, '"');
                        if (name) {
                            name++;
                            char *name_end = strchr(name, '"');
                            if (name_end && name_end - name < (int)sizeof(info->name)) {
                                strncpy(info->name, name, name_end - name);
                                info->name[name_end - name] = '\0';
                            }
                        }
                    }
                }
            }
        }
        pclose(fp);
    }
    if (info->name[0] == '\0') strncpy(info->name, "Unknown", sizeof(info->name) - 1);
    if (info->vendor[0] == '\0') strncpy(info->vendor, "Unknown", sizeof(info->vendor) - 1);

    // Try to get driver version from glxinfo
    fp = popen("glxinfo -B 2>/dev/null | grep 'OpenGL version string'", "r");
    if (fp) {
        char line[256];
        if (fgets(line, sizeof(line), fp)) {
            char *colon = strchr(line, ':');
            if (colon) {
                colon++;
                while (*colon == ' ') colon++;
                strncpy(info->driver_version, colon, sizeof(info->driver_version) - 1);
                info->driver_version[sizeof(info->driver_version) - 1] = '\0';
                // Remove trailing newline
                char *nl = strchr(info->driver_version, '\n');
                if (nl) *nl = '\0';
            }
        }
        pclose(fp);
    }
    if (info->driver_version[0] == '\0')
        strncpy(info->driver_version, "Unknown", sizeof(info->driver_version) - 1);

    // Memory info: not portable, set to 0
    info->memory_total = 0;
    info->memory_free = 0;
#endif
    return 0;
}

int fossil_sys_hostinfo_get_power(fossil_sys_hostinfo_power_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    SYSTEM_POWER_STATUS status;
    if (!GetSystemPowerStatus(&status)) return -1;

    info->on_ac_power = (status.ACLineStatus == 1) ? 1 : 0;
    info->battery_present = (status.BatteryFlag != 128) ? 1 : 0; // 128 = no battery
    info->battery_charging = (status.BatteryFlag & 8) ? 1 : 0;   // 8 = charging
    info->battery_percentage = (status.BatteryLifePercent != 255) ? status.BatteryLifePercent : -1;
    info->battery_seconds_left = (status.BatteryLifeTime != (DWORD)-1) ? (int)status.BatteryLifeTime : -1;

#elif defined(__APPLE__)
    // On macOS, use IOKit (not available by default in C, requires linking with -framework IOKit)
    // Fallback: set unknowns
    info->on_ac_power = -1;
    info->battery_present = -1;
    info->battery_charging = -1;
    info->battery_percentage = -1;
    info->battery_seconds_left = -1;
#else
    // On Linux, try to read from /sys/class/power_supply
    FILE *fp;
    char path[256];
    int found_battery = 0;
    info->on_ac_power = -1;
    info->battery_present = 0;
    info->battery_charging = -1;
    info->battery_percentage = -1;
    info->battery_seconds_left = -1;

    // Check AC status
    fp = fopen("/sys/class/power_supply/AC/online", "r");
    if (!fp) fp = fopen("/sys/class/power_supply/ACAD/online", "r");
    if (!fp) fp = fopen("/sys/class/power_supply/Mains/online", "r");
    if (fp) {
        int ac = 0;
        if (fscanf(fp, "%d", &ac) == 1)
            info->on_ac_power = ac;
        fclose(fp);
    }

    // Try to find a battery directory
    for (int i = 0; i < 2; ++i) {
        snprintf(path, sizeof(path), "/sys/class/power_supply/BAT%d/", i);
        FILE *test = fopen(path, "r");
        if (test) {
            found_battery = 1;
            fclose(test);
            snprintf(path, sizeof(path), "/sys/class/power_supply/BAT%d/status", i);
            fp = fopen(path, "r");
            if (fp) {
                char status[32];
                if (fgets(status, sizeof(status), fp)) {
                    if (strstr(status, "Charging"))
                        info->battery_charging = 1;
                    else if (strstr(status, "Discharging"))
                        info->battery_charging = 0;
                    else
                        info->battery_charging = -1;
                }
                fclose(fp);
            }
            snprintf(path, sizeof(path), "/sys/class/power_supply/BAT%d/capacity", i);
            fp = fopen(path, "r");
            if (fp) {
                int percent = -1;
                if (fscanf(fp, "%d", &percent) == 1)
                    info->battery_percentage = percent;
                fclose(fp);
            }
            snprintf(path, sizeof(path), "/sys/class/power_supply/BAT%d/time_to_empty_now", i);
            fp = fopen(path, "r");
            if (fp) {
                int secs = -1;
                if (fscanf(fp, "%d", &secs) == 1)
                    info->battery_seconds_left = secs;
                fclose(fp);
            }
            break;
        }
    }
    info->battery_present = found_battery ? 1 : 0;
#endif
    return 0;
}

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
