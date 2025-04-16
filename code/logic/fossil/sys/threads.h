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
#ifndef FOSSIL_SYS_THREADS_H
#define FOSSIL_SYS_THREADS_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque thread types
typedef struct fossil_sys_thread_t fossil_sys_thread_t;
typedef struct fossil_sys_thread_lock_t fossil_sys_thread_lock_t;
typedef struct fossil_sys_thread_event_t fossil_sys_thread_event_t;

// Thread function signature
typedef void *(*fossil_sys_thread_func)(void *arg);


//
// THREADS
//

/**
 * Creates a new thread.
 *
 * @param[out] out_thread Pointer to the thread handle to be created.
 * @param[in] fn Function to be executed by the thread.
 * @param[in] arg Argument to be passed to the thread function.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_create(fossil_sys_thread_t **out_thread, fossil_sys_thread_func fn, void *arg);

/**
 * Waits for the specified thread to terminate.
 *
 * @param[in] thread The thread handle to join.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_join(fossil_sys_thread_t *thread);

/**
 * Detaches the specified thread, allowing it to run independently.
 *
 * @param[in] thread The thread handle to detach.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_detach(fossil_sys_thread_t *thread);

/**
 * Destroys the specified thread handle.
 *
 * @param[in] thread The thread handle to destroy.
 */
void fossil_sys_thread_destroy(fossil_sys_thread_t *thread);

//
// THREAD LOCKS (like Python threading.Lock)
//

/**
 * Creates a new thread lock.
 *
 * @param[out] out_lock Pointer to the lock handle to be created.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_lock_create(fossil_sys_thread_lock_t **out_lock);

/**
 * Acquires the specified thread lock.
 *
 * @param[in] lock The lock handle to acquire.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_lock_acquire(fossil_sys_thread_lock_t *lock);

/**
 * Releases the specified thread lock.
 *
 * @param[in] lock The lock handle to release.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_lock_release(fossil_sys_thread_lock_t *lock);

/**
 * Destroys the specified thread lock handle.
 *
 * @param[in] lock The lock handle to destroy.
 */
void fossil_sys_thread_lock_destroy(fossil_sys_thread_lock_t *lock);

//
// THREAD EVENTS (like Python threading.Event)
//

/**
 * Creates a new thread event.
 *
 * @param[out] out_event Pointer to the event handle to be created.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_event_create(fossil_sys_thread_event_t **out_event);

/**
 * Sets the specified thread event, signaling it.
 *
 * @param[in] event The event handle to set.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_event_set(fossil_sys_thread_event_t *event);

/**
 * Clears the specified thread event, resetting its state.
 *
 * @param[in] event The event handle to clear.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_event_clear(fossil_sys_thread_event_t *event);

/**
 * Waits for the specified thread event to be set.
 *
 * @param[in] event The event handle to wait for.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_event_wait(fossil_sys_thread_event_t *event);

/**
 * Waits for the specified thread event to be set, with a timeout.
 *
 * @param[in] event The event handle to wait for.
 * @param[in] milliseconds Timeout in milliseconds.
 * @return 0 on success, or an error code on failure.
 */
int fossil_sys_thread_event_wait_timeout(fossil_sys_thread_event_t *event, unsigned milliseconds);

/**
 * Destroys the specified thread event handle.
 *
 * @param[in] event The event handle to destroy.
 */
