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
#ifndef FOSSIL_SYS_ATOMIC_H
#define FOSSIL_SYS_ATOMIC_H

#include <stdint.h>
#include <stdbool.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    // C11 atomics
    #include <stdatomic.h>
#else
    // Fallback for older compilers (e.g., GCC, Clang, Windows)
    #include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Types
//

#ifdef __cplusplus
#include <atomic>
typedef struct {
    std::atomic<int32_t> value;
} fossil_sys_atomic_i32;

typedef struct {
    std::atomic<int64_t> value;
} fossil_sys_atomic_i64;

typedef struct {
    std::atomic<uint32_t> value;
} fossil_sys_atomic_u32;

typedef struct {
    std::atomic<uint64_t> value;
} fossil_sys_atomic_u64;
#else
typedef struct {
    _Atomic int32_t value;
} fossil_sys_atomic_i32;

typedef struct {
    _Atomic int64_t value;
} fossil_sys_atomic_i64;

typedef struct {
    _Atomic uint32_t value;
} fossil_sys_atomic_u32;

typedef struct {
    _Atomic uint64_t value;
} fossil_sys_atomic_u64;
#endif

//
// Memory ordering (optional abstraction layer)
//
typedef enum {
    FOSSIL_ATOMIC_RELAXED,
    FOSSIL_ATOMIC_ACQUIRE,
    FOSSIL_ATOMIC_RELEASE,
    FOSSIL_ATOMIC_ACQ_REL,
    FOSSIL_ATOMIC_SEQ_CST
} fossil_sys_atomic_order;

//
// Init
//

#define fossil_sys_atomic_i32_init(val) ((fossil_sys_atomic_i32){ .value = (val) })
#define fossil_sys_atomic_i64_init(val) ((fossil_sys_atomic_i64){ .value = (val) })
#define fossil_sys_atomic_u32_init(val) ((fossil_sys_atomic_u32){ .value = (val) })
#define fossil_sys_atomic_u64_init(val) ((fossil_sys_atomic_u64){ .value = (val) })

//
// Load / Store
//

/**
 * @brief Loads the current value of a 32-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @return The current value of the atomic integer.
 */
int32_t fossil_sys_atomic_i32_load(const fossil_sys_atomic_i32 *a);

/**
 * @brief Loads the current value of a 64-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @return The current value of the atomic integer.
 */
int64_t fossil_sys_atomic_i64_load(const fossil_sys_atomic_i64 *a);

/**
 * @brief Loads the current value of a 32-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @return The current value of the atomic unsigned integer.
 */
uint32_t fossil_sys_atomic_u32_load(const fossil_sys_atomic_u32 *a);

/**
 * @brief Loads the current value of a 64-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @return The current value of the atomic unsigned integer.
 */
uint64_t fossil_sys_atomic_u64_load(const fossil_sys_atomic_u64 *a);

/**
 * @brief Stores a value into a 32-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @param val The value to store.
 */
void fossil_sys_atomic_i32_store(fossil_sys_atomic_i32 *a, int32_t val);

/**
 * @brief Stores a value into a 64-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @param val The value to store.
 */
void fossil_sys_atomic_i64_store(fossil_sys_atomic_i64 *a, int64_t val);

/**
 * @brief Stores a value into a 32-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param val The value to store.
 */
void fossil_sys_atomic_u32_store(fossil_sys_atomic_u32 *a, uint32_t val);

/**
 * @brief Stores a value into a 64-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param val The value to store.
 */
void fossil_sys_atomic_u64_store(fossil_sys_atomic_u64 *a, uint64_t val);

//
// Atomic arithmetic
//

/**
 * @brief Adds a delta to a 32-bit atomic integer and returns the old value.
 *
 * @param a Pointer to the atomic integer.
 * @param delta The value to add.
 * @return The old value of the atomic integer.
 */
int32_t fossil_sys_atomic_i32_add(fossil_sys_atomic_i32 *a, int32_t delta);

/**
 * @brief Adds a delta to a 64-bit atomic integer and returns the old value.
 *
 * @param a Pointer to the atomic integer.
 * @param delta The value to add.
 * @return The old value of the atomic integer.
 */
int64_t fossil_sys_atomic_i64_add(fossil_sys_atomic_i64 *a, int64_t delta);

/**
 * @brief Adds a delta to a 32-bit atomic unsigned integer and returns the old value.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param delta The value to add.
 * @return The old value of the atomic unsigned integer.
 */
