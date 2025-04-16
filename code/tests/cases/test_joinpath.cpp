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
FOSSIL_TEST_SUITE(cpp_bitwise_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_bitwise_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_bitwise_suite) {
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

// ** Test fossil_sys_path_separator Function **
// FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_separator) {
//     char sep = fossil_sys_path_separator();
// #if defined(_WIN32)
//     ASSUME_ITS_EQUAL_CSTR(sep, '\\');
// #else
//     ASSUME_ITS_EQUAL_CS(sep, '/');
// #endif
// }

// ** Test fossil_sys_path_envvar Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_envvar) {
    const char *envvar = fossil_sys_path_envvar();
#if defined(_WIN32)
    ASSUME_ITS_EQUAL_CSTR(envvar, "Path");
#else
    ASSUME_ITS_EQUAL_CSTR(envvar, "PATH");
#endif
}

// ** Test fossil_sys_path_join Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_join) {
    char *joined = fossil_sys_path_join(const_cast<char *>("home"), const_cast<char *>("user"));
    ASSUME_NOT_CNULL(joined);
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user");
    free(joined);

    joined = fossil_sys_path_join(const_cast<char *>("home/"), const_cast<char *>("user"));
    ASSUME_NOT_CNULL(joined);
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user");
    free(joined);
}

// ** Test fossil_sys_path_joinv Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_joinv) {
    const char *paths[] = {const_cast<char *>("home"), const_cast<char *>("user"), const_cast<char *>("documents")};
    char *joined = fossil_sys_path_joinv(3, paths);
    ASSUME_NOT_CNULL(joined);
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user/documents");
    free(joined);
}

// ** Test fossil_sys_path_normalize Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_normalize) {
    char *normalized = fossil_sys_path_normalize(const_cast<char *>("home//user///documents"));
    ASSUME_NOT_CNULL(normalized);
    ASSUME_ITS_EQUAL_CSTR(normalized, "home/user/documents");
    free(normalized);
}

// ** Test fossil_sys_path_basename Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_basename) {
    char *basename = fossil_sys_path_basename(const_cast<char *>("home/user/documents/file.txt"));
    ASSUME_NOT_CNULL(basename);
    ASSUME_ITS_EQUAL_CSTR(basename, "file.txt");
    free(basename);
}

// ** Test fossil_sys_path_dirname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_dirname) {
    char *dirname = fossil_sys_path_dirname(const_cast<char *>("home/user/documents/file.txt"));
    ASSUME_NOT_CNULL(dirname);
    ASSUME_ITS_EQUAL_CSTR(dirname, "home/user/documents");
    free(dirname);
}

// ** Test fossil_sys_path_extname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_extname) {
    char *extname = fossil_sys_path_extname(const_cast<char *>("file.txt"));
    ASSUME_NOT_CNULL(extname);
    ASSUME_ITS_EQUAL_CSTR(extname, ".txt");
    free(extname);
}

// ** Test fossil_sys_path_strip_ext Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_strip_ext) {
    char *stripped = fossil_sys_path_strip_ext(const_cast<char *>("file.txt"));
    ASSUME_NOT_CNULL(stripped);
    ASSUME_ITS_EQUAL_CSTR(stripped, "file");
    free(stripped);
}

// ** Test fossil_sys_path_isabs Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isabs) {
#if defined(_WIN32)
    ASSUME_ITS_TRUE(fossil_sys_path_isabs(const_cast<char *>("C:\\Windows")));
    ASSUME_ITS_FALSE(fossil_sys_path_isabs(const_cast<char *>("Windows\\System32")));
#else
    ASSUME_ITS_TRUE(fossil_sys_path_isabs(const_cast<char *>("/usr/bin")));
    ASSUME_ITS_FALSE(fossil_sys_path_isabs(const_cast<char *>("usr/bin")));
#endif
}

// ** Test fossil_sys_path_exists Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_exists) {
    ASSUME_ITS_TRUE(fossil_sys_path_exists(const_cast<char *>("/")));
    ASSUME_ITS_FALSE(fossil_sys_path_exists(const_cast<char *>("/nonexistent_path")));
}

// ** Test fossil_sys_path_isdir Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isdir) {
    ASSUME_ITS_TRUE(fossil_sys_path_isdir(const_cast<char *>("/")));
    ASSUME_ITS_FALSE(fossil_sys_path_isdir(const_cast<char *>("/nonexistent_path")));
}

// ** Test fossil_sys_path_isfile Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_isfile) {
    ASSUME_ITS_FALSE(fossil_sys_path_isfile(const_cast<char *>("/")));
    ASSUME_ITS_FALSE(fossil_sys_path_isfile(const_cast<char *>("/nonexistent_file")));
}

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
    ASSUME_ITS_EQUAL_CSTR(envvar, "PATH");
#endif
}

// ** Test fossil::sys::Path::join Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_join_class) {
    std::string joined = fossil::sys::Path::join("home", "user");
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user");

    joined = fossil::sys::Path::join("home/", "user");
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user");
}

// ** Test fossil::sys::Path::joinv Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_joinv_class) {
    const char *paths[] = {"home", "user", "documents"};
    std::string joined = fossil::sys::Path::joinv(3, paths);
    ASSUME_ITS_EQUAL_CSTR(joined, "home/user/documents");
}

// ** Test fossil::sys::Path::normalize Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_normalize_class) {
    std::string normalized = fossil::sys::Path::normalize("home//user///documents");
    ASSUME_ITS_EQUAL_CSTR(normalized, "home/user/documents");
}

// ** Test fossil::sys::Path::basename Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_basename_class) {
    std::string basename = fossil::sys::Path::basename("home/user/documents/file.txt");
    ASSUME_ITS_EQUAL_CSTR(basename, "file.txt");
}

// ** Test fossil::sys::Path::dirname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_dirname_class) {
    std::string dirname = fossil::sys::Path::dirname("home/user/documents/file.txt");
    ASSUME_ITS_EQUAL_CSTR(dirname, "home/user/documents");
}

// ** Test fossil::sys::Path::extname Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_extname_class) {
    std::string extname = fossil::sys::Path::extname("file.txt");
    ASSUME_ITS_EQUAL_CSTR(extname, ".txt");
}

// ** Test fossil::sys::Path::strip_ext Function **
FOSSIL_TEST_CASE(cpp_test_fossil_sys_path_strip_ext_class) {
    std::string stripped = fossil::sys::Path::strip_ext("file.txt");
    ASSUME_ITS_EQUAL_CSTR(stripped, "file");
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
    // FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_separator);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_envvar);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_join);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_joinv);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_normalize);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_basename);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_dirname);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_extname);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_strip_ext);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isabs);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_exists);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isdir);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isfile);

    // FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_separator_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_envvar_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_join_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_joinv_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_normalize_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_basename_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_dirname_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_extname_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_strip_ext_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isabs_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_exists_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isdir_class);
    FOSSIL_TEST_ADD(cpp_bitwise_suite, cpp_test_fossil_sys_path_isfile_class);

    FOSSIL_TEST_REGISTER(cpp_bitwise_suite);
}
