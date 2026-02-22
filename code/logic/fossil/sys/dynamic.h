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
#ifndef FOSSIL_SYS_DYNAMIC_H
#define FOSSIL_SYS_DYNAMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/* ------------------------------------------------------
 * Platform abstraction
 * ----------------------------------------------------- */

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef HMODULE fossil_sys_dynamic_handle_t;
#else
typedef void* fossil_sys_dynamic_handle_t;
#endif

/* ------------------------------------------------------
 * Types
 * ----------------------------------------------------- */

/* Dynamic library descriptor */
typedef struct {
    const char* id;                    /* string ID for AI/meta tracking */
    const char* path;                  /* file path to library */
    fossil_sys_dynamic_handle_t handle;
    int status;                        /* loaded / unloaded / error */
} fossil_sys_dynamic_lib_t;


/* ------------------------------------------------------
 * Lifecycle
 * ----------------------------------------------------- */

/* Load dynamic library */
bool fossil_sys_dynamic_load(
    const char* path,
    fossil_sys_dynamic_lib_t* out_lib);

/* Unload dynamic library */
bool fossil_sys_dynamic_unload(
    fossil_sys_dynamic_lib_t* lib);


/* ------------------------------------------------------
 * Symbol resolution
 * ----------------------------------------------------- */

/* Get symbol pointer from library */
void* fossil_sys_dynamic_symbol(
    fossil_sys_dynamic_lib_t* lib,
    const char* symbol_name);


/* ------------------------------------------------------
 * Introspection / diagnostics
 * ----------------------------------------------------- */

/* Check if library is loaded */
bool fossil_sys_dynamic_is_loaded(
    const fossil_sys_dynamic_lib_t* lib);

/* Get last dynamic loading error message */
const char* fossil_sys_dynamic_error(void);


#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_SYS_DYNAMIC_H */