uint32_t fossil_sys_atomic_u32_add(fossil_sys_atomic_u32 *a, uint32_t delta);

/**
 * @brief Adds a delta to a 64-bit atomic unsigned integer and returns the old value.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param delta The value to add.
 * @return The old value of the atomic unsigned integer.
 */
uint64_t fossil_sys_atomic_u64_add(fossil_sys_atomic_u64 *a, uint64_t delta);

/**
 * @brief Subtracts a delta from a 32-bit atomic integer and returns the old value.
 *
 * @param a Pointer to the atomic integer.
 * @param delta The value to subtract.
 * @return The old value of the atomic integer.
 */
int32_t fossil_sys_atomic_i32_sub(fossil_sys_atomic_i32 *a, int32_t delta);

/**
 * @brief Subtracts a delta from a 64-bit atomic integer and returns the old value.
 *
 * @param a Pointer to the atomic integer.
 * @param delta The value to subtract.
 * @return The old value of the atomic integer.
 */
int64_t fossil_sys_atomic_i64_sub(fossil_sys_atomic_i64 *a, int64_t delta);

/**
 * @brief Subtracts a delta from a 32-bit atomic unsigned integer and returns the old value.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param delta The value to subtract.
 * @return The old value of the atomic unsigned integer.
 */
uint32_t fossil_sys_atomic_u32_sub(fossil_sys_atomic_u32 *a, uint32_t delta);

/**
 * @brief Subtracts a delta from a 64-bit atomic unsigned integer and returns the old value.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param delta The value to subtract.
 * @return The old value of the atomic unsigned integer.
 */
uint64_t fossil_sys_atomic_u64_sub(fossil_sys_atomic_u64 *a, uint64_t delta);

//
// Compare-and-swap
//

/**
 * @brief Performs a compare-and-swap operation on a 32-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @param expected The value expected to be found.
 * @param desired The value to set if the expected value matches.
 * @return True if the swap was successful, false otherwise.
 */
bool fossil_sys_atomic_i32_cas(fossil_sys_atomic_i32 *a, int32_t expected, int32_t desired);

/**
 * @brief Performs a compare-and-swap operation on a 64-bit atomic integer.
 *
 * @param a Pointer to the atomic integer.
 * @param expected The value expected to be found.
 * @param desired The value to set if the expected value matches.
 * @return True if the swap was successful, false otherwise.
 */
bool fossil_sys_atomic_i64_cas(fossil_sys_atomic_i64 *a, int64_t expected, int64_t desired);

/**
 * @brief Performs a compare-and-swap operation on a 32-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param expected The value expected to be found.
 * @param desired The value to set if the expected value matches.
 * @return True if the swap was successful, false otherwise.
 */
bool fossil_sys_atomic_u32_cas(fossil_sys_atomic_u32 *a, uint32_t expected, uint32_t desired);

/**
 * @brief Performs a compare-and-swap operation on a 64-bit atomic unsigned integer.
 *
 * @param a Pointer to the atomic unsigned integer.
 * @param expected The value expected to be found.
 * @param desired The value to set if the expected value matches.
 * @return True if the swap was successful, false otherwise.
 */
bool fossil_sys_atomic_u64_cas(fossil_sys_atomic_u64 *a, uint64_t expected, uint64_t desired);

#ifdef __cplusplus
}
#include <string>

/**
 * Fossil namespace.
 */
namespace fossil {

    /**
     * System namespace.
     */
    namespace sys {

        /**
         * @brief Provides atomic operations for 32-bit signed integers.
         */
        class AtomicI32 {
        public:
            /**
             * @brief Loads the current value of a 32-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @return The current value of the atomic signed integer.
             */
            static int32_t load(const fossil_sys_atomic_i32 *a) {
                return fossil_sys_atomic_i32_load(a);
            }

            /**
             * @brief Stores a value into a 32-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @param val The value to store.
             */
            static void store(fossil_sys_atomic_i32 *a, int32_t val) {
                fossil_sys_atomic_i32_store(a, val);
            }

            /**
             * @brief Adds a delta to a 32-bit atomic signed integer and returns the old value.
             *
             * @param a Pointer to the atomic signed integer.
             * @param delta The value to add.
             * @return The old value of the atomic signed integer.
             */
            static int32_t add(fossil_sys_atomic_i32 *a, int32_t delta) {
                return fossil_sys_atomic_i32_add(a, delta);
            }

