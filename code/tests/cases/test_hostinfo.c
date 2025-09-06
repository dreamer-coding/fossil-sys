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
#include <fossil/pizza/framework.h>

#include "fossil/sys/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_hostinfo_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_hostinfo_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_hostinfo_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_hostinfo_get_system) {
    fossil_sys_hostinfo_system_t info;
    int result = fossil_sys_hostinfo_get_system(&info);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(strlen(info.os_name) > 0);
    ASSUME_ITS_TRUE(strlen(info.os_version) > 0);
    ASSUME_ITS_TRUE(strlen(info.kernel_version) > 0);
}

FOSSIL_TEST(c_test_hostinfo_get_memory) {
    fossil_sys_hostinfo_memory_t info;
    int result = fossil_sys_hostinfo_get_memory(&info);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(info.total_memory > 0);
    ASSUME_ITS_TRUE(info.free_memory <= info.total_memory);
}

FOSSIL_TEST(c_test_hostinfo_get_architecture) {
    fossil_sys_hostinfo_architecture_t info;
    int result = fossil_sys_hostinfo_get_architecture(&info);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(strlen(info.name) > 0);
}

FOSSIL_TEST(c_test_hostinfo_get_endianness) {
    fossil_sys_hostinfo_endianness_t info;
    int result = fossil_sys_hostinfo_get_endianness(&info);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(info.is_little_endian == 0 || info.is_little_endian == 1);
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_hostinfo_tests) {
    FOSSIL_TEST_ADD(c_hostinfo_suite, c_test_hostinfo_get_system);
    FOSSIL_TEST_ADD(c_hostinfo_suite, c_test_hostinfo_get_memory);
    FOSSIL_TEST_ADD(c_hostinfo_suite, c_test_hostinfo_get_architecture);
    FOSSIL_TEST_ADD(c_hostinfo_suite, c_test_hostinfo_get_endianness);

    FOSSIL_TEST_REGISTER(c_hostinfo_suite);
}
