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
#include "fossil/lib/command.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

#ifdef _WIN32
#include <windows.h>
#endif


int fossil_sys_command_exec(const char *command) {
    if (!command) return -1;
#ifdef _WIN32
    return system(command);
#else
    return system(command);
#endif
}

int fossil_sys_command_dup(int oldfd) {
#ifdef _WIN32
    return _dup(oldfd);
#else
    return dup(oldfd);
#endif
}

int64_t fossil_sys_command_uptime(void) {
#ifdef _WIN32
    return GetTickCount64() / 1000;
#else
    struct sysinfo info;
    if (sysinfo(&info) == 0) return info.uptime;
    return -1;
#endif
}

int64_t fossil_sys_command_meminfo(void) {
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex))
        return statex.ullAvailPhys;
    return -1;
#else
    struct sysinfo info;
    if (sysinfo(&info) == 0) return info.freeram;
    return -1;
#endif
}
