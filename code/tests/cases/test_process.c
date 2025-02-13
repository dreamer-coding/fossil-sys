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

FOSSIL_TEST_CASE(c_test_process_spawn) {
    const char *path = "/bin/echo";
    char *const argv[] = { "echo", "Hello, World!", NULL };
    char *const envp[] = { NULL };

    int pid = fossil_sys_process_spawn(path, argv, envp);
    ASSUME_ITS_TRUE(pid > 0); // Ensure process is spawned successfully

    int status;
    int wait_result = fossil_sys_process_wait(pid, &status);
    ASSUME_ITS_TRUE(wait_result == 0); // Ensure process wait is successful
    ASSUME_ITS_TRUE(status == 0); // Ensure process exited with status 0
}

FOSSIL_TEST_CASE(c_test_process_wait) {
    const char *path = "/bin/sleep";
    char *const argv[] = { "sleep", "1", NULL };
    char *const envp[] = { NULL };

    int pid = fossil_sys_process_spawn(path, argv, envp);
    ASSUME_ITS_TRUE(pid > 0); // Ensure process is spawned successfully

    int status;
    int wait_result = fossil_sys_process_wait(pid, &status);
    ASSUME_ITS_TRUE(wait_result == 0); // Ensure process wait is successful
    ASSUME_ITS_TRUE(status == 0); // Ensure process exited with status 0
}

FOSSIL_TEST_CASE(c_test_process_terminate) {
    const char *path = "/bin/sleep";
    char *const argv[] = { "sleep", "10", NULL };
    char *const envp[] = { NULL };

    int pid = fossil_sys_process_spawn(path, argv, envp);
    ASSUME_ITS_TRUE(pid > 0); // Ensure process is spawned successfully

    int terminate_result = fossil_sys_process_terminate(pid);
    ASSUME_ITS_TRUE(terminate_result == 0); // Ensure process termination is successful

    int status;
    int wait_result = fossil_sys_process_wait(pid, &status);
    ASSUME_ITS_TRUE(wait_result == 0); // Ensure process wait is successful
    ASSUME_ITS_TRUE(status != 0); // Ensure process did not exit normally
}

FOSSIL_TEST_CASE(c_test_process_is_running) {
    const char *path = "/bin/sleep";
    char *const argv[] = { "sleep", "2", NULL };
    char *const envp[] = { NULL };

    int pid = fossil_sys_process_spawn(path, argv, envp);
    ASSUME_ITS_TRUE(pid > 0); // Ensure process is spawned successfully

    ASSUME_ITS_TRUE(fossil_sys_process_is_running(pid) == 1); // Ensure process is running

    int status;
    fossil_sys_process_wait(pid, &status); // Wait for process to finish

    ASSUME_ITS_TRUE(fossil_sys_process_is_running(pid) == 0); // Ensure process is no longer running
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_process_tests) {
    FOSSIL_TEST_ADD(c_process_suite, c_test_process_spawn);
    // FOSSIL_TEST_ADD(c_process_suite, c_test_process_wait);
    // FOSSIL_TEST_ADD(c_process_suite, c_test_process_terminate);
    // FOSSIL_TEST_ADD(c_process_suite, c_test_process_is_running);

    FOSSIL_TEST_REGISTER(c_process_suite);
}
