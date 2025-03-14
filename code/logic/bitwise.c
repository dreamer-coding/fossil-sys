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
#include "fossil/sys/bitwise.h"
#include <stdlib.h>
#include <stdio.h>

/* ============================================================================
 *  Basic Bitwise Operations
 * ============================================================================ */

uint8_t fossil_sys_bitwise_and_u8(uint8_t a, uint8_t b) { return a & b; }
uint16_t fossil_sys_bitwise_and_u16(uint16_t a, uint16_t b) { return a & b; }
uint32_t fossil_sys_bitwise_and_u32(uint32_t a, uint32_t b) { return a & b; }
uint64_t fossil_sys_bitwise_and_u64(uint64_t a, uint64_t b) { return a & b; }

uint8_t fossil_sys_bitwise_or_u8(uint8_t a, uint8_t b) { return a | b; }
uint16_t fossil_sys_bitwise_or_u16(uint16_t a, uint16_t b) { return a | b; }
uint32_t fossil_sys_bitwise_or_u32(uint32_t a, uint32_t b) { return a | b; }
uint64_t fossil_sys_bitwise_or_u64(uint64_t a, uint64_t b) { return a | b; }

uint8_t fossil_sys_bitwise_xor_u8(uint8_t a, uint8_t b) { return a ^ b; }
uint16_t fossil_sys_bitwise_xor_u16(uint16_t a, uint16_t b) { return a ^ b; }
uint32_t fossil_sys_bitwise_xor_u32(uint32_t a, uint32_t b) { return a ^ b; }
uint64_t fossil_sys_bitwise_xor_u64(uint64_t a, uint64_t b) { return a ^ b; }

uint8_t fossil_sys_bitwise_not_u8(uint8_t a) { return ~a; }
uint16_t fossil_sys_bitwise_not_u16(uint16_t a) { return ~a; }
uint32_t fossil_sys_bitwise_not_u32(uint32_t a) { return ~a; }
uint64_t fossil_sys_bitwise_not_u64(uint64_t a) { return ~a; }

/* ============================================================================
 *  Bitwise Shift Operations
 * ============================================================================ */

uint8_t fossil_sys_bitwise_lshift_u8(uint8_t a, uint8_t shift) { return a << shift; }
uint16_t fossil_sys_bitwise_lshift_u16(uint16_t a, uint8_t shift) { return a << shift; }
uint32_t fossil_sys_bitwise_lshift_u32(uint32_t a, uint8_t shift) { return a << shift; }
uint64_t fossil_sys_bitwise_lshift_u64(uint64_t a, uint8_t shift) { return a << shift; }

uint8_t fossil_sys_bitwise_rshift_u8(uint8_t a, uint8_t shift) { return a >> shift; }
uint16_t fossil_sys_bitwise_rshift_u16(uint16_t a, uint8_t shift) { return a >> shift; }
uint32_t fossil_sys_bitwise_rshift_u32(uint32_t a, uint8_t shift) { return a >> shift; }
uint64_t fossil_sys_bitwise_rshift_u64(uint64_t a, uint8_t shift) { return a >> shift; }

/* ============================================================================
 *  Bit Manipulation Functions
 * ============================================================================ */

bool fossil_sys_bitwise_test_u32(uint32_t value, uint8_t bit) { return (value & (1U << bit)) != 0; }
uint32_t fossil_sys_bitwise_set_u32(uint32_t value, uint8_t bit) { return value | (1U << bit); }
uint32_t fossil_sys_bitwise_clear_u32(uint32_t value, uint8_t bit) { return value & ~(1U << bit); }
uint32_t fossil_sys_bitwise_toggle_u32(uint32_t value, uint8_t bit) { return value ^ (1U << bit); }

/* ============================================================================
 *  Serialization Functions (Hex String Representation)
 * ============================================================================ */

char* fossil_sys_bitwise_serialize_u8(uint8_t value) {
    char* buffer = (char*)malloc(3); 
    if (buffer) sprintf(buffer, "%02X", value);
    return buffer;
}

char* fossil_sys_bitwise_serialize_u16(uint16_t value) {
    char* buffer = (char*)malloc(5); 
    if (buffer) sprintf(buffer, "%04X", value);
    return buffer;
}

char* fossil_sys_bitwise_serialize_u32(uint32_t value) {
    char* buffer = (char*)malloc(9); 
    if (buffer) sprintf(buffer, "%08X", value);
    return buffer;
}

char* fossil_sys_bitwise_serialize_u64(uint64_t value) {
    char* buffer = (char*)malloc(17); 
    if (buffer) sprintf(buffer, "%016llX", (unsigned long long)value);
    return buffer;
}
