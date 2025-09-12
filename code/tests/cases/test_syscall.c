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
#include <fossil/pizza/framework.h>

#include "fossil/sys/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_syscall_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_syscall_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_syscall_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_sys_call_execute) {
    int result = fossil_sys_call_execute("echo Fossil Logic");
    ASSUME_ITS_TRUE(result == 0);
}

FOSSIL_TEST(c_test_sys_call_getpid) {
    int pid = fossil_sys_call_getpid();
    ASSUME_ITS_TRUE(pid > 0);
}

FOSSIL_TEST(c_test_sys_call_create_file) {
    const char *filename = "test_file.txt";
    int result = fossil_sys_call_create_file(filename);
    ASSUME_ITS_TRUE(result == 0);
    remove(filename); // Clean up the test file
}

FOSSIL_TEST(c_test_sys_call_delete_file) {
    const char *filename = "delete_me.txt";
    FILE *f = fopen(filename, "w");
    if (f) fclose(f);
    int result = fossil_sys_call_delete_file(filename);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(!fossil_sys_call_file_exists(filename));
}

FOSSIL_TEST(c_test_sys_call_file_exists) {
    const char *filename = "exists.txt";
    FILE *f = fopen(filename, "w");
    if (f) fclose(f);
    ASSUME_ITS_TRUE(fossil_sys_call_file_exists(filename) == 1);
    remove(filename);
    ASSUME_ITS_TRUE(fossil_sys_call_file_exists(filename) == 0);
}

FOSSIL_TEST(c_test_sys_call_create_directory) {
    const char *dirname = "test_dir";
    int result = fossil_sys_call_create_directory(dirname);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(fossil_sys_call_is_directory(dirname) == 1);
    fossil_sys_call_delete_directory(dirname, 0);
}

FOSSIL_TEST(c_test_sys_call_delete_directory_non_recursive) {
    const char *dirname = "dir_non_recursive";
    fossil_sys_call_create_directory(dirname);
    int result = fossil_sys_call_delete_directory(dirname, 0);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(fossil_sys_call_is_directory(dirname) == 0);
}

FOSSIL_TEST(c_test_sys_call_delete_directory_recursive) {
    const char *dirname = "dir_recursive";
    fossil_sys_call_create_directory(dirname);
    FILE *f;
#if defined(_WIN32)
    char path[256];
    snprintf(path, sizeof(path), "%s\\file.txt", dirname);
    f = fopen(path, "w");
#else
    const char *filename = "dir_recursive/file.txt";
    f = fopen(filename, "w");
#endif
    if (f) fclose(f);
    int result = fossil_sys_call_delete_directory(dirname, 1);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(fossil_sys_call_is_directory(dirname) == 0);
}

FOSSIL_TEST(c_test_sys_call_getcwd_and_chdir) {
    char orig[256], temp[256];
    fossil_sys_call_getcwd(orig, sizeof(orig));
    fossil_sys_call_create_directory("cwd_test");
    fossil_sys_call_chdir("cwd_test");
    fossil_sys_call_getcwd(temp, sizeof(temp));
    ASSUME_ITS_TRUE(strstr(temp, "cwd_test") != NULL);
    fossil_sys_call_chdir(orig);
    fossil_sys_call_delete_directory("cwd_test", 0);
}

FOSSIL_TEST(c_test_sys_call_list_directory) {
    const char *dirname = "list_dir";
    fossil_sys_call_create_directory(dirname);
    char fname1[256], fname2[256];
#if defined(_WIN32)
    snprintf(fname1, sizeof(fname1), "%s\\a.txt", dirname);
    snprintf(fname2, sizeof(fname2), "%s\\b.txt", dirname);
#else
    snprintf(fname1, sizeof(fname1), "%s/a.txt", dirname);
    snprintf(fname2, sizeof(fname2), "%s/b.txt", dirname);
#endif
    FILE *f1 = fopen(fname1, "w");
    FILE *f2 = fopen(fname2, "w");
    if (f1) fclose(f1);
    if (f2) fclose(f2);

    char **list = NULL;
    size_t count = 0;
    int result = fossil_sys_call_list_directory(dirname, &list, &count);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(count >= 2);
    for (size_t i = 0; i < count; ++i) free(list[i]);
    free(list);

    fossil_sys_call_delete_file(fname1);
    fossil_sys_call_delete_file(fname2);
    fossil_sys_call_delete_directory(dirname, 0);
}

FOSSIL_TEST(c_test_sys_call_is_directory_and_is_file) {
    const char *dirname = "type_dir";
    const char *filename = "type_file.txt";
    fossil_sys_call_create_directory(dirname);
    FILE *f = fopen(filename, "w");
    if (f) fclose(f);
    ASSUME_ITS_TRUE(fossil_sys_call_is_directory(dirname) == 1);
    ASSUME_ITS_TRUE(fossil_sys_call_is_file(filename) == 1);
    fossil_sys_call_delete_file(filename);
    fossil_sys_call_delete_directory(dirname, 0);
}

FOSSIL_TEST(c_test_sys_call_sleep) {
    int start = fossil_sys_call_getpid(); // Just to use something
    fossil_sys_call_sleep(1); // Sleep for 1 ms (may be longer on some platforms)
    int end = fossil_sys_call_getpid();
    ASSUME_ITS_TRUE(start == end); // PID should not change
}

FOSSIL_TEST(c_test_sys_call_execute_capture) {
    char buffer[128];
    int result = fossil_sys_call_execute_capture("echo HelloWorld", buffer, sizeof(buffer));
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(strstr(buffer, "HelloWorld") != NULL);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_syscall_tests) {
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_execute);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_getpid);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_create_file);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_delete_file);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_file_exists);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_create_directory);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_delete_directory_non_recursive);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_delete_directory_recursive);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_getcwd_and_chdir);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_list_directory);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_is_directory_and_is_file);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_sleep);
    FOSSIL_TEST_ADD(c_syscall_suite, c_test_sys_call_execute_capture);

    FOSSIL_TEST_REGISTER(c_syscall_suite);
}
