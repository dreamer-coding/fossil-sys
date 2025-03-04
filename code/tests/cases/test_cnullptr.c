/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * performance, cross-platform applications and libraries. The code contained
 * This file is part of the Fossil Logic project, which aims to develop high-
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/test/framework.h>

#include "fossil/sys/framework.h"

#ifndef cnull
#error "cnull is not defined."
#endif

#ifndef cnullptr
#error "cnullptr is not defined."
#endif

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(c_null_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_null_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_null_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Test cases for cnull
FOSSIL_TEST_CASE(c_test_cnull_definition) {
    // Test cnull definition
#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
    // C++11 or later, C23 or later
    ASSUME_ITS_EQUAL_PTR(cnull, nullptr);
    ASSUME_ITS_EQUAL_PTR(cnullptr, nullptr);
#else
    // Pre-C++11 or C23
    #if defined(_WIN64) || defined(_WIN32)
    // Windows
        ASSUME_ITS_EQUAL_PTR(cnull, 0);
        ASSUME_ITS_EQUAL_PTR(cnullptr, 0);
    #else
    // POSIX, macOS, and embedded systems
        ASSUME_ITS_EQUAL_PTR(cnull, (void *)(0));
        ASSUME_ITS_EQUAL_PTR(cnullptr, (void *)(0));
    #endif
#endif
}


// ** Test cnull Assignment **
FOSSIL_TEST_CASE(c_test_cnull_assignment) {
    void *ptr = cnull;
    ASSUME_ITS_EQUAL_PTR(ptr, cnull);
}

// ** Test cnull Comparison **
FOSSIL_TEST_CASE(c_test_cnull_comparison) {
    void *ptr = cnull;
    ASSUME_ITS_TRUE(ptr == cnull);
    ASSUME_ITS_FALSE(ptr != cnull);
}

// ** Test cnullify Macro **
FOSSIL_TEST_CASE(c_test_cnullify) {
    void *ptr = (void *)1;
    cnullify(ptr);
    ASSUME_ITS_EQUAL_PTR(ptr, cnull);
}

// ** Test cnotnull Macro **
FOSSIL_TEST_CASE(c_test_cnotnull) {
    void *ptr = (void *)1;
    ASSUME_ITS_TRUE(cnotnull(ptr));
    cnullify(ptr);
    ASSUME_ITS_FALSE(cnotnull(ptr));
}

// ** Test cmaybe Macro **
FOSSIL_TEST_CASE(c_test_cmaybe) {
    void *ptr = (void *)1;
    ASSUME_ITS_EQUAL_PTR(cmaybe(ptr, (void *)99), ptr);
    cnullify(ptr);
    ASSUME_ITS_EQUAL_PTR(cmaybe(ptr, (void *)99), (void *)99);
}

// ** Test String Termination Constants **
FOSSIL_TEST_CASE(c_test_string_terminators) {
    ASSUME_ITS_EQUAL_CCHAR(cterm, '\0');
    ASSUME_ITS_EQUAL_WCHAR(wterm, L'\0');
    ASSUME_ITS_EQUAL_CCHAR(cterminator, '\0');
    ASSUME_ITS_EQUAL_WCHAR(wterminator, L'\0');
}

// ** Test Newline Constants **
FOSSIL_TEST_CASE(c_test_newlines) {
    ASSUME_ITS_EQUAL_CCHAR(cnewline, '\n');
    ASSUME_ITS_EQUAL_WCHAR(wnewline, L'\n');
}

// ** Test Empty String Macros **
FOSSIL_TEST_CASE(c_test_empty_strings) {
    ASSUME_ITS_EQUAL_CSTR(cempty, "");
    ASSUME_ITS_EQUAL_WSTR(wempty, L"");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_null_tests) {
    FOSSIL_TEST_ADD(c_null_suite, c_test_cnull_definition);
    FOSSIL_TEST_ADD(c_null_suite, c_test_cnull_assignment);
    FOSSIL_TEST_ADD(c_null_suite, c_test_cnull_comparison);
    FOSSIL_TEST_ADD(c_null_suite, c_test_cnullify);
    FOSSIL_TEST_ADD(c_null_suite, c_test_cnotnull);
    FOSSIL_TEST_ADD(c_null_suite, c_test_cmaybe);
    FOSSIL_TEST_ADD(c_null_suite, c_test_string_terminators);
    FOSSIL_TEST_ADD(c_null_suite, c_test_newlines);
    FOSSIL_TEST_ADD(c_null_suite, c_test_empty_strings);

    FOSSIL_TEST_REGISTER(c_null_suite);
}
