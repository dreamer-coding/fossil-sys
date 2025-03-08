/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic - Bitwise Operations Test
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
#include "fossil/sys/bitwise.h"

// Define the test suite
FOSSIL_TEST_SUITE(cpp_bitwise_suite);

// Setup function
FOSSIL_SETUP(cpp_bitwise_suite) {
    // Any necessary setup steps
}

// Teardown function
FOSSIL_TEARDOWN(cpp_bitwise_suite) {
    // Any necessary cleanup steps
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Counting Ones
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_count_ones) {
    // Variables
    const int8_t value_i8 = 0b10101010;
    const int16_t value_i16 = 0b1100110011001100;
    const int32_t value_i32 = 0xFFFFFFFF;
    const int64_t value_i64 = 0xF0F0F0F0F0F0F0F0;

    const uint8_t value_u8 = 0b10101010;
    const uint16_t value_u16 = 0b1100110011001100;
    const uint32_t value_u32 = 0xFFFFFFFF;
    const uint64_t value_u64 = 0xF0F0F0F0F0F0F0F0;

    // Signed
    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_count_ones_i8(value_i8), 4);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_count_ones_i16(value_i16), 8);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_count_ones_i32(value_i32), 32);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_count_ones_i64(value_i64), 32);

    // Unsigned
    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_count_ones_u8(value_u8), 4);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_count_ones_u16(value_u16), 8);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_count_ones_u32(value_u32), 32);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_count_ones_u64(value_u64), 32);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Reversal
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_bitwise_reverse) {
    // Variables
    const int8_t value_i8 = 0b00001111;
    const int16_t value_i16 = 0b0000000011111111;
    const int32_t value_i32 = 0x12345678;
    const int64_t value_i64 = 0x8000000000000001;

    const uint8_t value_u8 = 0b00001111;
    const uint16_t value_u16 = 0b0000000011111111;
    const uint32_t value_u32 = 0x12345678;
    const uint64_t value_u64 = 0x8000000000000001;

    // Signed
    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_reverse_i8(value_i8), 0b11110000);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_reverse_i16(value_i16), 0b1111111100000000);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_reverse_i32(value_i32), 0x1E6A2C48); // Expected reversed bit pattern
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_reverse_i64(value_i64), 0x8000000000000001);

    // Unsigned
    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_reverse_u8(value_u8), 0b11110000);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_reverse_u16(value_u16), 0b1111111100000000);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_reverse_u32(value_u32), 0x1E6A2C48);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_reverse_u64(value_u64), 0x8000000000000001);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Rotation
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_bitwise_rotate_left) {
    // Variables
    const int8_t value_i8_left = 0b10000001;
    const int16_t value_i16_left = 0x8001;
    const int32_t value_i32_left = 0x12345678;
    const int64_t value_i64_left = 0x8000000000000001;

    const uint8_t value_u8_left = 0b10000001;
    const uint16_t value_u16_left = 0x8001;
    const uint32_t value_u32_left = 0x12345678;
    const uint64_t value_u64_left = 0x8000000000000001;

    // Signed
    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_left_i8(value_i8_left, 2), 0b00000110);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_left_i16(value_i16_left, 4), 0x0018);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_left_i32(value_i32_left, 8), 0x34567812);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_left_i64(value_i64_left, 16), 0x0000000000001880);

    // Unsigned
    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_left_u8(value_u8_left, 2), 0b00000110);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_left_u16(value_u16_left, 4), 0x0018);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_left_u32(value_u32_left, 8), 0x34567812);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_left_u64(value_u64_left, 16), 0x0000000000001880);
}

FOSSIL_TEST_CASE(cpp_test_bitwise_rotate_right) {
    // Variables
    const int8_t value_i8_right = 0b10000001;
    const int16_t value_i16_right = 0x8001;
    const int32_t value_i32_right = 0x12345678;
    const int64_t value_i64_right = 0x8000000000000001;

    const uint8_t value_u8_right = 0b10000001;
    const uint16_t value_u16_right = 0x8001;
    const uint32_t value_u32_right = 0x12345678;
    const uint64_t value_u64_right = 0x8000000000000001;

    // Signed
    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_right_i8(value_i8_right, 2), 0b01100000);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_right_i16(value_i16_right, 4), 0x1800);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_right_i32(value_i32_right, 8), 0x78123456);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_right_i64(value_i64_right, 16), 0x0001800000000000);

    // Unsigned
    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_right_u8(value_u8_right, 2), 0b01100000);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_right_u16(value_u16_right, 4), 0x1800);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_right_u32(value_u32_right, 8), 0x78123456);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_right_u64(value_u64_right, 16), 0x0001800000000000);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_bitwise_tests) {
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_count_ones);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_bitwise_reverse);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_bitwise_rotate_left);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_bitwise_rotate_right);

    FOSSIL_TEST_REGISTER(cpp_bitwise_suite);
}
