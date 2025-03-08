/**
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
FOSSIL_TEST_SUITE(c_bitwise_suite);

// Setup function
FOSSIL_SETUP(c_bitwise_suite) {
    // Any necessary setup steps
}

// Teardown function
FOSSIL_TEARDOWN(c_bitwise_suite) {
    // Any necessary cleanup steps
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Counting Ones
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_count_ones) {
    // Signed
    int8_t test_val_i8 = 0b10101010;
    int16_t test_val_i16 = 0b1100110011001100;
    int32_t test_val_i32 = 0xFFFFFFFF;
    int64_t test_val_i64 = 0xF0F0F0F0F0F0F0F0;

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_count_ones_i8(test_val_i8), 4);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_count_ones_i16(test_val_i16), 8);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_count_ones_i32(test_val_i32), 32);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_count_ones_i64(test_val_i64), 32);

    // Unsigned
    uint8_t test_val_u8 = 0b10101010;
    uint16_t test_val_u16 = 0b1100110011001100;
    uint32_t test_val_u32 = 0xFFFFFFFF;
    uint64_t test_val_u64 = 0xF0F0F0F0F0F0F0F0;

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_count_ones_u8(test_val_u8), 4);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_count_ones_u16(test_val_u16), 8);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_count_ones_u32(test_val_u32), 32);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_count_ones_u64(test_val_u64), 32);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Reversal
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_bitwise_reverse) {
    // Signed
    int8_t test_val_i8 = 0b00001111;
    int16_t test_val_i16 = 0b0000000011111111;
    int32_t test_val_i32 = 0x12345678;
    int64_t test_val_i64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_reverse_i8(test_val_i8), 0b11110000);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_reverse_i16(test_val_i16), 0b1111111100000000);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_reverse_i32(test_val_i32), 0x1E6A2C48);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_reverse_i64(test_val_i64), 0x8000000000000001);

    // Unsigned
    uint8_t test_val_u8 = 0b00001111;
    uint16_t test_val_u16 = 0b0000000011111111;
    uint32_t test_val_u32 = 0x12345678;
    uint64_t test_val_u64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_reverse_u8(test_val_u8), 0b11110000);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_reverse_u16(test_val_u16), 0b1111111100000000);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_reverse_u32(test_val_u32), 0x1E6A2C48);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_reverse_u64(test_val_u64), 0x8000000000000001);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Rotation
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_bitwise_rotate_left) {
    // Signed
    int8_t test_val_i8 = 0b10000001;
    int16_t test_val_i16 = 0x8001;
    int32_t test_val_i32 = 0x12345678;
    int64_t test_val_i64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_left_i8(test_val_i8, 2), 0b00000110);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_left_i16(test_val_i16, 4), 0x0018);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_left_i32(test_val_i32, 8), 0x34567812);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_left_i64(test_val_i64, 16), 0x0000000000001880);

    // Unsigned
    uint8_t test_val_u8 = 0b10000001;
    uint16_t test_val_u16 = 0x8001;
    uint32_t test_val_u32 = 0x12345678;
    uint64_t test_val_u64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_left_u8(test_val_u8, 2), 0b00000110);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_left_u16(test_val_u16, 4), 0x0018);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_left_u32(test_val_u32, 8), 0x34567812);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_left_u64(test_val_u64, 16), 0x0000000000001880);
}

FOSSIL_TEST_CASE(c_test_bitwise_rotate_right) {
    // Signed
    int8_t test_val_i8 = 0b10000001;
    int16_t test_val_i16 = 0x8001;
    int32_t test_val_i32 = 0x12345678;
    int64_t test_val_i64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_right_i8(test_val_i8, 2), 0b01100000);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_right_i16(test_val_i16, 4), 0x1800);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_right_i32(test_val_i32, 8), 0x78123456);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_right_i64(test_val_i64, 16), 0x0001800000000000);

    // Unsigned
    uint8_t test_val_u8 = 0b10000001;
    uint16_t test_val_u16 = 0x8001;
    uint32_t test_val_u32 = 0x12345678;
    uint64_t test_val_u64 = 0x8000000000000001;

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_right_u8(test_val_u8, 2), 0b01100000);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_right_u16(test_val_u16, 4), 0x1800);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_right_u32(test_val_u32, 8), 0x78123456);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_right_u64(test_val_u64, 16), 0x0001800000000000);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_bitwise_tests) {
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_count_ones);
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_reverse);
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_rotate_left);
    FOSSIL_TEST_ADD(c_bitwise_suite, c_test_bitwise_rotate_right);

    FOSSIL_TEST_REGISTER(c_bitwise_suite);
}
