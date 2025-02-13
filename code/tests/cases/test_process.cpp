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
FOSSIL_TEST_SUITE(cpp_process_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_process_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_process_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_process_class_spawn) {
    fossil::sys::Process process;
    std::vector<std::string> args = { "echo", "Hello, Fossil!" };
    fossil_sys_process_t proc = process.spawn("/bin/echo", args);

    int status;
    ASSUME_ITS_TRUE(process.wait(proc, &status) == 0);
}

FOSSIL_TEST_CASE(cpp_test_process_class_wait) {
    fossil::sys::Process process;
    std::vector<std::string> args = { "sleep", "1" };
    fossil_sys_process_t proc = process.spawn("/bin/sleep", args);

    int status;
    ASSUME_ITS_TRUE(process.wait(proc, &status) == 0);
}

FOSSIL_TEST_CASE(cpp_test_process_class_terminate) {
    fossil::sys::Process process;
    std::vector<std::string> args = { "sleep", "10" };
    fossil_sys_process_t proc = process.spawn("/bin/sleep", args);

    ASSUME_ITS_TRUE(process.terminate(proc) == 0);

    int status;
    ASSUME_ITS_TRUE(process.wait(proc, &status) == 0);
}

FOSSIL_TEST_CASE(cpp_test_process_class_is_running) {
    fossil::sys::Process process;
    std::vector<std::string> args = { "sleep", "2" };
    fossil_sys_process_t proc = process.spawn("/bin/sleep", args);

    ASSUME_ITS_TRUE(process.is_running(proc) == 1);

    int status;
    ASSUME_ITS_TRUE(process.wait(proc, &status) == 0);
    ASSUME_ITS_TRUE(process.is_running(proc) == 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_process_tests) {
    FOSSIL_TEST_ADD(cpp_process_suite, cpp_test_process_class_spawn);
    FOSSIL_TEST_ADD(cpp_process_suite, cpp_test_process_class_wait);
    FOSSIL_TEST_ADD(cpp_process_suite, cpp_test_process_class_terminate);
    FOSSIL_TEST_ADD(cpp_process_suite, cpp_test_process_class_is_running);

    FOSSIL_TEST_REGISTER(cpp_process_suite);
}
