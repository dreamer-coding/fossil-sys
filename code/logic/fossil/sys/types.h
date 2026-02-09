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
#ifndef FOSSIL_SYS_TYPE_H
#define FOSSIL_SYS_TYPE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

/* ======================================================
 * Core integer limits (portable, no UB)
 * ====================================================== */
#define FOSSIL_SYS_TYPE_MIN_I8    INT8_MIN
#define FOSSIL_SYS_TYPE_MAX_I8    INT8_MAX
#define FOSSIL_SYS_TYPE_MAX_U8    UINT8_MAX

#define FOSSIL_SYS_TYPE_MIN_I16   INT16_MIN
#define FOSSIL_SYS_TYPE_MAX_I16   INT16_MAX
#define FOSSIL_SYS_TYPE_MAX_U16   UINT16_MAX

#define FOSSIL_SYS_TYPE_MIN_I32   INT32_MIN
#define FOSSIL_SYS_TYPE_MAX_I32   INT32_MAX
#define FOSSIL_SYS_TYPE_MAX_U32   UINT32_MAX

#define FOSSIL_SYS_TYPE_MIN_I64   INT64_MIN
#define FOSSIL_SYS_TYPE_MAX_I64   INT64_MAX
#define FOSSIL_SYS_TYPE_MAX_U64   UINT64_MAX

/* ======================================================
 * Alignment helpers
 * ====================================================== */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define FOSSIL_SYS_TYPE_ALIGNOF(type) _Alignof(type)
#elif defined(__GNUC__) || defined(__clang__)
    #define FOSSIL_SYS_TYPE_ALIGNOF(type) __alignof__(type)
#elif defined(_MSC_VER)
    #define FOSSIL_SYS_TYPE_ALIGNOF(type) __alignof(type)
#else
    #define FOSSIL_SYS_TYPE_ALIGNOF(type) sizeof(type)
#endif

/* ======================================================
 * Type-safe cast & value helpers
 * ====================================================== */
#define FOSSIL_SYS_TYPE_CAST_TO_I8(v)   ((i8)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_U8(v)   ((u8)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_I16(v)  ((i16)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_U16(v)  ((u16)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_I32(v)  ((i32)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_U32(v)  ((u32)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_I64(v)  ((i64)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_U64(v)  ((u64)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_F32(v)  ((f32)(v))
#define FOSSIL_SYS_TYPE_CAST_TO_F64(v)  ((f64)(v))

#define FOSSIL_SYS_TYPE_IS_NEGATIVE(v) ((v) < 0)
#define FOSSIL_SYS_TYPE_IS_POSITIVE(v) ((v) > 0)
#define FOSSIL_SYS_TYPE_IS_ZERO(v)     ((v) == 0)
#define FOSSIL_SYS_TYPE_IS_NONZERO(v)  ((v) != 0)

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================
 * Fixed-width integer types
 * ====================================================== */
#ifdef _MSC_VER
    typedef __int8   i8;
    typedef __int16  i16;
    typedef __int32  i32;
    typedef __int64  i64;

    typedef unsigned __int8   u8;
    typedef unsigned __int16  u16;
    typedef unsigned __int32  u32;
    typedef unsigned __int64  u64;
#else
    typedef int8_t   i8;
    typedef int16_t  i16;
    typedef int32_t  i32;
    typedef int64_t  i64;

    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
#endif

/* ======================================================
 * Pointer-sized & size types
 * ====================================================== */
typedef size_t    usize;
typedef ptrdiff_t isize;
typedef uintptr_t uptr;
typedef intptr_t  iptr;

/* ======================================================
 * Byte / bit helpers
 * ====================================================== */
typedef u8 byte;

#define FOSSIL_SYS_TYPE_BITS_PER_BYTE 8
#define FOSSIL_SYS_TYPE_BITS(type) (sizeof(type) * FOSSIL_SYS_TYPE_BITS_PER_BYTE)

/* ======================================================
 * Numeric representation aliases
 * ====================================================== */
typedef u8  h8;
typedef u16 h16;
typedef u32 h32;
typedef u64 h64;

typedef u8  b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

typedef u8  o8;
typedef u16 o16;
typedef u32 o32;
typedef u64 o64;

/* ======================================================
 * Floating-point types
 * ====================================================== */
typedef float  f32;
typedef double f64;

/* ======================================================
 * Endianness detection
 * ====================================================== */
#define FOSSIL_LITTLE_ENDIAN 1234
#define FOSSIL_BIG_ENDIAN    4321

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define FOSSIL_SYS_ENDIAN FOSSIL_BIG_ENDIAN
#else
    #define FOSSIL_SYS_ENDIAN FOSSIL_LITTLE_ENDIAN
#endif

/* ======================================================
 * Static assertions (ABI sanity)
 * ====================================================== */
#define FOSSIL_STATIC_ASSERT(cond, name) \
    typedef char fossil_static_assert_##name[(cond) ? 1 : -1]

FOSSIL_STATIC_ASSERT(sizeof(i8)  == 1, i8_size);
FOSSIL_STATIC_ASSERT(sizeof(i16) == 2, i16_size);
FOSSIL_STATIC_ASSERT(sizeof(i32) == 4, i32_size);
FOSSIL_STATIC_ASSERT(sizeof(i64) == 8, i64_size);

#ifdef __cplusplus
}

namespace fossil {

    namespace sys {
    
        /* Generic numeric wrapper (reduces duplication) */
        template<typename T>
        class Num {
        public:
            T value;
        
            constexpr Num(T v = 0) noexcept : value(v) {}
            constexpr operator T() const noexcept { return value; }
        
            constexpr Num operator+(Num o) const noexcept { return value + o.value; }
            constexpr Num operator-(Num o) const noexcept { return value - o.value; }
            constexpr Num operator*(Num o) const noexcept { return value * o.value; }
            constexpr Num operator/(Num o) const noexcept { return value / o.value; }
        
            constexpr bool operator==(Num o) const noexcept { return value == o.value; }
            constexpr bool operator!=(Num o) const noexcept { return value != o.value; }
        };
        
        using I8  = Num<i8>;
        using U8  = Num<u8>;
        using I16 = Num<i16>;
        using U16 = Num<u16>;
        using I32 = Num<i32>;
        using U32 = Num<u32>;
        using I64 = Num<i64>;
        using U64 = Num<u64>;
        using F32 = Num<f32>;
        using F64 = Num<f64>;
    
    } /* namespace sys */

} /* namespace fossil */

#endif

#endif /* FOSSIL_SYS_TYPE_H */
