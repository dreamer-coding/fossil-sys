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
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 *  Bitwise Operations Library - Fossil Sys Bitwise
 *  This library provides portable bitwise operations for unsigned integers.
 *  It supports 8, 16, 32, and 64-bit operations and is compatible with both 
 *  C11 and C23. It also uses C string parameters where necessary for 
 *  serialization.
 * ============================================================================ */

/* ------------------------------------------------------------------------
 *  Basic Bitwise Operations
 *  These functions perform common bitwise operations: AND, OR, XOR, and NOT.
 *  Operations are available for 8, 16, 32, and 64-bit unsigned integers.
 * ------------------------------------------------------------------------ */

/**
 * Perform a bitwise AND operation between two 8-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a & b).
 */
uint8_t fossil_sys_bitwise_and_u8(uint8_t a, uint8_t b);

/**
 * Perform a bitwise AND operation between two 16-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a & b).
 */
uint16_t fossil_sys_bitwise_and_u16(uint16_t a, uint16_t b);

/**
 * Perform a bitwise AND operation between two 32-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a & b).
 */
uint32_t fossil_sys_bitwise_and_u32(uint32_t a, uint32_t b);

/**
 * Perform a bitwise AND operation between two 64-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a & b).
 */
uint64_t fossil_sys_bitwise_and_u64(uint64_t a, uint64_t b);

/**
 * Perform a bitwise OR operation between two 8-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a | b).
 */
uint8_t fossil_sys_bitwise_or_u8(uint8_t a, uint8_t b);

/**
 * Perform a bitwise OR operation between two 16-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a | b).
 */
uint16_t fossil_sys_bitwise_or_u16(uint16_t a, uint16_t b);

/**
 * Perform a bitwise OR operation between two 32-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a | b).
 */
uint32_t fossil_sys_bitwise_or_u32(uint32_t a, uint32_t b);

/**
 * Perform a bitwise OR operation between two 64-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a | b).
 */
uint64_t fossil_sys_bitwise_or_u64(uint64_t a, uint64_t b);

/**
 * Perform a bitwise XOR operation between two 8-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a ^ b).
 */
uint8_t fossil_sys_bitwise_xor_u8(uint8_t a, uint8_t b);

/**
 * Perform a bitwise XOR operation between two 16-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a ^ b).
 */
uint16_t fossil_sys_bitwise_xor_u16(uint16_t a, uint16_t b);

/**
 * Perform a bitwise XOR operation between two 32-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a ^ b).
 */
uint32_t fossil_sys_bitwise_xor_u32(uint32_t a, uint32_t b);

/**
 * Perform a bitwise XOR operation between two 64-bit unsigned integers.
 * @param a First operand.
 * @param b Second operand.
 * @return Result of (a ^ b).
 */
uint64_t fossil_sys_bitwise_xor_u64(uint64_t a, uint64_t b);

/**
 * Perform a bitwise NOT operation on an 8-bit unsigned integer.
 * @param a The operand.
 * @return Result of (~a).
 */
uint8_t fossil_sys_bitwise_not_u8(uint8_t a);

/**
 * Perform a bitwise NOT operation on a 16-bit unsigned integer.
 * @param a The operand.
 * @return Result of (~a).
 */
uint16_t fossil_sys_bitwise_not_u16(uint16_t a);

/**
 * Perform a bitwise NOT operation on a 32-bit unsigned integer.
 * @param a The operand.
 * @return Result of (~a).
 */
uint32_t fossil_sys_bitwise_not_u32(uint32_t a);

/**
 * Perform a bitwise NOT operation on a 64-bit unsigned integer.
 * @param a The operand.
 * @return Result of (~a).
 */
uint64_t fossil_sys_bitwise_not_u64(uint64_t a);

/* ------------------------------------------------------------------------
 *  Bitwise Shift Operations
 *  These functions perform left and right shifts on integers of size
 *  8, 16, 32, and 64 bits.
 * ------------------------------------------------------------------------ */

/**
 * Perform a left bit shift on an 8-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a << shift).
 */
uint8_t fossil_sys_bitwise_lshift_u8(uint8_t a, uint8_t shift);

/**
 * Perform a left bit shift on a 16-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a << shift).
 */
uint16_t fossil_sys_bitwise_lshift_u16(uint16_t a, uint8_t shift);

/**
 * Perform a left bit shift on a 32-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a << shift).
 */
