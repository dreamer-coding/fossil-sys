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
FOSSIL_TEST_SUITE(c_syscall_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_syscall_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_syscall_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_sys_call_execute) {
    int result = fossil_sys_call_execute("echo Fossil Logic");
    ASSUME_ITS_TRUE(result == 0);
}

FOSSIL_TEST_CASE(c_test_sys_call_getpid) {
    int pid = fossil_sys_call_getpid();
    ASSUME_ITS_TRUE(pid > 0);
}

FOSSIL_TEST_CASE(c_test_sys_call_create_file) {
    const char *filename = "test_file.txt";
    int result = fossil_sys_call_create_file(filename);
    ASSUME_ITS_TRUE(result == 0);
    remove(filename); // Clean up the test file
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_syscall_tests) {
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_execute);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_getpid);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_create_file);

    FOSSIL_TEST_REGISTER(c_syscall_suite);
}