void fossil_sys_thread_event_destroy(fossil_sys_thread_event_t *event);

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
         * A class that provides static methods for managing threads.
         */
        class Thread {
        public:
            /**
             * Creates a new thread.
             *
             * @param[out] out_thread Pointer to the thread handle to be created.
             * @param[in] fn Function to be executed by the thread.
             * @param[in] arg Argument to be passed to the thread function.
             * @return 0 on success, or an error code on failure.
             */
            static int create(fossil_sys_thread_t **out_thread, fossil_sys_thread_func fn, void *arg) {
            return fossil_sys_thread_create(out_thread, fn, arg);
            }

            /**
             * Waits for the specified thread to terminate.
             *
             * @param[in] thread The thread handle to join.
             * @return 0 on success, or an error code on failure.
             */
            static int join(fossil_sys_thread_t *thread) {
            return fossil_sys_thread_join(thread);
            }

            /**
             * Detaches the specified thread, allowing it to run independently.
             *
             * @param[in] thread The thread handle to detach.
             * @return 0 on success, or an error code on failure.
             */
            static int detach(fossil_sys_thread_t *thread) {
            return fossil_sys_thread_detach(thread);
            }

            /**
             * Destroys the specified thread handle.
             *
             * @param[in] thread The thread handle to destroy.
             */
            static void destroy(fossil_sys_thread_t *thread) {
            fossil_sys_thread_destroy(thread);
            }
        };

        /**
         * A class that provides static methods for managing thread locks.
         */
        class ThreadLock {
        public:
            /**
             * Creates a new thread lock.
             *
             * @param[out] out_lock Pointer to the lock handle to be created.
             * @return 0 on success, or an error code on failure.
             */
            static int create(fossil_sys_thread_lock_t **out_lock) {
            return fossil_sys_thread_lock_create(out_lock);
            }

            /**
             * Acquires the specified thread lock.
             *
             * @param[in] lock The lock handle to acquire.
             * @return 0 on success, or an error code on failure.
             */
            static int acquire(fossil_sys_thread_lock_t *lock) {
            return fossil_sys_thread_lock_acquire(lock);
            }

            /**
             * Releases the specified thread lock.
             *
             * @param[in] lock The lock handle to release.
             * @return 0 on success, or an error code on failure.
             */
            static int release(fossil_sys_thread_lock_t *lock) {
            return fossil_sys_thread_lock_release(lock);
            }

            /**
             * Destroys the specified thread lock handle.
             *
             * @param[in] lock The lock handle to destroy.
             */
            static void destroy(fossil_sys_thread_lock_t *lock) {
            fossil_sys_thread_lock_destroy(lock);
            }
        };

        /**
         * A class that provides static methods for managing thread events.
         */
        class ThreadEvent {
        public:
            /**
             * Creates a new thread event.
             *
             * @param[out] out_event Pointer to the event handle to be created.
             * @return 0 on success, or an error code on failure.
             */
            static int create(fossil_sys_thread_event_t **out_event) {
            return fossil_sys_thread_event_create(out_event);
            }

            /**
             * Sets the specified thread event, signaling it.
             *
             * @param[in] event The event handle to set.
             * @return 0 on success, or an error code on failure.
             */
            static int set(fossil_sys_thread_event_t *event) {
            return fossil_sys_thread_event_set(event);
            }

            /**
             * Clears the specified thread event, resetting its state.
             *
             * @param[in] event The event handle to clear.
             * @return 0 on success, or an error code on failure.
             */
            static int clear(fossil_sys_thread_event_t *event) {
            return fossil_sys_thread_event_clear(event);
            }

            /**
             * Waits for the specified thread event to be set.
             *
             * @param[in] event The event handle to wait for.
             * @return 0 on success, or an error code on failure.
             */
            static int wait(fossil_sys_thread_event_t *event) {
            return fossil_sys_thread_event_wait(event);
            }

            /**
             * Waits for the specified thread event to be set, with a timeout.
             *
             * @param[in] event The event handle to wait for.
             * @param[in] milliseconds Timeout in milliseconds.
             * @return 0 on success, or an error code on failure.
             */
            static int wait_timeout(fossil_sys_thread_event_t *event, unsigned milliseconds) {
            return fossil_sys_thread_event_wait_timeout(event, milliseconds);
            }

            /**
             * Destroys the specified thread event handle.
             *
             * @param[in] event The event handle to destroy.
             */
            static void destroy(fossil_sys_thread_event_t *event) {
            fossil_sys_thread_event_destroy(event);
            }
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
