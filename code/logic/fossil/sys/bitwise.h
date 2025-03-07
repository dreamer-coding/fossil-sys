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
#ifndef FOSSIL_SYS_BITWISE_H
#define FOSSIL_SYS_BITWISE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Macro definitions for bit-width constants.
 * These values represent the number of bits in each supported integer type.
 */
#define FOSSIL_SYS_BITWISE_BITS_8   8
#define FOSSIL_SYS_BITWISE_BITS_16 16
#define FOSSIL_SYS_BITWISE_BITS_32 32
#define FOSSIL_SYS_BITWISE_BITS_64 64

/* ============================================================================
 *                             UNSIGNED FUNCTIONS
 * ============================================================================ */

/**
 * @brief Counts the number of '1' bits in an 8-bit unsigned integer.
 * @param value The 8-bit unsigned integer.
 * @return The number of bits set to '1' in the given value.
 */
uint8_t fossil_sys_bitwise_count_ones_u8(uint8_t value);

/**
 * @brief Counts the number of '1' bits in a 16-bit unsigned integer.
 * @param value The 16-bit unsigned integer.
 * @return The number of bits set to '1' in the given value.
 */
uint16_t fossil_sys_bitwise_count_ones_u16(uint16_t value);

/**
 * @brief Counts the number of '1' bits in a 32-bit unsigned integer.
 * @param value The 32-bit unsigned integer.
 * @return The number of bits set to '1' in the given value.
 */
uint32_t fossil_sys_bitwise_count_ones_u32(uint32_t value);

/**
 * @brief Counts the number of '1' bits in a 64-bit unsigned integer.
 * @param value The 64-bit unsigned integer.
 * @return The number of bits set to '1' in the given value.
 */
uint64_t fossil_sys_bitwise_count_ones_u64(uint64_t value);

/**
 * @brief Reverses the bit order of an 8-bit unsigned integer.
 * @param value The 8-bit unsigned integer.
 * @return The value with its bits reversed.
 */
uint8_t fossil_sys_bitwise_reverse_u8(uint8_t value);

/**
 * @brief Reverses the bit order of a 16-bit unsigned integer.
 * @param value The 16-bit unsigned integer.
 * @return The value with its bits reversed.
 */
uint16_t fossil_sys_bitwise_reverse_u16(uint16_t value);

/**
 * @brief Reverses the bit order of a 32-bit unsigned integer.
 * @param value The 32-bit unsigned integer.
 * @return The value with its bits reversed.
 */
uint32_t fossil_sys_bitwise_reverse_u32(uint32_t value);

/**
 * @brief Reverses the bit order of a 64-bit unsigned integer.
 * @param value The 64-bit unsigned integer.
 * @return The value with its bits reversed.
 */
uint64_t fossil_sys_bitwise_reverse_u64(uint64_t value);

/**
 * @brief Rotates bits of an 8-bit unsigned integer to the left.
 * @param value The 8-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 */
