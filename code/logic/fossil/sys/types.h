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
#ifndef FOSSIL_SYS_USER_H
#define FOSSIL_SYS_USER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

/* Ieger constants */
#define FOSSIL_SYS_TYPE_MAX_U8   0xFF
#define FOSSIL_SYS_TYPE_MIN_I8   (-128)
#define FOSSIL_SYS_TYPE_MAX_I8   127
#define FOSSIL_SYS_TYPE_MAX_U16  0xFFFF
#define FOSSIL_SYS_TYPE_MIN_I16  (-32768)
#define FOSSIL_SYS_TYPE_MAX_I16  32767
#define FOSSIL_SYS_TYPE_MAX_U32  0xFFFFFFFF
#define FOSSIL_SYS_TYPE_MIN_I32  (-2147483648)
#define FOSSIL_SYS_TYPE_MAX_I32  2147483647
#define FOSSIL_SYS_TYPE_MAX_U64  0xFFFFFFFFFFFFFFFF
#define FOSSIL_SYS_TYPE_MIN_I64  (-9223372036854775807LL)
#define FOSSIL_SYS_TYPE_MAX_I64  9223372036854775807LL

/* Type alignments (platform-specific) */
#define FOSSIL_SYS_TYPE_ALIGNOF_I8   __alignof(i8)
#define FOSSIL_SYS_TYPE_ALIGNOF_I16  __alignof(i16)
#define FOSSIL_SYS_TYPE_ALIGNOF_I32  __alignof(i32)
#define FOSSIL_SYS_TYPE_ALIGNOF_I64  __alignof(i64)
#define FOSSIL_SYS_TYPE_ALIGNOF_U8   __alignof(u8)
#define FOSSIL_SYS_TYPE_ALIGNOF_U16  __alignof(u16)
#define FOSSIL_SYS_TYPE_ALIGNOF_U32  __alignof(u32)
#define FOSSIL_SYS_TYPE_ALIGNOF_U64  __alignof(u64)

/* Type-Safe Macros */
#define FOSSIL_SYS_TYPE_CAST_TO_I8(value)  ((i8)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_U8(value)  ((u8)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_I16(value) ((i16)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_U16(value) ((u16)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_I32(value) ((i32)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_U32(value) ((u32)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_I64(value) ((i64)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_U64(value) ((u64)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_F32(value) ((f32)(value))
#define FOSSIL_SYS_TYPE_CAST_TO_F64(value) ((f64)(value))
#define FOSSIL_SYS_TYPE_IS_NEGATIVE(value) ((value) < 0)
#define FOSSIL_SYS_TYPE_IS_POSITIVE(value) ((value) > 0)
#define FOSSIL_SYS_TYPE_IS_ZERO(value)     ((value) == 0)
#define FOSSIL_SYS_TYPE_IS_NONZERO(value)  ((value) != 0)

#ifdef __cplusplus
extern "C" {
#endif

/* Signed and unsigned integer types */
#ifdef _MSC_VER
    /* Windows */
    typedef __int8  i8;   /* 8-bit signed integer */
    typedef __int16 i16;  /* 16-bit signed integer */
    typedef __int32 i32;  /* 32-bit signed integer */
    typedef __int64 i64;  /* 64-bit signed integer */

    typedef unsigned __int8  u8;   /* 8-bit unsigned integer */
    typedef unsigned __int16 u16;  /* 16-bit unsigned integer */
    typedef unsigned __int32 u32;  /* 32-bit unsigned integer */
    typedef unsigned __int64 u64;  /* 64-bit unsigned integer */
#else
    /* POSIX / Linux / macOS */
    typedef int8_t  i8;   /* 8-bit signed integer */
    typedef int16_t i16;  /* 16-bit signed integer */
    typedef int32_t i32;  /* 32-bit signed integer */
    typedef int64_t i64;  /* 64-bit signed integer */

    typedef uint8_t  u8;   /* 8-bit unsigned integer */
    typedef uint16_t u16;  /* 16-bit unsigned integer */
    typedef uint32_t u32;  /* 32-bit unsigned integer */
    typedef uint64_t u64;  /* 64-bit unsigned integer */
#endif

/* Floating point types (optional for precision) */
typedef float  f32;   /* 32-bit float */
typedef double f64;   /* 64-bit double */

#ifdef __cplusplus
}

#include <string>
#include <vector>

/**
 * C++ wrapper for the process management API.
 */
namespace fossil {

    /**
     * Process management utilities.
     */
    namespace sys {
        /**
         * Class representing an 8-bit signed integer.
         */
        class I8 {
        public:
            i8 value;

            I8(i8 val = 0) : value(val) {}

            // Operator overloading
            I8 operator+(const I8& other) const {
                return I8(value + other.value);
            }

            I8 operator-(const I8& other) const {
                return I8(value - other.value);
            }

            I8 operator*(const I8& other) const {
                return I8(value * other.value);
            }

            I8 operator/(const I8& other) const {
                return I8(value / other.value);
            }

            bool operator==(const I8& other) const {
                return value == other.value;
            }

