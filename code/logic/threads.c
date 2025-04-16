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
#include "fossil/sys/threads.h"

#include <stdlib.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#endif

//
// Internal structures
//

struct fossil_sys_thread_t {
#ifdef _WIN32
    HANDLE handle;
    DWORD id;
#else
    pthread_t thread;
#endif
};

struct fossil_sys_thread_lock_t {
#ifdef _WIN32
    CRITICAL_SECTION cs;
#else
    pthread_mutex_t mutex;
#endif
};

struct fossil_sys_thread_event_t {
#ifdef _WIN32
    HANDLE handle;
#else
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int is_set;
#endif
};

//
// Threads
//

#ifdef _WIN32
static DWORD WINAPI thread_entry(LPVOID arg) {
    fossil_sys_thread_func fn = ((fossil_sys_thread_func *)arg)[0];
    void *fn_arg = ((void **)arg)[1];
    free(arg);
    fn(fn_arg);
    return 0;
}
#else
static void *thread_entry(void *arg) {
    fossil_sys_thread_func fn = ((fossil_sys_thread_func *)arg)[0];
    void *fn_arg = ((void **)arg)[1];
    free(arg);
    return fn(fn_arg);
}
#endif

int fossil_sys_thread_create(fossil_sys_thread_t **out_thread, fossil_sys_thread_func fn, void *arg) {
    if (!out_thread || !fn) return -1;
    fossil_sys_thread_t *t = malloc(sizeof(fossil_sys_thread_t));
    if (!t) return -1;

#ifdef _WIN32
    void **args = malloc(2 * sizeof(void *));
    if (!args) { free(t); return -1; }
    args[0] = (void *)fn;
    args[1] = arg;

    t->handle = CreateThread(NULL, 0, thread_entry, args, 0, &t->id);
    if (!t->handle) { free(args); free(t); return -1; }

#else
    void **args = malloc(2 * sizeof(void *));
    if (!args) { free(t); return -1; }
    args[0] = (void *)fn;
    args[1] = arg;

    if (pthread_create(&t->thread, NULL, thread_entry, args) != 0) {
        free(args); free(t); return -1;
    }
#endif

    *out_thread = t;
    return 0;
}

int fossil_sys_thread_join(fossil_sys_thread_t *thread) {
    if (!thread) return -1;
#ifdef _WIN32
    WaitForSingleObject(thread->handle, INFINITE);
#else
    pthread_join(thread->thread, NULL);
#endif
    return 0;
}

int fossil_sys_thread_detach(fossil_sys_thread_t *thread) {
    if (!thread) return -1;
#ifdef _WIN32
    CloseHandle(thread->handle); // detached
#else
    pthread_detach(thread->thread);
#endif
    return 0;
}

void fossil_sys_thread_destroy(fossil_sys_thread_t *thread) {
    if (!thread) return;
#ifdef _WIN32
    CloseHandle(thread->handle);
#endif
    free(thread);
}

//
// Locks
//

int fossil_sys_thread_lock_create(fossil_sys_thread_lock_t **out_lock) {
    if (!out_lock) return -1;
    fossil_sys_thread_lock_t *lock = malloc(sizeof(fossil_sys_thread_lock_t));
    if (!lock) return -1;

#ifdef _WIN32
    InitializeCriticalSection(&lock->cs);
#else
    if (pthread_mutex_init(&lock->mutex, NULL) != 0) {
        free(lock); return -1;
    }
#endif

    *out_lock = lock;
    return 0;
}

int fossil_sys_thread_lock_acquire(fossil_sys_thread_lock_t *lock) {
    if (!lock) return -1;
#ifdef _WIN32
    EnterCriticalSection(&lock->cs);
#else
    pthread_mutex_lock(&lock->mutex);
#endif
    return 0;
}

int fossil_sys_thread_lock_release(fossil_sys_thread_lock_t *lock) {
    if (!lock) return -1;
#ifdef _WIN32
    LeaveCriticalSection(&lock->cs);
#else
    pthread_mutex_unlock(&lock->mutex);
#endif
    return 0;
}

void fossil_sys_thread_lock_destroy(fossil_sys_thread_lock_t *lock) {
    if (!lock) return;
#ifdef _WIN32
    DeleteCriticalSection(&lock->cs);
#else
    pthread_mutex_destroy(&lock->mutex);
#endif
    free(lock);
}

//
// Events
//

int fossil_sys_thread_event_create(fossil_sys_thread_event_t **out_event) {
    if (!out_event) return -1;
    fossil_sys_thread_event_t *ev = malloc(sizeof(fossil_sys_thread_event_t));
    if (!ev) return -1;

#ifdef _WIN32
    ev->handle = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!ev->handle) { free(ev); return -1; }
#else
    if (pthread_mutex_init(&ev->mutex, NULL) != 0 ||
        pthread_cond_init(&ev->cond, NULL) != 0) {
        free(ev); return -1;
    }
    ev->is_set = 0;
#endif

    *out_event = ev;
    return 0;
}

int fossil_sys_thread_event_set(fossil_sys_thread_event_t *event) {
    if (!event) return -1;
#ifdef _WIN32
    SetEvent(event->handle);
#else
    pthread_mutex_lock(&event->mutex);
    event->is_set = 1;
    pthread_cond_broadcast(&event->cond);
    pthread_mutex_unlock(&event->mutex);
#endif
    return 0;
}

int fossil_sys_thread_event_clear(fossil_sys_thread_event_t *event) {
    if (!event) return -1;
#ifdef _WIN32
    ResetEvent(event->handle);
#else
    pthread_mutex_lock(&event->mutex);
    event->is_set = 0;
    pthread_mutex_unlock(&event->mutex);
#endif
    return 0;
}

int fossil_sys_thread_event_wait(fossil_sys_thread_event_t *event) {
    if (!event) return -1;
#ifdef _WIN32
    WaitForSingleObject(event->handle, INFINITE);
#else
    pthread_mutex_lock(&event->mutex);
    while (!event->is_set) {
        pthread_cond_wait(&event->cond, &event->mutex);
    }
    pthread_mutex_unlock(&event->mutex);
#endif
    return 0;
}

int fossil_sys_thread_event_wait_timeout(fossil_sys_thread_event_t *event, unsigned milliseconds) {
    if (!event) return -1;
#ifdef _WIN32
    DWORD res = WaitForSingleObject(event->handle, milliseconds);
    return (res == WAIT_OBJECT_0) ? 0 : -1;
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += milliseconds / 1000;
    ts.tv_nsec += (milliseconds % 1000) * 1000000;
    if (ts.tv_nsec >= 1000000000L) {
        ts.tv_sec++;
        ts.tv_nsec -= 1000000000L;
    }

    pthread_mutex_lock(&event->mutex);
    int rc = 0;
    while (!event->is_set && rc == 0) {
        rc = pthread_cond_timedwait(&event->cond, &event->mutex, &ts);
    }
    pthread_mutex_unlock(&event->mutex);
    return (rc == 0) ? 0 : -1;
#endif
}

void fossil_sys_thread_event_destroy(fossil_sys_thread_event_t *event) {
    if (!event) return;
#ifdef _WIN32
    CloseHandle(event->handle);
#else
    pthread_mutex_destroy(&event->mutex);
    pthread_cond_destroy(&event->cond);
#endif
    free(event);
}
