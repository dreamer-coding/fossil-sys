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
 * @brief Query the current power state of the system.
 *
 * This function fills the provided fossil_sys_power_info_t structure
 * with the current power source, battery state, battery percentage,
 * and low power mode status. Returns true if the query was successful,
 * false otherwise.
 *
 * @param info Pointer to a fossil_sys_power_info_t structure to be filled.
 * @return true if the power state was successfully queried, false otherwise.
 */
bool
fossil_sys_power_query(fossil_sys_power_info_t *info);

/**
 * @brief Check if the system is currently running on battery power.
 *
 * This function returns true if the system is powered by a battery,
 * and false if it is powered by AC or if the power source is unknown.
 *
 * @return true if running on battery, false otherwise.
 */
bool
fossil_sys_power_on_battery(void);

/**
 * @brief Check if the system is currently in low power mode.
 *
 * This function returns true if the system is operating in a low power
 * or energy-saving mode, and false otherwise.
 *
 * @return true if low power mode is active, false otherwise.
 */
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

        //
        /**
         * @brief Power information class.
         *
         * Provides a C++ interface for querying system power state.
         */
        class power
        {
        public:
            /**
             * Query the current power state of the system.
             * @param info Reference to a fossil_sys_power_info_t to fill.
             * @return true if the power state was successfully queried, false otherwise.
             */
            static bool query(fossil_sys_power_info_t &info)
            {
                return fossil_sys_power_query(&info);
            }

            /**
             * Check if the system is currently running on battery power.
             * @return true if running on battery, false otherwise.
             */
            static bool on_battery()
            {
                return fossil_sys_power_on_battery();
            }

            /**
             * Check if the system is currently in low power mode.
             * @return true if low power mode is active, false otherwise.
             */
            static bool low_power_mode()
            {
                return fossil_sys_power_low_power_mode();
            }
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
