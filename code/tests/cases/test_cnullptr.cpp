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
FOSSIL_TEST_SUITE(cpp_null_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_null_suite) {
    // Setup code if needed
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_null_suite) {
    // Cleanup if needed
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// ** Test cppnull and cppnullptr Definitions **
FOSSIL_TEST_CASE(cpp_test_cppnull_definition) {
#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
    ASSUME_ITS_EQUAL_PTR(cnull, nullptr);
    ASSUME_ITS_EQUAL_PTR(cnullptr, nullptr);
#else
    #if defined(_WIN64) || defined(_WIN32)
        ASSUME_ITS_EQUAL_PTR(cnull, 0);
        ASSUME_ITS_EQUAL_PTR(cnullptr, 0);
    #else
        ASSUME_ITS_EQUAL_PTR(cnull, (void *)(0));
        ASSUME_ITS_EQUAL_PTR(cnullptr, (void *)(0));
    #endif
#endif
}

// ** Test cppnull Assignment **
FOSSIL_TEST_CASE(cpp_test_cppnull_assignment) {
    void *ptr = cnull;
    ASSUME_ITS_EQUAL_PTR(ptr, cnull);
}

// ** Test cppnull Comparison **
FOSSIL_TEST_CASE(cpp_test_cppnull_comparison) {
    void *ptr = cnull;
    ASSUME_ITS_TRUE(ptr == cnull);
    ASSUME_ITS_FALSE(ptr != cnull);
}

// ** Test cppnullify Macro **
FOSSIL_TEST_CASE(cpp_test_cppnullify) {
    void *ptr = (void *)1;
    cnullify(ptr);
    ASSUME_ITS_EQUAL_PTR(ptr, cnull);
}

// ** Test cppnotnull Macro **
FOSSIL_TEST_CASE(cpp_test_cppnotnull) {
    void *ptr = (void *)1;
    ASSUME_ITS_TRUE(cnotnull(ptr));
    cnullify(ptr);
    ASSUME_ITS_FALSE(cnotnull(ptr));
}

// ** Test cppmaybe Macro **
FOSSIL_TEST_CASE(cpp_test_cppmaybe) {
    void *ptr = (void *)1;
    ASSUME_ITS_EQUAL_PTR(cmaybe(ptr, (void *)99), ptr);
    cnullify(ptr);
    ASSUME_ITS_EQUAL_PTR(cmaybe(ptr, (void *)99), (void *)99);
}

// ** Test Empty String Macros **
FOSSIL_TEST_CASE(cpp_test_cppempty_strings) {
    ASSUME_ITS_EQUAL_CSTR(cempty, "");
    ASSUME_ITS_EQUAL_WSTR(wempty, L"");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_null_tests) {
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppnull_definition);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppnull_assignment);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppnull_comparison);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppnullify);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppnotnull);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppmaybe);
    FOSSIL_TEST_ADD(cpp_null_suite, cpp_test_cppempty_strings);

    FOSSIL_TEST_REGISTER(cpp_null_suite);
}
