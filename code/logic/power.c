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
#include "fossil/sys/power.h"

#include <string.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#else
    #include <unistd.h>
#endif

/* ============================================================
 * Helpers
 * ============================================================ */

static void
fossil_sys_power_clear(fossil_sys_power_info_t *info)
{
    memset(info, 0, sizeof(*info));
    info->source        = FOSSIL_POWER_SOURCE_UNKNOWN;
    info->battery_state = FOSSIL_POWER_BATTERY_UNKNOWN;
}

/* ============================================================
 * Queries
 * ============================================================ */

bool
fossil_sys_power_query(fossil_sys_power_info_t *info)
{
    if (!info)
        return false;

    fossil_sys_power_clear(info);

#if defined(_WIN32)

    SYSTEM_POWER_STATUS sps;
    if (!GetSystemPowerStatus(&sps))
        return false;

    if (sps.ACLineStatus == 1)
        info->source = FOSSIL_POWER_SOURCE_AC;
    else if (sps.ACLineStatus == 0)
        info->source = FOSSIL_POWER_SOURCE_BATTERY;

    if (sps.BatteryFlag & 8)
        info->battery_state = FOSSIL_POWER_BATTERY_CHARGING;
    else if (sps.BatteryLifePercent == 100)
        info->battery_state = FOSSIL_POWER_BATTERY_FULL;
    else
        info->battery_state = FOSSIL_POWER_BATTERY_DISCHARGING;

    info->battery_percent = (sps.BatteryLifePercent <= 100)
        ? (uint32_t)sps.BatteryLifePercent
        : 0;

    info->low_power_mode = (sps.SystemStatusFlag != 0);
    return true;

#elif defined(__APPLE__)

    int on_battery = 0;
    size_t size = sizeof(on_battery);

    if (sysctlbyname("hw.acpi.acline", &on_battery, &size, NULL, 0) == 0) {
        info->source = on_battery
            ? FOSSIL_POWER_SOURCE_AC
            : FOSSIL_POWER_SOURCE_BATTERY;
    }

    /* macOS does not expose battery % portably without IOKit */
    info->battery_state   = FOSSIL_POWER_BATTERY_UNKNOWN;
    info->battery_percent = 0;
    info->low_power_mode  = false;

    return true;

#elif defined(__linux__)

    /* Best-effort: presence-based detection */
    if (access("/sys/class/power_supply/AC/online", F_OK) == 0)
        info->source = FOSSIL_POWER_SOURCE_AC;
    else if (access("/sys/class/power_supply/BAT0", F_OK) == 0)
        info->source = FOSSIL_POWER_SOURCE_BATTERY;

    info->battery_state   = FOSSIL_POWER_BATTERY_UNKNOWN;
    info->battery_percent = 0;
    info->low_power_mode  = false;

    return true;

#else
    return false;
#endif
}

/* ============================================================
 * Convenience Helpers
 * ============================================================ */

bool
fossil_sys_power_on_battery(void)
{
    fossil_sys_power_info_t info;
    if (!fossil_sys_power_query(&info))
        return false;

    return info.source == FOSSIL_POWER_SOURCE_BATTERY;
}

bool
fossil_sys_power_low_power_mode(void)
{
    fossil_sys_power_info_t info;
    if (!fossil_sys_power_query(&info))
        return false;

    return info.low_power_mode;
}
