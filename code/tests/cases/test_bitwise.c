/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * performance, cross-platform applications and libraries. The code contained
 * This file is part of the Fossil Logic project, which aims to develop high-
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
FOSSIL_TEST_SUITE(c_bitwise_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_bitwise_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_bitwise_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// ** Test fossil_sys_bitwise_parse Function **
FOSSIL_TEST_CASE(c_test_bitwise_parse) {
    fossil_sys_bitwise_entry_t entries[] = {
        {"read", 0x1},
        {"write", 0x2},
        {"execute", 0x4},
        {NULL, 0}
    };

    const fossil_sys_bitwise_table_t table = {entries, sizeof(entries) / sizeof(entries[0]) - 1};

    uint64_t result = fossil_sys_bitwise_parse("read|write", &table);
    ASSUME_ITS_EQUAL_I32(result, 0x3); // 0x1 | 0x2

    result = fossil_sys_bitwise_parse("execute", &table);
    ASSUME_ITS_EQUAL_I32(result, 0x4);

    result = fossil_sys_bitwise_parse("", &table);
    ASSUME_ITS_EQUAL_I32(result, 0x0);
}

// ** Test fossil_sys_bitwise_format Function **
FOSSIL_TEST_CASE(c_test_bitwise_format) {
    fossil_sys_bitwise_entry_t entries[] = {
        {"read", 0x1},
        {"write", 0x2},
        {"execute", 0x4},
        {NULL, 0}
    };

    const fossil_sys_bitwise_table_t table = {entries, sizeof(entries) / sizeof(entries[0]) - 1};

    char buffer[64];
    int status = fossil_sys_bitwise_format(0x3, &table, buffer, sizeof(buffer));
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_CSTR(buffer, "read|write");

    status = fossil_sys_bitwise_format(0x4, &table, buffer, sizeof(buffer));
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_CSTR(buffer, "execute");

    status = fossil_sys_bitwise_format(0x0, &table, buffer, sizeof(buffer));
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_CSTR(buffer, "");
}

// ** Test fossil_sys_bitwise_lookup Function **
FOSSIL_TEST_CASE(c_test_bitwise_lookup) {
    fossil_sys_bitwise_entry_t entries[] = {
        {"read", 0x1},
        {"write", 0x2},
        {"execute", 0x4},
        {NULL, 0}
    };
    const fossil_sys_bitwise_table_t table = {entries, sizeof(entries) / sizeof(entries[0]) - 1};
    uint64_t bit;
    int status = fossil_sys_bitwise_lookup("read", &table, &bit);
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_I32(bit, 0x1);
    status = fossil_sys_bitwise_lookup("write", &table, &bit);
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_I32(bit, 0x2);
    status = fossil_sys_bitwise_lookup("execute", &table, &bit);
    ASSUME_ITS_EQUAL_I32(status, 0);
    ASSUME_ITS_EQUAL_I32(bit, 0x4);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_bitwise_tests) {
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_parse);
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_format);
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_lookup);

    FOSSIL_TEST_REGISTER(c_bitwise_suite);
}
