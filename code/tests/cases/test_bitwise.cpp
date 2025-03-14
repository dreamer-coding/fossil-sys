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
    // Signed
    static const int8_t test_val_i8 = static_cast<int8_t>(0xAA);     // 10101010 in binary
    static const int16_t test_val_i16 = static_cast<int16_t>(0xCCCC); // 1100110011001100 in binary
    static const int32_t test_val_i32 = static_cast<int32_t>(0xFFFFFFFF);
    static const int64_t test_val_i64 = static_cast<int64_t>(0xF0F0F0F0F0F0F0F0LL);

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_count_ones_i8(test_val_i8), 4);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_count_ones_i16(test_val_i16), 8);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_count_ones_i32(test_val_i32), 32);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_count_ones_i64(test_val_i64), 32);

    // Unsigned
    static const uint8_t test_val_u8 = static_cast<uint8_t>(0xAA);     // 10101010 in binary
    static const uint16_t test_val_u16 = static_cast<uint16_t>(0xCCCC); // 1100110011001100 in binary
    static const uint32_t test_val_u32 = static_cast<uint32_t>(0xFFFFFFFFU);
    static const uint64_t test_val_u64 = static_cast<uint64_t>(0xF0F0F0F0F0F0F0F0ULL);

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_count_ones_u8(test_val_u8), 4);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_count_ones_u16(test_val_u16), 8);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_count_ones_u32(test_val_u32), 32);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_count_ones_u64(test_val_u64), 32);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Reversal
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_bitwise_reverse) {
    // Signed
    static const int8_t test_val_i8 = static_cast<int8_t>(0x0F);   // 00001111 in binary
    static const int16_t test_val_i16 = static_cast<int16_t>(0x00FF); // 0000000011111111 in binary
    static const int32_t test_val_i32 = static_cast<int32_t>(0x12345678);
    static const int64_t test_val_i64 = static_cast<int64_t>(0x8000000000000001LL);

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_reverse_i8(test_val_i8), 0xF0);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_reverse_i16(test_val_i16), 0xFF00);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_reverse_i32(test_val_i32), 0x1E6A2C48);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_reverse_i64(test_val_i64), 0x8000000000000001LL);

    // Unsigned
    static const uint8_t test_val_u8 = static_cast<uint8_t>(0x0F);
    static const uint16_t test_val_u16 = static_cast<uint16_t>(0x00FF);
    static const uint32_t test_val_u32 = static_cast<uint32_t>(0x12345678U);
    static const uint64_t test_val_u64 = static_cast<uint64_t>(0x8000000000000001ULL);

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_reverse_u8(test_val_u8), 0xF0);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_reverse_u16(test_val_u16), 0xFF00);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_reverse_u32(test_val_u32), 0x1E6A2C48U);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_reverse_u64(test_val_u64), 0x8000000000000001ULL);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Rotation
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_bitwise_rotate_left) {
    // Signed
    static const int8_t test_val_i8 = static_cast<int8_t>(0x81); // 10000001 in binary
    static const int16_t test_val_i16 = static_cast<int16_t>(0x8001);
    static const int32_t test_val_i32 = static_cast<int32_t>(0x12345678);
    static const int64_t test_val_i64 = static_cast<int64_t>(0x8000000000000001LL);

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_left_i8(test_val_i8, 2), 0x06);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_left_i16(test_val_i16, 4), 0x0018);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_left_i32(test_val_i32, 8), 0x34567812);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_left_i64(test_val_i64, 16), 0x0000000000001880LL);

    // Unsigned
    static const uint8_t test_val_u8 = static_cast<uint8_t>(0x81);
    static const uint16_t test_val_u16 = static_cast<uint16_t>(0x8001);
    static const uint32_t test_val_u32 = static_cast<uint32_t>(0x12345678U);
    static const uint64_t test_val_u64 = static_cast<uint64_t>(0x8000000000000001ULL);

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_left_u8(test_val_u8, 2), 0x06);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_left_u16(test_val_u16, 4), 0x0018);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_left_u32(test_val_u32, 8), 0x34567812U);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_left_u64(test_val_u64, 16), 0x0000000000001880ULL);
}

// * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases: Bit Rotation Right
// * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_bitwise_rotate_right) {
    // Signed
    static const int8_t test_val_i8 = static_cast<int8_t>(0x81);  // 10000001 in binary
    static const int16_t test_val_i16 = static_cast<int16_t>(0x8001);
    static const int32_t test_val_i32 = static_cast<int32_t>(0x12345678);
    static const int64_t test_val_i64 = static_cast<int64_t>(0x8000000000000001LL);

    ASSUME_ITS_EQUAL_I8(fossil_sys_bitwise_rotate_right_i8(test_val_i8, 2), 0x60);
    ASSUME_ITS_EQUAL_I16(fossil_sys_bitwise_rotate_right_i16(test_val_i16, 4), 0x1800);
    ASSUME_ITS_EQUAL_I32(fossil_sys_bitwise_rotate_right_i32(test_val_i32, 8), 0x78123456);
    ASSUME_ITS_EQUAL_I64(fossil_sys_bitwise_rotate_right_i64(test_val_i64, 16), 0x0001800000000000LL);

    // Unsigned
    static const uint8_t test_val_u8 = static_cast<uint8_t>(0x81);
    static const uint16_t test_val_u16 = static_cast<uint16_t>(0x8001);
    static const uint32_t test_val_u32 = static_cast<uint32_t>(0x12345678U);
    static const uint64_t test_val_u64 = static_cast<uint64_t>(0x8000000000000001ULL);

    ASSUME_ITS_EQUAL_U8(fossil_sys_bitwise_rotate_right_u8(test_val_u8, 2), 0x60);
    ASSUME_ITS_EQUAL_U16(fossil_sys_bitwise_rotate_right_u16(test_val_u16, 4), 0x1800);
    ASSUME_ITS_EQUAL_U32(fossil_sys_bitwise_rotate_right_u32(test_val_u32, 8), 0x78123456U);
    ASSUME_ITS_EQUAL_U64(fossil_sys_bitwise_rotate_right_u64(test_val_u64, 16), 0x0001800000000000ULL);
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
