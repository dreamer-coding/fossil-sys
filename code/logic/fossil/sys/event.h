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
#ifndef FOSSIL_SYS_EVENT_H
#define FOSSIL_SYS_EVENT_H

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------
 * Event Types
 * ----------------------------------------------------- */
typedef enum {
    FOSSIL_EVENT_NONE,
    FOSSIL_EVENT_IO,
    FOSSIL_EVENT_TIMER,
    FOSSIL_EVENT_SIGNAL,
    FOSSIL_EVENT_CUSTOM
} fossil_sys_event_type_t;

/* ------------------------------------------------------
 * Event Structure
 * ----------------------------------------------------- */
typedef struct {
    const char* id;                // string ID for AI/tracking
    fossil_sys_event_type_t type;
    void* payload;                 // user-defined data
    size_t size;                   // payload size
} fossil_sys_event_t;

/* ------------------------------------------------------
 * Event API
 * ----------------------------------------------------- */

// Initialize event subsystem
int fossil_sys_event_init(void);

// Poll events (non-blocking)
int fossil_sys_event_poll(fossil_sys_event_t* out_event);

// Wait for next event (blocking)
int fossil_sys_event_wait(fossil_sys_event_t* out_event, uint32_t timeout_ms);

// Post a custom event
int fossil_sys_event_post(const char* id, void* payload, size_t size);

// Shutdown event subsystem
void fossil_sys_event_shutdown(void);

#endif /* FOSSIL_SYS_EVENT_H */
