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

// ============================================================================
/*                             UNSIGNED FUNCTIONS
 * ============================================================================ */

uint8_t fossil_sys_bitwise_count_ones_u8(uint8_t value) {
    uint8_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

uint16_t fossil_sys_bitwise_count_ones_u16(uint16_t value) {
    uint16_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

uint32_t fossil_sys_bitwise_count_ones_u32(uint32_t value) {
    uint32_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

uint64_t fossil_sys_bitwise_count_ones_u64(uint64_t value) {
    uint64_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

uint8_t fossil_sys_bitwise_reverse_u8(uint8_t value) {
    uint8_t reversed = 0;
    for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

uint16_t fossil_sys_bitwise_reverse_u16(uint16_t value) {
    uint16_t reversed = 0;
    for (int i = 0; i < 16; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

uint32_t fossil_sys_bitwise_reverse_u32(uint32_t value) {
    uint32_t reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

uint64_t fossil_sys_bitwise_reverse_u64(uint64_t value) {
    uint64_t reversed = 0;
    for (int i = 0; i < 64; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

uint8_t fossil_sys_bitwise_rotate_left_u8(uint8_t value, uint8_t shift) {
    return (value << shift) | (value >> (8 - shift));
}

uint16_t fossil_sys_bitwise_rotate_left_u16(uint16_t value, uint8_t shift) {
    return (value << shift) | (value >> (16 - shift));
}

uint32_t fossil_sys_bitwise_rotate_left_u32(uint32_t value, uint8_t shift) {
    return (value << shift) | (value >> (32 - shift));
}

uint64_t fossil_sys_bitwise_rotate_left_u64(uint64_t value, uint8_t shift) {
    return (value << shift) | (value >> (64 - shift));
}

uint8_t fossil_sys_bitwise_rotate_right_u8(uint8_t value, uint8_t shift) {
    return (value >> shift) | (value << (8 - shift));
}

uint16_t fossil_sys_bitwise_rotate_right_u16(uint16_t value, uint8_t shift) {
    return (value >> shift) | (value << (16 - shift));
}

uint32_t fossil_sys_bitwise_rotate_right_u32(uint32_t value, uint8_t shift) {
    return (value >> shift) | (value << (32 - shift));
}

uint64_t fossil_sys_bitwise_rotate_right_u64(uint64_t value, uint8_t shift) {
    return (value >> shift) | (value << (64 - shift));
}

// ============================================================================
/*                             SIGNED FUNCTIONS
 * ============================================================================ */

int8_t fossil_sys_bitwise_count_ones_i8(int8_t value) {
    int8_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int16_t fossil_sys_bitwise_count_ones_i16(int16_t value) {
    int16_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int32_t fossil_sys_bitwise_count_ones_i32(int32_t value) {
    int32_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int64_t fossil_sys_bitwise_count_ones_i64(int64_t value) {
    int64_t count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int8_t fossil_sys_bitwise_reverse_i8(int8_t value) {
    int8_t reversed = 0;
    for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

int16_t fossil_sys_bitwise_reverse_i16(int16_t value) {
    int16_t reversed = 0;
    for (int i = 0; i < 16; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

int32_t fossil_sys_bitwise_reverse_i32(int32_t value) {
    int32_t reversed = 0;
    for (int i = 0; i < 32; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

int64_t fossil_sys_bitwise_reverse_i64(int64_t value) {
    int64_t reversed = 0;
    for (int i = 0; i < 64; i++) {
        reversed = (reversed << 1) | (value & 1);
        value >>= 1;
    }
    return reversed;
}

int8_t fossil_sys_bitwise_rotate_left_i8(int8_t value, int8_t shift) {
    return (value << shift) | (value >> (8 - shift));
}

int16_t fossil_sys_bitwise_rotate_left_i16(int16_t value, int8_t shift) {
    return (value << shift) | (value >> (16 - shift));
}

int32_t fossil_sys_bitwise_rotate_left_i32(int32_t value, int8_t shift) {
    return (value << shift) | (value >> (32 - shift));
}

int64_t fossil_sys_bitwise_rotate_left_i64(int64_t value, int8_t shift) {
    return (value << shift) | (value >> (64 - shift));
}

int8_t fossil_sys_bitwise_rotate_right_i8(int8_t value, int8_t shift) {
    return (value >> shift) | (value << (8 - shift));
}

int16_t fossil_sys_bitwise_rotate_right_i16(int16_t value, int8_t shift) {
    return (value >> shift) | (value << (16 - shift));
}

int32_t fossil_sys_bitwise_rotate_right_i32(int32_t value, int8_t shift) {
    return (value >> shift) | (value << (32 - shift));
}

int64_t fossil_sys_bitwise_rotate_right_i64(int64_t value, int8_t shift) {
    return (value >> shift) | (value << (64 - shift));
}
