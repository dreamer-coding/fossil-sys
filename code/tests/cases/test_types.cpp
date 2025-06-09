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
FOSSIL_SUITE(cpp_types_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_types_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_types_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_test_type_max_u8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U8 == 0xFF);
}

FOSSIL_TEST(cpp_test_type_min_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I8 == -128);
}

FOSSIL_TEST(cpp_test_type_max_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I8 == 127);
}

FOSSIL_TEST(cpp_test_type_max_u16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U16 == 0xFFFF);
}

FOSSIL_TEST(cpp_test_type_min_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I16 == -32768);
}

FOSSIL_TEST(cpp_test_type_max_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I16 == 32767);
}

FOSSIL_TEST(cpp_test_type_max_u32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U32 == 0xFFFFFFFF);
}

FOSSIL_TEST(cpp_test_type_min_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I32 == -2147483648);
}

FOSSIL_TEST(cpp_test_type_max_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I32 == 2147483647);
}

FOSSIL_TEST(cpp_test_type_max_u64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_U64 == 0xFFFFFFFFFFFFFFFF);
}

FOSSIL_TEST(cpp_test_type_min_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MIN_I64 == -9223372036854775807LL);
}

FOSSIL_TEST(cpp_test_type_max_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_MAX_I64 == 9223372036854775807LL);
}

FOSSIL_TEST(cpp_test_type_alignof_i8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I8 == __alignof(i8));
}

FOSSIL_TEST(cpp_test_type_alignof_i16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I16 == __alignof(i16));
}

FOSSIL_TEST(cpp_test_type_alignof_i32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I32 == __alignof(i32));
}

FOSSIL_TEST(cpp_test_type_alignof_i64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_I64 == __alignof(i64));
}

FOSSIL_TEST(cpp_test_type_alignof_u8) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U8 == __alignof(u8));
}

FOSSIL_TEST(cpp_test_type_alignof_u16) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U16 == __alignof(u16));
}

FOSSIL_TEST(cpp_test_type_alignof_u32) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U32 == __alignof(u32));
}

FOSSIL_TEST(cpp_test_type_alignof_u64) {
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_ALIGNOF_U64 == __alignof(u64));
}

FOSSIL_TEST(cpp_test_type_cast_to_i32) {
    int value = 123;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_CAST_TO_I32(value) == (i32)value);
}

FOSSIL_TEST(cpp_test_type_cast_to_u32) {
    unsigned int value = 123;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_CAST_TO_U32(value) == (u32)value);
}

FOSSIL_TEST(cpp_test_type_is_negative) {
    int value = -1;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_IS_NEGATIVE(value));
}

FOSSIL_TEST(cpp_test_type_is_positive) {
    int value = 1;
    ASSUME_ITS_TRUE(FOSSIL_SYS_TYPE_IS_POSITIVE(value));
}

FOSSIL_TEST(cpp_test_class_i8_addition) {
    fossil::sys::I8 a(10);
    fossil::sys::I8 b(20);
    fossil::sys::I8 result = a + b;
    ASSUME_ITS_TRUE(result.value == 30);
}

FOSSIL_TEST(cpp_test_class_i8_subtraction) {
    fossil::sys::I8 a(20);
    fossil::sys::I8 b(10);
    fossil::sys::I8 result = a - b;
    ASSUME_ITS_TRUE(result.value == 10);
}

FOSSIL_TEST(cpp_test_class_i8_division) {
    fossil::sys::I8 a(20);
    fossil::sys::I8 b(10);
    fossil::sys::I8 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_u8_addition) {
    fossil::sys::U8 a(10);
    fossil::sys::U8 b(20);
    fossil::sys::U8 result = a + b;
    ASSUME_ITS_TRUE(result.value == 30);
}

FOSSIL_TEST(cpp_test_class_u8_subtraction) {
    fossil::sys::U8 a(20);
    fossil::sys::U8 b(10);
    fossil::sys::U8 result = a - b;
    ASSUME_ITS_TRUE(result.value == 10);
}

FOSSIL_TEST(cpp_test_class_u8_division) {
    fossil::sys::U8 a(20);
    fossil::sys::U8 b(10);
    fossil::sys::U8 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_i16_addition) {
    fossil::sys::I16 a(1000);
    fossil::sys::I16 b(2000);
    fossil::sys::I16 result = a + b;
    ASSUME_ITS_TRUE(result.value == 3000);
}

FOSSIL_TEST(cpp_test_class_i16_subtraction) {
    fossil::sys::I16 a(2000);
    fossil::sys::I16 b(1000);
    fossil::sys::I16 result = a - b;
    ASSUME_ITS_TRUE(result.value == 1000);
}

