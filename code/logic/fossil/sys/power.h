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
#ifndef FOSSIL_SYS_POWER_H
#define FOSSIL_SYS_POWER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Fossil System Power — Core Types
 * ============================================================ */

/**
 * @brief Power source.
 */
typedef enum fossil_sys_power_source {
    FOSSIL_POWER_SOURCE_UNKNOWN = 0,
    FOSSIL_POWER_SOURCE_AC,
    FOSSIL_POWER_SOURCE_BATTERY
} fossil_sys_power_source_t;

/**
 * @brief Battery state.
 */
typedef enum fossil_sys_power_battery_state {
    FOSSIL_POWER_BATTERY_UNKNOWN = 0,
    FOSSIL_POWER_BATTERY_CHARGING,
    FOSSIL_POWER_BATTERY_DISCHARGING,
    FOSSIL_POWER_BATTERY_FULL
} fossil_sys_power_battery_state_t;

/**
 * @brief Power information snapshot.
 */
typedef struct fossil_sys_power_info {
    fossil_sys_power_source_t        source;
    fossil_sys_power_battery_state_t battery_state;
    uint32_t                         battery_percent; /* 0–100, 0 if unknown */
    bool                             low_power_mode;
} fossil_sys_power_info_t;

/* ============================================================
 * Queries
 * ============================================================ */

/**
 * @brief Query current power state.
 */
bool
fossil_sys_power_query(fossil_sys_power_info_t *info);

/**
 * @brief Convenience helpers.
 */
bool
fossil_sys_power_on_battery(void);

bool
fossil_sys_power_low_power_mode(void);

#ifdef __cplusplus
}

/**
 * Fossil namespace.
 */
namespace fossil {

    /**
     * System namespace.
     */
    namespace sys {



    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
