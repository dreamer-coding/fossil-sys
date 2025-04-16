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

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(cpp_path_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_path_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_path_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// need to add char assume ASAP

// // ** Test fossil::sys::Path::separator Function **
// FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_separator_class) {
//     std::string sep = fossil::sys::Path::separator();
// #if defined(_WIN32)
//     ASSUME_ITS_EQUAL_CSTR(sep, "\\");
// #else
//     ASSUME_ITS_EQUAL_CSTR(sep, "/");
// #endif
// }

// ** Test fossil::sys::Path::envvar Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_envvar_class) {
    std::string envvar = fossil::sys::Path::envvar();
#if defined(_WIN32)
    ASSUME_ITS_EQUAL_CSTR(envvar, "Path");
#else
    ASSUME_ITS_EQUAL_CSTR(envvar.c_str(), "PATH");
#endif
}

// ** Test fossil::sys::Path::join Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_join_class) {
    std::string joined = fossil::sys::Path::join("home", "user");
    ASSUME_ITS_EQUAL_CSTR(joined.c_str(), "home/user");

    joined = fossil::sys::Path::join("home/", "user");
    ASSUME_ITS_EQUAL_CSTR(joined.c_str(), "home/user");
}

// ** Test fossil::sys::Path::joinv Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_joinv_class) {
    const char *paths[] = {"home", "user", "documents"};
    std::string joined = fossil::sys::Path::joinv(3, paths);
    ASSUME_ITS_EQUAL_CSTR(joined.c_str(), "home/user/documents");
}

// ** Test fossil::sys::Path::normalize Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_normalize_class) {
    std::string normalized = fossil::sys::Path::normalize("home//user///documents");
    ASSUME_ITS_EQUAL_CSTR(normalized.c_str(), "home/user/documents");
}

// ** Test fossil::sys::Path::basename Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_basename_class) {
    std::string basename = fossil::sys::Path::basename("home/user/documents/file.txt");
    ASSUME_ITS_EQUAL_CSTR(basename.c_str(), "file.txt");
}

// ** Test fossil::sys::Path::dirname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_dirname_class) {
    std::string dirname = fossil::sys::Path::dirname("home/user/documents/file.txt");
    ASSUME_ITS_EQUAL_CSTR(dirname.c_str(), "home/user/documents");
}

// ** Test fossil::sys::Path::extname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_extname_class) {
    std::string extname = fossil::sys::Path::extname("file.txt");
    ASSUME_ITS_EQUAL_CSTR(extname.c_str(), ".txt");
}

// ** Test fossil::sys::Path::strip_ext Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_strip_ext_class) {
    std::string stripped = fossil::sys::Path::strip_ext("file.txt");
    ASSUME_ITS_EQUAL_CSTR(stripped.c_str(), "file");
}

// ** Test fossil::sys::Path::isabs Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isabs_class) {
#if defined(_WIN32)
    ASSUME_ITS_TRUE(fossil::sys::Path::isabs("C:\\Windows"));
    ASSUME_ITS_FALSE(fossil::sys::Path::isabs("Windows\\System32"));
#else
    ASSUME_ITS_TRUE(fossil::sys::Path::isabs("/usr/bin"));
    ASSUME_ITS_FALSE(fossil::sys::Path::isabs("usr/bin"));
#endif
}

// ** Test fossil::sys::Path::exists Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_exists_class) {
    ASSUME_ITS_TRUE(fossil::sys::Path::exists("/"));
    ASSUME_ITS_FALSE(fossil::sys::Path::exists("/nonexistent_path"));
}

// ** Test fossil::sys::Path::isdir Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isdir_class) {
    ASSUME_ITS_TRUE(fossil::sys::Path::isdir("/"));
    ASSUME_ITS_FALSE(fossil::sys::Path::isdir("/nonexistent_path"));
}

// ** Test fossil::sys::Path::isfile Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isfile_class) {
    ASSUME_ITS_FALSE(fossil::sys::Path::isfile("/"));
    ASSUME_ITS_FALSE(fossil::sys::Path::isfile("/nonexistent_file"));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_path_tests) {
    // FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_separator_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_envvar_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_join_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_joinv_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_normalize_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_basename_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_dirname_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_extname_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_strip_ext_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_isabs_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_exists_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_isdir_class);
    FOSSIL_TEST_ADD(cpp_path_suite, cpp_test_fossil_sys_path_isfile_class);

    FOSSIL_TEST_REGISTER(cpp_path_suite);
}
