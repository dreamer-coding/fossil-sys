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

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Ensure null pointer definitions across C and C++ environments
#ifndef FOSSIL_CNULL

#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
/**
 * @brief Safe null pointer definition for modern C++ and C23.
 */
    #define cnull    nullptr
    #define cnullptr nullptr
#else
/**
 * @brief Platform-agnostic null pointer definition for older C standards.
 */
    #define cnull    ((void*)0)
    #define cnullptr ((void*)0)
#endif

#endif // FOSSIL_CNULL

/**
 * @brief Nullify a pointer safely.
 * 
 * Ensures that the pointer is explicitly set to `cnull`.
 */
#define cnullify(ptr) ((ptr) = cnull)

/**
 * @brief Check if a pointer is not null safely.
 *
 * Prevents misuse of potentially null pointers.
 */
#define cnotnull(ptr) ((ptr) != cnull)

/**
 * @brief Option-like behavior to return a pointer or a default value.
 *
 * Mimics Rust's `Option::unwrap_or()` safely.
 */
#define cunwrap_or(ptr, default_val) ((ptr) ? (ptr) : (default_val))

/**
 * @brief Unwraps a pointer safely or terminates if it's null.
 *
 * Mimics Rust's `Option::unwrap()`.
 */
#define cunwrap(ptr) ((cnotnull(ptr)) ? (ptr) : (fprintf(stderr, "Fatal error: called cunwrap() on a null pointer at %s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE), cnull))

/**
 * @brief Safely casts one pointer type to another with null-checking.
 *
 * Mimics Rust's `as` with additional null safety. If the input is `cnull`,
 * it returns `cnull` instead of attempting an invalid cast.
 *
 * @param type The target type for the cast.
 * @param ptr The pointer to cast.
 * @return The casted pointer or `cnull` if the input pointer is null.
 */
#ifdef __cplusplus
    #define csafe_cast(type, ptr) ((cnotnull(ptr)) ? (static_cast<type>(ptr)) : cnull)
#else
    #define csafe_cast(type, ptr) ((cnotnull(ptr)) ? ((type)(ptr)) : cnull)
#endif

/**
 * @brief Marks a variable as intentionally unused to prevent warnings.
 */
#ifndef cunused
    #if defined(__GNUC__) || defined(__clang__)
        #define cunused(x) (void)(x)
    #else
        #define cunused(x) /* no-op */
    #endif
#endif

/**
 * @brief Compiler hints for nullable and nonnull values.
 *
 * Provides stronger safety checks at compile time.
 */
#if defined(__clang__) || defined(__GNUC__)
    #define cnullable __attribute__((nullable))
    #define cnonnull  __attribute__((nonnull))
#elif defined(_MSC_VER)
    #define cnullable _Null_terminated_
    #define cnonnull  _In_
#else
    #define cnullable
    #define cnonnull
#endif

/**
 * @brief Compiler branch prediction hints for likely and unlikely conditions.
 *
 * Helps the compiler optimize branches based on expected conditions.
 */
#if defined(__GNUC__) || defined(__clang__)
    #define clikely(x)   __builtin_expect(!!(x), 1)
    #define cunlikely(x) __builtin_expect(!!(x), 0)
#else
    #define clikely(x)   (x)
    #define cunlikely(x) (x)
#endif

// Safe string and character constants

/**
 * @brief Null terminators for C and wide strings.
 */
#define cterm '\0'
#define wterm L'\0'

/**
 * @brief Newline constants for C and wide strings.
 */
#define cnewline '\n'
#define wnewline L'\n'

/**
 * @brief Empty string constants for C and wide strings.
 */
#define cempty ""
#define wempty L""

/**
 * @brief Ensure safe cleanup by nullifying pointers after use.
 *
 * Mimics Rust's memory safety using explicit pointer management.
 */
#define cdrop(ptr) do { cnullify(ptr); } while (0)

/**
 * @brief Panic behavior for immediate program termination with error message.
 * 
 * This macro causes the program to immediately terminate with an error message,
 * similar to Rust's `panic!()` functionality.
 *
 * @param msg The message to display when panicking.
 */
#define cpanic(msg) (fprintf(stderr, "Panic: %s\n", msg), exit(EXIT_FAILURE))

/**
 * @brief Mimics Rust's Option type.
 * 
 * The `coptional` macro represents a nullable pointer that can be either `cnull` or a valid pointer.
 * It can be used to model optional values that may or may not be present.
 */
#define coptional(ptr) ((ptr) ? (ptr) : cnull)

/**
 * @brief `COption` structure to mimic Rust's `Option<T>`.
 * 
 * This structure allows representation of an optional value where it can either contain a value
 * (`Some`) or be `None` (`cnull`).
 */
typedef struct {
    void* value;  // The value held by the Option (could be a pointer to any type)
    int is_some;  // Flag indicating whether the Option is `Some` (1) or `None` (0)
} COption;

/**
 * @brief Creates an `Option` with a value (Some).
 *
 * @param val The value to wrap in the Option.
 * @return The created `COption` containing the value.
 */
#ifdef __cplusplus
    #define csome(val) (COption{val, 1})
#else
    #define csome(val) ((COption){(void*)(val), 1})
#endif

/**
 * @brief Creates an empty `Option` (None).
 *
 * @return An `Option` representing `None`.
 */
#ifdef __cplusplus
    #define cnone() (COption{cnull, 0})
#else
    #define cnone() ((COption){cnull, 0})
#endif

/**
 * @brief Unwraps the `COption`. If it's `Some`, return the value; if it's `None`, panic.
 *
 * Mimics Rust's `Option::unwrap()`.
 *
 * @param opt The `COption` to unwrap.
 * @return The value inside the `Option`.
 */
#define cunwrap_option(opt) ((opt).is_some ? (opt).value : (fprintf(stderr, "Panic: Unwrapped a None value at %s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE), cnull))

/**
 * @brief Returns the value inside the `COption` or a default value if it's `None`.
 *
 * Mimics Rust's `Option::unwrap_or()`.
 *
 * @param opt The `COption` to unwrap.
 * @param default_val The default value to return if the `COption` is `None`.
 * @return The value inside the `Option`, or the default value if `None`.
 */
#define cunwrap_or_option(opt, default_val) ((opt).is_some ? (opt).value : (default_val))

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SYS_CNULLPTR_H