FOSSIL_TEST(cpp_test_class_i16_division) {
    fossil::sys::I16 a(2000);
    fossil::sys::I16 b(1000);
    fossil::sys::I16 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_u16_addition) {
    fossil::sys::U16 a(1000);
    fossil::sys::U16 b(2000);
    fossil::sys::U16 result = a + b;
    ASSUME_ITS_TRUE(result.value == 3000);
}

FOSSIL_TEST(cpp_test_class_u16_subtraction) {
    fossil::sys::U16 a(2000);
    fossil::sys::U16 b(1000);
    fossil::sys::U16 result = a - b;
    ASSUME_ITS_TRUE(result.value == 1000);
}

FOSSIL_TEST(cpp_test_class_u16_division) {
    fossil::sys::U16 a(2000);
    fossil::sys::U16 b(1000);
    fossil::sys::U16 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_i32_addition) {
    fossil::sys::I32 a(100);
    fossil::sys::I32 b(200);
    fossil::sys::I32 result = a + b;
    ASSUME_ITS_TRUE(result.value == 300);
}

FOSSIL_TEST(cpp_test_class_i32_subtraction) {
    fossil::sys::I32 a(200);
    fossil::sys::I32 b(100);
    fossil::sys::I32 result = a - b;
    ASSUME_ITS_TRUE(result.value == 100);
}

FOSSIL_TEST(cpp_test_class_i32_division) {
    fossil::sys::I32 a(200);
    fossil::sys::I32 b(100);
    fossil::sys::I32 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_u32_addition) {
    fossil::sys::U32 a(100);
    fossil::sys::U32 b(200);
    fossil::sys::U32 result = a + b;
    ASSUME_ITS_TRUE(result.value == 300);
}

FOSSIL_TEST(cpp_test_class_u32_subtraction) {
    fossil::sys::U32 a(200);
    fossil::sys::U32 b(100);
    fossil::sys::U32 result = a - b;
    ASSUME_ITS_TRUE(result.value == 100);
}

FOSSIL_TEST(cpp_test_class_u32_division) {
    fossil::sys::U32 a(200);
    fossil::sys::U32 b(100);
    fossil::sys::U32 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_i64_addition) {
    fossil::sys::I64 a(1000);
    fossil::sys::I64 b(2000);
    fossil::sys::I64 result = a + b;
    ASSUME_ITS_TRUE(result.value == 3000);
}

FOSSIL_TEST(cpp_test_class_i64_subtraction) {
    fossil::sys::I64 a(2000);
    fossil::sys::I64 b(1000);
    fossil::sys::I64 result = a - b;
    ASSUME_ITS_TRUE(result.value == 1000);
}

FOSSIL_TEST(cpp_test_class_i64_division) {
    fossil::sys::I64 a(2000);
    fossil::sys::I64 b(1000);
    fossil::sys::I64 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}

FOSSIL_TEST(cpp_test_class_u64_addition) {
    fossil::sys::U64 a(1000);
    fossil::sys::U64 b(2000);
    fossil::sys::U64 result = a + b;
    ASSUME_ITS_TRUE(result.value == 3000);
}

FOSSIL_TEST(cpp_test_class_u64_subtraction) {
    fossil::sys::U64 a(2000);
    fossil::sys::U64 b(1000);
    fossil::sys::U64 result = a - b;
    ASSUME_ITS_TRUE(result.value == 1000);
}

FOSSIL_TEST(cpp_test_class_u64_division) {
    fossil::sys::U64 a(2000);
    fossil::sys::U64 b(1000);
    fossil::sys::U64 result = a / b;
    ASSUME_ITS_TRUE(result.value == 2);
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_type_tests) {
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_u8);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_min_i8);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_i8);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_u16);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_min_i16);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_i16);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_u32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_min_i32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_i32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_u64);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_min_i64);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_max_i64);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_i8);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_i16);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_i32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_i64);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_u8);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_u16);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_u32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_alignof_u64);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_cast_to_i32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_cast_to_u32);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_is_negative);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_type_is_positive);

    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i8_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i8_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i8_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u8_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u8_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u8_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i16_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i16_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i16_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u16_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u16_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u16_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i32_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i32_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i32_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u32_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u32_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u32_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i64_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i64_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_i64_division);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u64_addition);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u64_subtraction);
    FOSSIL_TEST_ADD(cpp_types_suite, cpp_test_class_u64_division);

    FOSSIL_TEST_REGISTER(cpp_types_suite);
}