            bool operator!=(const I8& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing an 8-bit unsigned integer.
         */
        class U8 {
        public:
            u8 value;

            U8(u8 val = 0) : value(val) {}

            // Operator overloading
            U8 operator+(const U8& other) const {
                return U8(value + other.value);
            }

            U8 operator-(const U8& other) const {
                return U8(value - other.value);
            }

            U8 operator*(const U8& other) const {
                return U8(value * other.value);
            }

            U8 operator/(const U8& other) const {
                return U8(value / other.value);
            }

            bool operator==(const U8& other) const {
                return value == other.value;
            }

            bool operator!=(const U8& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 16-bit signed integer.
         */
        class I16 {
        public:
            i16 value;

            I16(i16 val = 0) : value(val) {}

            // Operator overloading
            I16 operator+(const I16& other) const {
                return I16(value + other.value);
            }

            I16 operator-(const I16& other) const {
                return I16(value - other.value);
            }

            I16 operator*(const I16& other) const {
                return I16(value * other.value);
            }

            I16 operator/(const I16& other) const {
                return I16(value / other.value);
            }

            bool operator==(const I16& other) const {
                return value == other.value;
            }

            bool operator!=(const I16& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 16-bit unsigned integer.
         */
        class U16 {
        public:
            u16 value;

            U16(u16 val = 0) : value(val) {}

            // Operator overloading
            U16 operator+(const U16& other) const {
                return U16(value + other.value);
            }

            U16 operator-(const U16& other) const {
                return U16(value - other.value);
            }

            U16 operator*(const U16& other) const {
                return U16(value * other.value);
            }

            U16 operator/(const U16& other) const {
                return U16(value / other.value);
            }

            bool operator==(const U16& other) const {
                return value == other.value;
            }

            bool operator!=(const U16& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 32-bit signed integer.
         */
        class I32 {
        public:
            i32 value;

            I32(i32 val = 0) : value(val) {}

            // Operator overloading
            I32 operator+(const I32& other) const {
                return I32(value + other.value);
            }

            I32 operator-(const I32& other) const {
                return I32(value - other.value);
            }

            I32 operator*(const I32& other) const {
                return I32(value * other.value);
            }

            I32 operator/(const I32& other) const {
                return I32(value / other.value);
            }

            bool operator==(const I32& other) const {
                return value == other.value;
            }

            bool operator!=(const I32& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 32-bit unsigned integer.
         */
        class U32 {
        public:
            u32 value;

            U32(u32 val = 0) : value(val) {}

            // Operator overloading
            U32 operator+(const U32& other) const {
                return U32(value + other.value);
            }

            U32 operator-(const U32& other) const {
                return U32(value - other.value);
            }

            U32 operator*(const U32& other) const {
                return U32(value * other.value);
            }

            U32 operator/(const U32& other) const {
                return U32(value / other.value);
            }

            bool operator==(const U32& other) const {
                return value == other.value;
            }

            bool operator!=(const U32& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 64-bit signed integer.
         */
        class I64 {
        public:
            i64 value;

            I64(i64 val = 0) : value(val) {}

            // Operator overloading
            I64 operator+(const I64& other) const {
                return I64(value + other.value);
            }

            I64 operator-(const I64& other) const {
                return I64(value - other.value);
            }

            I64 operator*(const I64& other) const {
                return I64(value * other.value);
            }

            I64 operator/(const I64& other) const {
                return I64(value / other.value);
            }

            bool operator==(const I64& other) const {
                return value == other.value;
            }

            bool operator!=(const I64& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 64-bit unsigned integer.
         */
        class U64 {
        public:
            u64 value;

            U64(u64 val = 0) : value(val) {}

            // Operator overloading
            U64 operator+(const U64& other) const {
                return U64(value + other.value);
            }

            U64 operator-(const U64& other) const {
                return U64(value - other.value);
            }

            U64 operator*(const U64& other) const {
                return U64(value * other.value);
            }

            U64 operator/(const U64& other) const {
                return U64(value / other.value);
            }

            bool operator==(const U64& other) const {
                return value == other.value;
            }

            bool operator!=(const U64& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 32-bit floating point.
         */
        class F32 {
        public:
            f32 value;

            F32(f32 val = 0.0f) : value(val) {}

            // Operator overloading
            F32 operator+(const F32& other) const {
                return F32(value + other.value);
            }

            F32 operator-(const F32& other) const {
                return F32(value - other.value);
            }

            F32 operator*(const F32& other) const {
                return F32(value * other.value);
            }

            F32 operator/(const F32& other) const {
                return F32(value / other.value);
            }

            bool operator==(const F32& other) const {
                return value == other.value;
            }

            bool operator!=(const F32& other) const {
                return value != other.value;
            }
        };

        /**
         * Class representing a 64-bit floating point.
         */
        class F64 {
        public:
            f64 value;

            F64(f64 val = 0.0) : value(val) {}

            // Operator overloading
            F64 operator+(const F64& other) const {
                return F64(value + other.value);
            }

            F64 operator-(const F64& other) const {
                return F64(value - other.value);
            }

            F64 operator*(const F64& other) const {
                return F64(value * other.value);
            }

            F64 operator/(const F64& other) const {
                return F64(value / other.value);
            }

            bool operator==(const F64& other) const {
                return value == other.value;
            }

            bool operator!=(const F64& other) const {
                return value != other.value;
            }
        };

    } // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_PROCESS_H */
