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
#ifndef FOSSIL_SYS_CNULLPTR_H
#define FOSSIL_SYS_CNULLPTR_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Ensure null pointer is defined for compatibility with C11, C23, and C++ standards
#ifndef FOSSIL_CNULL

#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
/**
 * @brief Definition for cnull pointers in C++11 and later or C23 and later.
 *
 * In C++11 or later, `cnullptr` is a keyword representing a cnull pointer constant.
 * In C23 or later, `_cnullptr` is recognized in the same way as C++.
 */
    #define cnull    nullptr
    #define cnullptr nullptr
#else
    #if defined(_WIN64) || defined(_WIN32)
/**
 * @brief Definition for cnull pointers on Windows systems.
 *
 * For Windows (both 32-bit and 64-bit), we define `cnull` and `cnullptr` as 0.
 */
    #define cnull    0
    #define cnullptr 0
#else
/**
 * @brief Definition for cnull pointers on POSIX systems, macOS, and embedded systems.
 *
 * For POSIX, macOS, and embedded systems, we define `cnull` and `cnullptr` as a void pointer to 0.
 */
    #define cnull    (void *)(0)
    #define cnullptr (void *)(0)
    #endif
#endif
#endif

/**
 * @brief Macro to nullify a pointer.
 *
 * This macro sets a pointer to `cnull` (`nullptr` in C++ or platform-appropriate null in C).
 * It ensures that the pointer is safely assigned a null value.
 *
 * @param ptr The pointer to be nullified.
 */
#define cnullify(ptr) ((ptr) = cnull)

/**
 * @brief Checks if a pointer is not null.
 *
 * A macro that explicitly verifies if a pointer is not null before using it.
 *
 * @param ptr The pointer to check.
 * @return 1 if not null, 0 otherwise.
 */
#define cnotnull(ptr) ((ptr) != cnull)

/**
 * @brief Represents an optional (nullable) value.
 *
 * If the value is null, it returns a default value instead.
 *
 * @param ptr The pointer to check.
 * @param default_val The default value to return if `ptr` is null.
 * @return `ptr` if not null, otherwise `default_val`.
 */
#define cmaybe(ptr, default_val) ((ptr) ? (ptr) : (default_val))

// Termination values for regular and wide strings

/**
 * @brief Null-terminated character for C strings.
 *
 * This is used to mark the end of a C string (regular strings).
 * It is commonly used to indicate the end of an array of characters in C.
 * It is equivalent to the null character `'\0'`.
 */
#define cterminator '\0'

/**
 * @brief Null-terminated wide-character for wide strings.
 *
 * This is used to mark the end of a wide-character string (`wchar_t` arrays).
 * It is equivalent to the wide null character `L'\0'`.
 */
#define wterminator L'\0'

/**
 * @brief Null-terminated character for C strings.
 *
 * This is used as a constant for the null character in C strings, typically to represent the end of a string.
 */
#define cterm '\0'

/**
 * @brief Null-terminated wide-character for wide strings.
 *
 * This is used as a constant for the null character in wide strings (`wchar_t` arrays), typically to represent the end of a wide string.
 */
#define wterm L'\0'

// Newline constants for regular and wide strings

/**
 * @brief Defines the newline character for C.
 *
 * This is used in C and C++ environments for regular strings to denote a newline.
 */
#define cnewline    '\n'

/**
 * @brief Defines the newline character for wide strings in C and C++.
 *
 * This is used for wide-character strings (`wchar_t`) to denote a newline.
 */
#define wnewline    L'\n'

/**
 * @brief Defines an empty C string.
 *
 * This represents an empty string (`""`) for use in C and C++ code.
 */
#define cempty      ""

/**
 * @brief Defines an empty wide-character string.
 *
 * This represents an empty wide string (`L""`) for use in C and C++ code.
 */
#define wempty      L""

/**
 * @brief Type-safe compiler attributes for null and nullable types.
 *
 * - `cnull` and `cnullptr` handle null pointers across platforms.
 * - The constants `cterminator`, `wterminator`, `cterm`, `wterm` are used to represent the null terminators
 *   for regular and wide-character strings.
 * - `cnewline` and `wnewline` are used to represent newline characters for regular and wide strings.
 * - `cempty` and `wempty` represent empty strings for regular and wide-character strings.
 *
 * These definitions ensure proper handling of string terminations and special characters across platforms.
 * Compiler-specific attributes:
 * - **GCC/Clang**: The use of `nullptr` for null pointers in C++ and null terminators for strings.
 * - **MSVC**: MSVC compilers do not natively support `nullptr` but handle `cnull` as 0.
 */

#ifdef __cplusplus
}
#endif

#endif