uint32_t fossil_sys_bitwise_lshift_u32(uint32_t a, uint8_t shift);

/**
 * Perform a left bit shift on a 64-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a << shift).
 */
uint64_t fossil_sys_bitwise_lshift_u64(uint64_t a, uint8_t shift);

/**
 * Perform a right bit shift on an 8-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a >> shift).
 */
uint8_t fossil_sys_bitwise_rshift_u8(uint8_t a, uint8_t shift);

/**
 * Perform a right bit shift on a 16-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a >> shift).
 */
uint16_t fossil_sys_bitwise_rshift_u16(uint16_t a, uint8_t shift);

/**
 * Perform a right bit shift on a 32-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a >> shift).
 */
uint32_t fossil_sys_bitwise_rshift_u32(uint32_t a, uint8_t shift);

/**
 * Perform a right bit shift on a 64-bit unsigned integer.
 * @param a The value to shift.
 * @param shift Number of positions to shift.
 * @return The shifted result (a >> shift).
 */
uint64_t fossil_sys_bitwise_rshift_u64(uint64_t a, uint8_t shift);

/* ------------------------------------------------------------------------
 *  Bit Manipulation Functions
 *  These functions allow setting, clearing, toggling, and testing bits.
 *  Operations are available for 32-bit unsigned integers.
 * ------------------------------------------------------------------------ */

/**
 * Check if a specific bit in a 32-bit unsigned integer is set.
 * @param value The number to check.
 * @param bit The bit position (0-31).
 * @return true if the bit is set, false otherwise.
 */
bool fossil_sys_bitwise_test_u32(uint32_t value, uint8_t bit);

/**
 * Set a specific bit in a 32-bit unsigned integer.
 * @param value The number to modify.
 * @param bit The bit position (0-31).
 * @return The modified number with the bit set.
 */
uint32_t fossil_sys_bitwise_set_u32(uint32_t value, uint8_t bit);

/**
 * Clear a specific bit in a 32-bit unsigned integer.
 * @param value The number to modify.
 * @param bit The bit position (0-31).
 * @return The modified number with the bit cleared.
 */
uint32_t fossil_sys_bitwise_clear_u32(uint32_t value, uint8_t bit);

/**
 * Toggle a specific bit in a 32-bit unsigned integer.
 * @param value The number to modify.
 * @param bit The bit position (0-31).
 * @return The modified number with the bit toggled.
 */
uint32_t fossil_sys_bitwise_toggle_u32(uint32_t value, uint8_t bit);

/* ------------------------------------------------------------------------
 *  Serialization Functions
 *  These functions convert 8, 16, 32, and 64-bit unsigned integers to their 
 *  hexadecimal string representation for serialization.
 * ------------------------------------------------------------------------ */

/**
 * Serialize a 8-bit unsigned integer to a hexadecimal string.
 * @param value The value to serialize.
 * @return Hexadecimal string representing the value.
 */
char* fossil_sys_bitwise_serialize_u8(uint8_t value);

/**
 * Serialize a 16-bit unsigned integer to a hexadecimal string.
 * @param value The value to serialize.
 * @return Hexadecimal string representing the value.
 */
char* fossil_sys_bitwise_serialize_u16(uint16_t value);

/**
 * Serialize a 32-bit unsigned integer to a hexadecimal string.
 * @param value The value to serialize.
 * @return Hexadecimal string representing the value.
 */
char* fossil_sys_bitwise_serialize_u32(uint32_t value);

/**
 * Serialize a 64-bit unsigned integer to a hexadecimal string.
 * @param value The value to serialize.
 * @return Hexadecimal string representing the value.
 */
char* fossil_sys_bitwise_serialize_u64(uint64_t value);

#ifdef __cplusplus
}

#include <stdint.h>
#include <string>

namespace fossil {
namespace sys {

// ------------------------------------------------------------------------
//  8-bit Class Wrapper
// ------------------------------------------------------------------------

class BitwiseU8 {
public:
    static uint8_t and_op(uint8_t a, uint8_t b);
    static uint8_t or_op(uint8_t a, uint8_t b);
    static uint8_t xor_op(uint8_t a, uint8_t b);
    static uint8_t not_op(uint8_t a);

    static uint8_t lshift(uint8_t a, uint8_t shift);
    static uint8_t rshift(uint8_t a, uint8_t shift);

    static std::string serialize(uint8_t value);

