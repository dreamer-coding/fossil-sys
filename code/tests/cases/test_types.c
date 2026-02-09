/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
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
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(i8) == _Alignof(i8));
}

FOSSIL_TEST(c_test_type_alignof_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(i16) == _Alignof(i16));
}

FOSSIL_TEST(c_test_type_alignof_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(i32) == _Alignof(i32));
}

FOSSIL_TEST(c_test_type_alignof_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(i64) == _Alignof(i64));
}

FOSSIL_TEST(c_test_type_alignof_u8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(u8) == _Alignof(u8));
}

FOSSIL_TEST(c_test_type_alignof_u16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(u16) == _Alignof(u16));
}

FOSSIL_TEST(c_test_type_alignof_u32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(u32) == _Alignof(u32));
}

FOSSIL_TEST(c_test_type_alignof_u64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF(u64) == _Alignof(u64));
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