uint8_t fossil_sys_bitwise_rotate_left_u8(uint8_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 16-bit unsigned integer to the left.
 * @param value The 16-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 */
uint16_t fossil_sys_bitwise_rotate_left_u16(uint16_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 32-bit unsigned integer to the left.
 * @param value The 32-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 */
uint32_t fossil_sys_bitwise_rotate_left_u32(uint32_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 64-bit unsigned integer to the left.
 * @param value The 64-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 */
uint64_t fossil_sys_bitwise_rotate_left_u64(uint64_t value, uint8_t shift);

/**
 * @brief Rotates bits of an 8-bit unsigned integer to the right.
 * @param value The 8-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 */
uint8_t fossil_sys_bitwise_rotate_right_u8(uint8_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 16-bit unsigned integer to the right.
 * @param value The 16-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 */
uint16_t fossil_sys_bitwise_rotate_right_u16(uint16_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 32-bit unsigned integer to the right.
 * @param value The 32-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 */
uint32_t fossil_sys_bitwise_rotate_right_u32(uint32_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 64-bit unsigned integer to the right.
 * @param value The 64-bit unsigned integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 */
uint64_t fossil_sys_bitwise_rotate_right_u64(uint64_t value, uint8_t shift);

/* ============================================================================
 *                              SIGNED FUNCTIONS
 * ============================================================================ */

/**
 * @brief Counts the number of '1' bits in an 8-bit signed integer.
 * @param value The 8-bit signed integer.
 * @return The number of bits set to '1' in the given value.
 * @note The sign bit is included in the count. The function internally casts to `uint8_t` for bitwise operations.
 */
int8_t fossil_sys_bitwise_count_ones_i8(int8_t value);

/**
 * @brief Counts the number of '1' bits in a 16-bit signed integer.
 * @param value The 16-bit signed integer.
 * @return The number of bits set to '1' in the given value.
 * @note The sign bit is included in the count. The function internally casts to `uint16_t` for bitwise operations.
 */
int16_t fossil_sys_bitwise_count_ones_i16(int16_t value);

/**
 * @brief Counts the number of '1' bits in a 32-bit signed integer.
 * @param value The 32-bit signed integer.
 * @return The number of bits set to '1' in the given value.
 * @note The sign bit is included in the count. The function internally casts to `uint32_t` for bitwise operations.
 */
int32_t fossil_sys_bitwise_count_ones_i32(int32_t value);

/**
 * @brief Counts the number of '1' bits in a 64-bit signed integer.
 * @param value The 64-bit signed integer.
 * @return The number of bits set to '1' in the given value.
 * @note The sign bit is included in the count. The function internally casts to `uint64_t` for bitwise operations.
 */
int64_t fossil_sys_bitwise_count_ones_i64(int64_t value);

/**
 * @brief Reverses the bit order of an 8-bit signed integer.
 * @param value The 8-bit signed integer.
 * @return The value with its bits reversed.
 * @note The sign bit is preserved if the platform uses two's complement representation.
 *       The function internally casts to `uint8_t` for bitwise reversal.
 */
int8_t fossil_sys_bitwise_reverse_i8(int8_t value);

/**
 * @brief Reverses the bit order of a 16-bit signed integer.
 * @param value The 16-bit signed integer.
 * @return The value with its bits reversed.
 * @note The sign bit is preserved if the platform uses two's complement representation.
 *       The function internally casts to `uint16_t` for bitwise reversal.
 */
int16_t fossil_sys_bitwise_reverse_i16(int16_t value);

/**
 * @brief Reverses the bit order of a 32-bit signed integer.
 * @param value The 32-bit signed integer.
 * @return The value with its bits reversed.
 * @note The sign bit is preserved if the platform uses two's complement representation.
 *       The function internally casts to `uint32_t` for bitwise reversal.
 */
int32_t fossil_sys_bitwise_reverse_i32(int32_t value);

/**
 * @brief Reverses the bit order of a 64-bit signed integer.
 * @param value The 64-bit signed integer.
 * @return The value with its bits reversed.
 * @note The sign bit is preserved if the platform uses two's complement representation.
 *       The function internally casts to `uint64_t` for bitwise reversal.
 */
int64_t fossil_sys_bitwise_reverse_i64(int64_t value);

/**
 * @brief Rotates bits of an 8-bit signed integer to the left.
 * @param value The 8-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint8_t`, rotating, and then casting back to `int8_t`.
 */
int8_t fossil_sys_bitwise_rotate_left_i8(int8_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 16-bit signed integer to the left.
 * @param value The 16-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint16_t`, rotating, and then casting back to `int16_t`.
 */
int16_t fossil_sys_bitwise_rotate_left_i16(int16_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 32-bit signed integer to the left.
 * @param value The 32-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint32_t`, rotating, and then casting back to `int32_t`.
 */
int32_t fossil_sys_bitwise_rotate_left_i32(int32_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 64-bit signed integer to the left.
 * @param value The 64-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after left rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint64_t`, rotating, and then casting back to `int64_t`.
 */
int64_t fossil_sys_bitwise_rotate_left_i64(int64_t value, uint8_t shift);

/**
 * @brief Rotates bits of an 8-bit signed integer to the right.
 * @param value The 8-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint8_t`, rotating, and then casting back to `int8_t`.
 */
int8_t fossil_sys_bitwise_rotate_right_i8(int8_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 16-bit signed integer to the right.
 * @param value The 16-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint16_t`, rotating, and then casting back to `int16_t`.
 */
int16_t fossil_sys_bitwise_rotate_right_i16(int16_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 32-bit signed integer to the right.
 * @param value The 32-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint32_t`, rotating, and then casting back to `int32_t`.
 */
int32_t fossil_sys_bitwise_rotate_right_i32(int32_t value, uint8_t shift);

/**
 * @brief Rotates bits of a 64-bit signed integer to the right.
 * @param value The 64-bit signed integer.
 * @param shift The number of positions to rotate.
 * @return The resulting value after right rotation.
 * @note The sign bit is not treated specially. The function performs an unsigned rotation
 *       by casting to `uint64_t`, rotating, and then casting back to `int64_t`.
 */
int64_t fossil_sys_bitwise_rotate_right_i64(int64_t value, uint8_t shift);

#ifdef __cplusplus
}

#include <stdint.h>

namespace fossil {
namespace sys {

// Class for 8-bit signed integer bitwise operations
class BitwiseI8 {
public:
    /**
     * @brief Counts the number of '1' bits in an 8-bit signed integer.
     * @param value The 8-bit signed integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_i8`.
     */
    static int count_ones(int8_t value) {
        return fossil_sys_bitwise_count_ones_i8(value);
    }

    /**
     * @brief Reverses the bit order of an 8-bit signed integer.
     * @param value The 8-bit signed integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_i8`.
     */
    static int8_t reverse_bits(int8_t value) {
        return fossil_sys_bitwise_reverse_i8(value);
    }

    /**
     * @brief Rotates bits of an 8-bit signed integer to the left.
     * @param value The 8-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_i8`.
     */
    static int8_t rotate_left(int8_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_i8(value, shift);
    }

    /**
     * @brief Rotates bits of an 8-bit signed integer to the right.
     * @param value The 8-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_i8`.
     */
    static int8_t rotate_right(int8_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_i8(value, shift);
    }
};

// Class for 16-bit signed integer bitwise operations
class BitwiseI16 {
public:
    /**
     * @brief Counts the number of '1' bits in a 16-bit signed integer.
     * @param value The 16-bit signed integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_i16`.
     */
    static int count_ones(int16_t value) {
        return fossil_sys_bitwise_count_ones_i16(value);
    }

    /**
     * @brief Reverses the bit order of a 16-bit signed integer.
     * @param value The 16-bit signed integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_i16`.
     */
    static int16_t reverse_bits(int16_t value) {
        return fossil_sys_bitwise_reverse_i16(value);
    }

    /**
     * @brief Rotates bits of a 16-bit signed integer to the left.
     * @param value The 16-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_i16`.
     */
    static int16_t rotate_left(int16_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_i16(value, shift);
    }

    /**
     * @brief Rotates bits of a 16-bit signed integer to the right.
     * @param value The 16-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_i16`.
     */
    static int16_t rotate_right(int16_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_i16(value, shift);
    }
};

// Class for 32-bit signed integer bitwise operations
class BitwiseI32 {
public:
    /**
     * @brief Counts the number of '1' bits in a 32-bit signed integer.
     * @param value The 32-bit signed integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_i32`.
     */
    static int count_ones(int32_t value) {
        return fossil_sys_bitwise_count_ones_i32(value);
    }

    /**
     * @brief Reverses the bit order of a 32-bit signed integer.
     * @param value The 32-bit signed integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_i32`.
     */
    static int32_t reverse_bits(int32_t value) {
        return fossil_sys_bitwise_reverse_i32(value);
    }

    /**
     * @brief Rotates bits of a 32-bit signed integer to the left.
     * @param value The 32-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_i32`.
     */
    static int32_t rotate_left(int32_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_i32(value, shift);
    }

    /**
     * @brief Rotates bits of a 32-bit signed integer to the right.
     * @param value The 32-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_i32`.
     */
    static int32_t rotate_right(int32_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_i32(value, shift);
    }
};

// Class for 64-bit signed integer bitwise operations
class BitwiseI64 {
public:
    /**
     * @brief Counts the number of '1' bits in a 64-bit signed integer.
     * @param value The 64-bit signed integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_i64`.
     */
    static int count_ones(int64_t value) {
        return fossil_sys_bitwise_count_ones_i64(value);
    }

    /**
     * @brief Reverses the bit order of a 64-bit signed integer.
     * @param value The 64-bit signed integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_i64`.
     */
    static int64_t reverse_bits(int64_t value) {
        return fossil_sys_bitwise_reverse_i64(value);
    }

    /**
     * @brief Rotates bits of a 64-bit signed integer to the left.
     * @param value The 64-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_i64`.
     */
    static int64_t rotate_left(int64_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_i64(value, shift);
    }

    /**
     * @brief Rotates bits of a 64-bit signed integer to the right.
     * @param value The 64-bit signed integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_i64`.
     */
    static int64_t rotate_right(int64_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_i64(value, shift);
    }
};

// Class for 8-bit unsigned integer bitwise operations
class BitwiseU8 {
public:
    /**
     * @brief Counts the number of '1' bits in an 8-bit unsigned integer.
     * @param value The 8-bit unsigned integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_u8`.
     */
    static int count_ones(uint8_t value) {
        return fossil_sys_bitwise_count_ones_u8(value);
    }

    /**
     * @brief Reverses the bit order of an 8-bit unsigned integer.
     * @param value The 8-bit unsigned integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_u8`.
     */
    static uint8_t reverse_bits(uint8_t value) {
        return fossil_sys_bitwise_reverse_u8(value);
    }

    /**
     * @brief Rotates bits of an 8-bit unsigned integer to the left.
     * @param value The 8-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_u8`.
     */
    static uint8_t rotate_left(uint8_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_u8(value, shift);
    }

    /**
     * @brief Rotates bits of an 8-bit unsigned integer to the right.
     * @param value The 8-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_u8`.
     */
    static uint8_t rotate_right(uint8_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_u8(value, shift);
    }
};

// Class for 16-bit unsigned integer bitwise operations
class BitwiseU16 {
public:
    /**
     * @brief Counts the number of '1' bits in a 16-bit unsigned integer.
     * @param value The 16-bit unsigned integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_u16`.
     */
    static int count_ones(uint16_t value) {
        return fossil_sys_bitwise_count_ones_u16(value);
    }

    /**
     * @brief Reverses the bit order of a 16-bit unsigned integer.
     * @param value The 16-bit unsigned integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_u16`.
     */
    static uint16_t reverse_bits(uint16_t value) {
        return fossil_sys_bitwise_reverse_u16(value);
    }

    /**
     * @brief Rotates bits of a 16-bit unsigned integer to the left.
     * @param value The 16-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_u16`.
     */
    static uint16_t rotate_left(uint16_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_u16(value, shift);
    }

    /**
     * @brief Rotates bits of a 16-bit unsigned integer to the right.
     * @param value The 16-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_u16`.
     */
    static uint16_t rotate_right(uint16_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_u16(value, shift);
    }
};

// Class for 32-bit unsigned integer bitwise operations
class BitwiseU32 {
public:
    /**
     * @brief Counts the number of '1' bits in a 32-bit unsigned integer.
     * @param value The 32-bit unsigned integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_u32`.
     */
    static int count_ones(uint32_t value) {
        return fossil_sys_bitwise_count_ones_u32(value);
    }

    /**
     * @brief Reverses the bit order of a 32-bit unsigned integer.
     * @param value The 32-bit unsigned integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_u32`.
     */
    static uint32_t reverse_bits(uint32_t value) {
        return fossil_sys_bitwise_reverse_u32(value);
    }

    /**
     * @brief Rotates bits of a 32-bit unsigned integer to the left.
     * @param value The 32-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_u32`.
     */
    static uint32_t rotate_left(uint32_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_u32(value, shift);
    }

    /**
     * @brief Rotates bits of a 32-bit unsigned integer to the right.
     * @param value The 32-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_u32`.
     */
    static uint32_t rotate_right(uint32_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_u32(value, shift);
    }
};

// Class for 64-bit unsigned integer bitwise operations
class BitwiseU64 {
public:
    /**
     * @brief Counts the number of '1' bits in a 64-bit unsigned integer.
     * @param value The 64-bit unsigned integer.
     * @return The number of bits set to '1' in the given value.
     * @note Wraps the C function `fossil_sys_bitwise_count_ones_u64`.
     */
    static int count_ones(uint64_t value) {
        return fossil_sys_bitwise_count_ones_u64(value);
    }

    /**
     * @brief Reverses the bit order of a 64-bit unsigned integer.
     * @param value The 64-bit unsigned integer.
     * @return The value with its bits reversed.
     * @note Wraps the C function `fossil_sys_bitwise_reverse_u64`.
     */
    static uint64_t reverse_bits(uint64_t value) {
        return fossil_sys_bitwise_reverse_u64(value);
    }

    /**
     * @brief Rotates bits of a 64-bit unsigned integer to the left.
     * @param value The 64-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after left rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_left_u64`.
     */
    static uint64_t rotate_left(uint64_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_left_u64(value, shift);
    }

    /**
     * @brief Rotates bits of a 64-bit unsigned integer to the right.
     * @param value The 64-bit unsigned integer.
     * @param shift The number of positions to rotate.
     * @return The resulting value after right rotation.
     * @note Wraps the C function `fossil_sys_bitwise_rotate_right_u64`.
     */
    static uint64_t rotate_right(uint64_t value, unsigned int shift) {
        return fossil_sys_bitwise_rotate_right_u64(value, shift);
    }

};

} // namespace sys
} // namespace fossil

#endif

#endif /* FOSSIL_SYS_BITWISE_H */
