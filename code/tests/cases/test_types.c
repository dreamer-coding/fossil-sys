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
FOSSIL_SUITE(c_types_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_types_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_types_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_type_max_u8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U8 == 0xFF);
}

FOSSIL_TEST(c_test_type_min_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I8 == -128);
}

FOSSIL_TEST(c_test_type_max_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I8 == 127);
}

FOSSIL_TEST(c_test_type_max_u16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U16 == 0xFFFF);
}

FOSSIL_TEST(c_test_type_min_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I16 == -32768);
}

FOSSIL_TEST(c_test_type_max_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I16 == 32767);
}

FOSSIL_TEST(c_test_type_max_u32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U32 == 0xFFFFFFFF);
}

FOSSIL_TEST(c_test_type_min_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I32 == -2147483648);
}

FOSSIL_TEST(c_test_type_max_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I32 == 2147483647);
}

FOSSIL_TEST(c_test_type_max_u64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U64 == 0xFFFFFFFFFFFFFFFF);
}

FOSSIL_TEST(c_test_type_min_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I64 == -9223372036854775807LL);
}

FOSSIL_TEST(c_test_type_max_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I64 == 9223372036854775807LL);
}

FOSSIL_TEST(c_test_type_alignof_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I8 == __alignof(i8));
}

FOSSIL_TEST(c_test_type_alignof_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I16 == __alignof(i16));
}

FOSSIL_TEST(c_test_type_alignof_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I32 == __alignof(i32));
}

FOSSIL_TEST(c_test_type_alignof_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I64 == __alignof(i64));
}

FOSSIL_TEST(c_test_type_alignof_u8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U8 == __alignof(u8));
}

FOSSIL_TEST(c_test_type_alignof_u16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U16 == __alignof(u16));
}

FOSSIL_TEST(c_test_type_alignof_u32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U32 == __alignof(u32));
}

FOSSIL_TEST(c_test_type_alignof_u64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U64 == __alignof(u64));
}

FOSSIL_TEST(c_test_type_cast_to_i32) {
    int value = 123;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_CAST_TO_I32(value) == (i32)value);
}

FOSSIL_TEST(c_test_type_cast_to_u32) {
    unsigned int value = 123;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_CAST_TO_U32(value) == (u32)value);
}

FOSSIL_TEST(c_test_type_is_negative) {
    int value = -1;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_IS_NEGATIVE(value));
}

FOSSIL_TEST(c_test_type_is_positive) {
    int value = 1;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_IS_POSITIVE(value));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_type_tests) {
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_u8);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_min_i8);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_i8);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_u16);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_min_i16);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_i16);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_u32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_min_i32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_i32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_u64);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_min_i64);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_max_i64);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_i8);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_i16);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_i32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_i64);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_u8);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_u16);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_u32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_alignof_u64);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_cast_to_i32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_cast_to_u32);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_is_negative);
    FOSSIL_TEST_ADD(c_types_suite, c_test_type_is_positive);

    FOSSIL_TEST_REGISTER(c_types_suite);
}