    // Operator overloads
    uint8_t operator&(uint8_t other) const { return and_op(value, other); }
    uint8_t operator|(uint8_t other) const { return or_op(value, other); }
    uint8_t operator^(uint8_t other) const { return xor_op(value, other); }
    uint8_t operator~() const { return not_op(value); }
    uint8_t operator<<(uint8_t shift) const { return lshift(value, shift); }
    uint8_t operator>>(uint8_t shift) const { return rshift(value, shift); }

    explicit BitwiseU8(uint8_t val) : value(val) {}

private:
    uint8_t value;
};

// ------------------------------------------------------------------------
//  16-bit Class Wrapper
// ------------------------------------------------------------------------

class BitwiseU16 {
public:
    static uint16_t and_op(uint16_t a, uint16_t b);
    static uint16_t or_op(uint16_t a, uint16_t b);
    static uint16_t xor_op(uint16_t a, uint16_t b);
    static uint16_t not_op(uint16_t a);

    static uint16_t lshift(uint16_t a, uint8_t shift);
    static uint16_t rshift(uint16_t a, uint8_t shift);

    static std::string serialize(uint16_t value);

    // Operator overloads
    uint16_t operator&(uint16_t other) const { return and_op(value, other); }
    uint16_t operator|(uint16_t other) const { return or_op(value, other); }
    uint16_t operator^(uint16_t other) const { return xor_op(value, other); }
    uint16_t operator~() const { return not_op(value); }
    uint16_t operator<<(uint8_t shift) const { return lshift(value, shift); }
    uint16_t operator>>(uint8_t shift) const { return rshift(value, shift); }

    explicit BitwiseU16(uint16_t val) : value(val) {}

private:
    uint16_t value;
};

// ------------------------------------------------------------------------
//  32-bit Class Wrapper
// ------------------------------------------------------------------------

class BitwiseU32 {
public:
    static uint32_t and_op(uint32_t a, uint32_t b);
    static uint32_t or_op(uint32_t a, uint32_t b);
    static uint32_t xor_op(uint32_t a, uint32_t b);
    static uint32_t not_op(uint32_t a);

    static uint32_t lshift(uint32_t a, uint8_t shift);
    static uint32_t rshift(uint32_t a, uint8_t shift);

    static std::string serialize(uint32_t value);

    static bool test_bit(uint32_t value, uint8_t bit);
    static uint32_t set_bit(uint32_t value, uint8_t bit);
    static uint32_t clear_bit(uint32_t value, uint8_t bit);
    static uint32_t toggle_bit(uint32_t value, uint8_t bit);

    // Operator overloads
    uint32_t operator&(uint32_t other) const { return and_op(value, other); }
    uint32_t operator|(uint32_t other) const { return or_op(value, other); }
    uint32_t operator^(uint32_t other) const { return xor_op(value, other); }
    uint32_t operator~() const { return not_op(value); }
    uint32_t operator<<(uint8_t shift) const { return lshift(value, shift); }
    uint32_t operator>>(uint8_t shift) const { return rshift(value, shift); }

    explicit BitwiseU32(uint32_t val) : value(val) {}

private:
    uint32_t value;
};

// ------------------------------------------------------------------------
//  64-bit Class Wrapper
// ------------------------------------------------------------------------

class BitwiseU64 {
public:
    static uint64_t and_op(uint64_t a, uint64_t b);
    static uint64_t or_op(uint64_t a, uint64_t b);
    static uint64_t xor_op(uint64_t a, uint64_t b);
    static uint64_t not_op(uint64_t a);

    static uint64_t lshift(uint64_t a, uint8_t shift);
    static uint64_t rshift(uint64_t a, uint8_t shift);

    static std::string serialize(uint64_t value);

    // Operator overloads
    uint64_t operator&(uint64_t other) const { return and_op(value, other); }
    uint64_t operator|(uint64_t other) const { return or_op(value, other); }
    uint64_t operator^(uint64_t other) const { return xor_op(value, other); }
    uint64_t operator~() const { return not_op(value); }
    uint64_t operator<<(uint8_t shift) const { return lshift(value, shift); }
    uint64_t operator>>(uint8_t shift) const { return rshift(value, shift); }

    explicit BitwiseU64(uint64_t val) : value(val) {}

private:
    uint64_t value;
};

} // namespace sys
} // namespace fossil
#endif

#endif /* FOSSIL_SYS_BITWISE_H */
