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
#include <fossil/test/framework.h>

#include "fossil/sys/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(c_process_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_process_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_process_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_process_create) {
    const char *path = "/bin/echo";
    char *const args[] = { "echo", "Hello, Fossil!", NULL };
    fossil_sys_process_t process = fossil_sys_process_create(path, args);

    int status;
    ASSUME_ITS_TRUE(fossil_sys_process_wait(process, &status) == 0);
}

FOSSIL_TEST_CASE(c_test_process_wait) {
    const char *path = "/bin/sleep";
    char *const args[] = { "sleep", "1", NULL };
    fossil_sys_process_t process = fossil_sys_process_create(path, args);

    int status;
    ASSUME_ITS_TRUE(fossil_sys_process_wait(process, &status) == 0);
}

FOSSIL_TEST_CASE(c_test_process_terminate) {
    const char *path = "/bin/sleep";
    char *const args[] = { "sleep", "10", NULL };
    fossil_sys_process_t process = fossil_sys_process_create(path, args);

    ASSUME_ITS_TRUE(fossil_sys_process_terminate(process) == 0);

    int status;
    ASSUME_ITS_TRUE(fossil_sys_process_wait(process, &status) == 0);
}

FOSSIL_TEST_CASE(c_test_process_is_running) {
    const char *path = "/bin/sleep";
    char *const args[] = { "sleep", "2", NULL };
    fossil_sys_process_t process = fossil_sys_process_create(path, args);

    ASSUME_ITS_TRUE(fossil_sys_process_is_running(process) == 1);

    int status;
    ASSUME_ITS_TRUE(fossil_sys_process_wait(process, &status) == 0);
    ASSUME_ITS_TRUE(fossil_sys_process_is_running(process) == 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_process_tests) {
    FOSSIL_TEST_ADD(c_process_suite, c_test_process_create);
    FOSSIL_TEST_ADD(c_process_suite, c_test_process_wait);
    FOSSIL_TEST_ADD(c_process_suite, c_test_process_terminate);
    FOSSIL_TEST_ADD(c_process_suite, c_test_process_is_running);

    FOSSIL_TEST_REGISTER(c_process_suite);
}