            /**
             * @brief Performs a compare-and-swap operation on a 32-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @param expected The value expected to be found.
             * @param desired The value to set if the expected value matches.
             * @return True if the swap was successful, false otherwise.
             */
            static bool cas(fossil_sys_atomic_i32 *a, int32_t expected, int32_t desired) {
                return fossil_sys_atomic_i32_cas(a, expected, desired);
            }
        };

        /**
         * @brief Provides atomic operations for 64-bit signed integers.
         */
        class AtomicI64 {
        public:
            /**
             * @brief Loads the current value of a 64-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @return The current value of the atomic signed integer.
             */
            static int64_t load(const fossil_sys_atomic_i64 *a) {
                return fossil_sys_atomic_i64_load(a);
            }

            /**
             * @brief Stores a value into a 64-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @param val The value to store.
             */
            static void store(fossil_sys_atomic_i64 *a, int64_t val) {
                fossil_sys_atomic_i64_store(a, val);
            }

            /**
             * @brief Adds a delta to a 64-bit atomic signed integer and returns the old value.
             *
             * @param a Pointer to the atomic signed integer.
             * @param delta The value to add.
             * @return The old value of the atomic signed integer.
             */
            static int64_t add(fossil_sys_atomic_i64 *a, int64_t delta) {
                return fossil_sys_atomic_i64_add(a, delta);
            }

            /**
             * @brief Performs a compare-and-swap operation on a 64-bit atomic signed integer.
             *
             * @param a Pointer to the atomic signed integer.
             * @param expected The value expected to be found.
             * @param desired The value to set if the expected value matches.
             * @return True if the swap was successful, false otherwise.
             */
            static bool cas(fossil_sys_atomic_i64 *a, int64_t expected, int64_t desired) {
                return fossil_sys_atomic_i64_cas(a, expected, desired);
            }
        };

        /**
         * @brief Provides atomic operations for 32-bit unsigned integers.
         */
        class AtomicU32 {
        public:
            /**
             * @brief Loads the current value of a 32-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @return The current value of the atomic unsigned integer.
             */
            static uint32_t load(const fossil_sys_atomic_u32 *a) {
                return fossil_sys_atomic_u32_load(a);
            }

            /**
             * @brief Stores a value into a 32-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param val The value to store.
             */
            static void store(fossil_sys_atomic_u32 *a, uint32_t val) {
                fossil_sys_atomic_u32_store(a, val);
            }

            /**
             * @brief Adds a delta to a 32-bit atomic unsigned integer and returns the old value.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param delta The value to add.
             * @return The old value of the atomic unsigned integer.
             */
            static uint32_t add(fossil_sys_atomic_u32 *a, uint32_t delta) {
                return fossil_sys_atomic_u32_add(a, delta);
            }

            /**
             * @brief Performs a compare-and-swap operation on a 32-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param expected The value expected to be found.
             * @param desired The value to set if the expected value matches.
             * @return True if the swap was successful, false otherwise.
             */
            static bool cas(fossil_sys_atomic_u32 *a, uint32_t expected, uint32_t desired) {
                return fossil_sys_atomic_u32_cas(a, expected, desired);
            }
        };

        /**
         * @brief Provides atomic operations for 64-bit unsigned integers.
         */
        class AtomicU64 {
        public:
            /**
             * @brief Loads the current value of a 64-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @return The current value of the atomic unsigned integer.
             */
            static uint64_t load(const fossil_sys_atomic_u64 *a) {
                return fossil_sys_atomic_u64_load(a);
            }

            /**
             * @brief Stores a value into a 64-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param val The value to store.
             */
            static void store(fossil_sys_atomic_u64 *a, uint64_t val) {
                fossil_sys_atomic_u64_store(a, val);
            }

            /**
             * @brief Adds a delta to a 64-bit atomic unsigned integer and returns the old value.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param delta The value to add.
             * @return The old value of the atomic unsigned integer.
             */
            static uint64_t add(fossil_sys_atomic_u64 *a, uint64_t delta) {
                return fossil_sys_atomic_u64_add(a, delta);
            }

            /**
             * @brief Performs a compare-and-swap operation on a 64-bit atomic unsigned integer.
             *
             * @param a Pointer to the atomic unsigned integer.
             * @param expected The value expected to be found.
             * @param desired The value to set if the expected value matches.
             * @return True if the swap was successful, false otherwise.
             */
            static bool cas(fossil_sys_atomic_u64 *a, uint64_t expected, uint64_t desired) {
                return fossil_sys_atomic_u64_cas(a, expected, desired);
            }
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
