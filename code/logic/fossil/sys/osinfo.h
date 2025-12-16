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
#ifndef FOSSIL_SYS_OSINFO_H
#define FOSSIL_SYS_OSINFO_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ============================================================
 * Fossil System OS Info — Core Types
 * ============================================================ */

/**
 * @brief Operating system family.
 */
typedef enum fossil_sys_os_family {
    FOSSIL_OS_FAMILY_UNKNOWN = 0,
    FOSSIL_OS_FAMILY_POSIX,
    FOSSIL_OS_FAMILY_WINDOWS,
    FOSSIL_OS_FAMILY_RTOS,
    FOSSIL_OS_FAMILY_BAREMETAL
} fossil_sys_os_family_t;

/**
 * @brief Kernel / OS type.
 */
typedef enum fossil_sys_os_type {
    FOSSIL_OS_TYPE_UNKNOWN = 0,
    FOSSIL_OS_TYPE_LINUX,
    FOSSIL_OS_TYPE_MACOS,
    FOSSIL_OS_TYPE_WINDOWS,
    FOSSIL_OS_TYPE_BSD,
    FOSSIL_OS_TYPE_RTOS,
    FOSSIL_OS_TYPE_BAREMETAL
} fossil_sys_os_type_t;

/**
 * @brief OS information snapshot.
 */
typedef struct fossil_sys_osinfo {
    fossil_sys_os_family_t family;
    fossil_sys_os_type_t   type;

    uint32_t               version_major;
    uint32_t               version_minor;
    uint32_t               version_patch;

    bool                   is_embedded;
    bool                   is_64bit;

    char                   name[64];
    char                   version_string[64];
} fossil_sys_osinfo_t;

/* ============================================================
 * Queries
 * ============================================================ */

/**
 * @brief Query the current operating system information.
 *
 * This function fills the provided fossil_sys_osinfo_t structure with
 * details about the current operating system, such as family, type,
 * version numbers, and other relevant attributes.
 *
 * @param info Pointer to a fossil_sys_osinfo_t structure to be filled.
 * @return true if the query was successful, false otherwise.
 */
bool
fossil_sys_osinfo_query(fossil_sys_osinfo_t *info);

/* ============================================================
 * Convenience Helpers
 * ============================================================ */

/**
 * @brief Get the operating system family.
 *
 * Returns the family of the current operating system, such as POSIX,
 * Windows, RTOS, or Baremetal.
 *
 * @return The fossil_sys_os_family_t value representing the OS family.
 */
fossil_sys_os_family_t
fossil_sys_osinfo_family(void);

/**
 * @brief Get the operating system type.
 *
 * Returns the specific type of the current operating system, such as
 * Linux, macOS, Windows, BSD, RTOS, or Baremetal.
 *
 * @return The fossil_sys_os_type_t value representing the OS type.
 */
fossil_sys_os_type_t
fossil_sys_osinfo_type(void);

/**
 * @brief Check if the operating system is embedded.
 *
 * Determines whether the current operating system is considered an
 * embedded OS.
 *
 * @return true if the OS is embedded, false otherwise.
 */
bool
fossil_sys_osinfo_is_embedded(void);

/**
 * @brief Check if the operating system is 64-bit.
 *
 * Determines whether the current operating system is running in a
 * 64-bit environment.
 *
 * @return true if the OS is 64-bit, false otherwise.
 */
bool
fossil_sys_osinfo_is_64bit(void);

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

        /**
         * @brief OSInfo class.
         *
         * Provides a C++ wrapper around the Fossil System OS Info functions.
         */
        class OSInfo
        {
        public:
            /**
             * @brief Query the current operating system information.
             *
             * Fills the provided fossil_sys_osinfo_t structure with details about
             * the current operating system, such as family, type, version numbers,
             * and other relevant attributes.
             *
             * @param info Pointer to a fossil_sys_osinfo_t structure to be filled.
             * @return true if the query was successful, false otherwise.
             */
            static bool query(fossil_sys_osinfo_t *info)
            {
                return fossil_sys_osinfo_query(info);
            }

            /**
             * @brief Get the operating system family.
             *
             * Returns the family of the current operating system, such as POSIX,
             * Windows, RTOS, or Baremetal.
             *
             * @return The fossil_sys_os_family_t value representing the OS family.
             */
            static fossil_sys_os_family_t family()
            {
                return fossil_sys_osinfo_family();
            }

            /**
             * @brief Get the operating system type.
             *
             * Returns the specific type of the current operating system, such as
             * Linux, macOS, Windows, BSD, RTOS, or Baremetal.
             *
             * @return The fossil_sys_os_type_t value representing the OS type.
             */
            static fossil_sys_os_type_t type()
            {
                return fossil_sys_osinfo_type();
            }

            /**
             * @brief Check if the operating system is embedded.
             *
             * Determines whether the current operating system is considered an
             * embedded OS.
             *
             * @return true if the OS is embedded, false otherwise.
             */
            static bool is_embedded()
            {
                return fossil_sys_osinfo_is_embedded();
            }

            /**
             * @brief Check if the operating system is 64-bit.
             *
             * Determines whether the current operating system is running in a
             * 64-bit environment.
             *
             * @return true if the OS is 64-bit, false otherwise.
             */
            static bool is_64bit()
            {
                return fossil_sys_osinfo_is_64bit();
            }
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
