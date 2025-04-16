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
#include "fossil/sys/atomic.h"

//
// Load / Store
//

int32_t fossil_sys_atomic_i32_load(const fossil_sys_atomic_i32 *a) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_load(&a->value);
    #else
        return a->value;
    #endif
}

int64_t fossil_sys_atomic_i64_load(const fossil_sys_atomic_i64 *a) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_load(&a->value);
    #else
        return a->value;
    #endif
}

uint32_t fossil_sys_atomic_u32_load(const fossil_sys_atomic_u32 *a) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_load(&a->value);
    #else
        return a->value;
    #endif
}

uint64_t fossil_sys_atomic_u64_load(const fossil_sys_atomic_u64 *a) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_load(&a->value);
    #else
        return a->value;
    #endif
}

void fossil_sys_atomic_i32_store(fossil_sys_atomic_i32 *a, int32_t val) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        atomic_store(&a->value, val);
    #else
        a->value = val;
    #endif
}

void fossil_sys_atomic_i64_store(fossil_sys_atomic_i64 *a, int64_t val) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        atomic_store(&a->value, val);
    #else
        a->value = val;
    #endif
}

void fossil_sys_atomic_u32_store(fossil_sys_atomic_u32 *a, uint32_t val) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        atomic_store(&a->value, val);
    #else
        a->value = val;
    #endif
}

void fossil_sys_atomic_u64_store(fossil_sys_atomic_u64 *a, uint64_t val) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        atomic_store(&a->value, val);
    #else
        a->value = val;
    #endif
}

//
// Atomic arithmetic
//

int32_t fossil_sys_atomic_i32_add(fossil_sys_atomic_i32 *a, int32_t delta) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_fetch_add(&a->value, delta);
    #else
        int32_t old = a->value;
        a->value += delta;
        return old;
    #endif
}

int64_t fossil_sys_atomic_i64_add(fossil_sys_atomic_i64 *a, int64_t delta) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_fetch_add(&a->value, delta);
    #else
        int64_t old = a->value;
        a->value += delta;
        return old;
    #endif
}

uint32_t fossil_sys_atomic_u32_add(fossil_sys_atomic_u32 *a, uint32_t delta) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_fetch_add(&a->value, delta);
    #else
        uint32_t old = a->value;
        a->value += delta;
        return old;
    #endif
}

uint64_t fossil_sys_atomic_u64_add(fossil_sys_atomic_u64 *a, uint64_t delta) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_fetch_add(&a->value, delta);
    #else
        uint64_t old = a->value;
        a->value += delta;
        return old;
    #endif
}

int32_t fossil_sys_atomic_i32_sub(fossil_sys_atomic_i32 *a, int32_t delta) {
    return fossil_sys_atomic_i32_add(a, -delta);
}

int64_t fossil_sys_atomic_i64_sub(fossil_sys_atomic_i64 *a, int64_t delta) {
    return fossil_sys_atomic_i64_add(a, -delta);
}

uint32_t fossil_sys_atomic_u32_sub(fossil_sys_atomic_u32 *a, uint32_t delta) {
    return fossil_sys_atomic_u32_add(a, -delta);
}

uint64_t fossil_sys_atomic_u64_sub(fossil_sys_atomic_u64 *a, uint64_t delta) {
    return fossil_sys_atomic_u64_add(a, -delta);
}

//
// Compare-and-swap (CAS)
//

bool fossil_sys_atomic_i32_cas(fossil_sys_atomic_i32 *a, int32_t expected, int32_t desired) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_compare_exchange_strong(&a->value, &expected, desired);
    #else
        int32_t old = a->value;
        if (old == expected) {
            a->value = desired;
            return true;
        }
        return false;
    #endif
}

bool fossil_sys_atomic_i64_cas(fossil_sys_atomic_i64 *a, int64_t expected, int64_t desired) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_compare_exchange_strong(&a->value, &expected, desired);
    #else
        int64_t old = a->value;
        if (old == expected) {
            a->value = desired;
            return true;
        }
        return false;
    #endif
}

bool fossil_sys_atomic_u32_cas(fossil_sys_atomic_u32 *a, uint32_t expected, uint32_t desired) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_compare_exchange_strong(&a->value, &expected, desired);
    #else
        uint32_t old = a->value;
        if (old == expected) {
            a->value = desired;
            return true;
        }
        return false;
    #endif
}

bool fossil_sys_atomic_u64_cas(fossil_sys_atomic_u64 *a, uint64_t expected, uint64_t desired) {
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        return atomic_compare_exchange_strong(&a->value, &expected, desired);
    #else
        uint64_t old = a->value;
        if (old == expected) {
            a->value = desired;
            return true;
        }
        return false;
    #endif
}
