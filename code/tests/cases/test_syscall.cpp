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
#include <chrono>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(cpp_syscall_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_syscall_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_syscall_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_test_sys_call_execute) {
    int result = fossil::sys::Syscall::execute("echo Fossil Logic");
    ASSUME_ITS_TRUE(result == 0);
}

FOSSIL_TEST(cpp_test_sys_call_getpid) {
    int pid = fossil::sys::Syscall::getpid();
    ASSUME_ITS_TRUE(pid > 0);
}

FOSSIL_TEST(cpp_test_sys_call_create_file) {
    const std::string filename = "test_file.txt";
    int result = fossil::sys::Syscall::create_file(filename);
    ASSUME_ITS_TRUE(result == 0);
    remove(filename.c_str()); // Clean up the test file
}

FOSSIL_TEST(cpp_test_sys_call_execute_string) {
    int result = fossil::sys::Syscall::execute("echo Fossil Logic");
    ASSUME_ITS_TRUE(result == 0);
}

FOSSIL_TEST(cpp_test_sys_call_getpid_class) {
    int pid = fossil::sys::Syscall::getpid();
    ASSUME_ITS_TRUE(pid > 0);
}

FOSSIL_TEST(cpp_test_sys_call_create_file_class) {
    const std::string filename = "test_file_class.txt";
    int result = fossil::sys::Syscall::create_file(filename);
    ASSUME_ITS_TRUE(result == 0);
    remove(filename.c_str()); // Clean up the test file
}

FOSSIL_TEST(cpp_test_sys_call_create_file_cstr_class) {
    const char *filename = "test_file_cstr_class.txt";
    int result = fossil::sys::Syscall::create_file(std::string(filename));
    ASSUME_ITS_TRUE(result == 0);
    remove(filename); // Clean up the test file
}

FOSSIL_TEST(cpp_test_sys_call_delete_file) {
    const std::string filename = "test_delete_file.txt";
    // Create file first
    int create_result = fossil::sys::Syscall::create_file(filename);
    ASSUME_ITS_TRUE(create_result == 0);
    // Delete file
    int delete_result = fossil::sys::Syscall::delete_file(filename);
    ASSUME_ITS_TRUE(delete_result == 0);
}

FOSSIL_TEST(cpp_test_sys_call_file_exists) {
    const std::string filename = "test_exists_file.txt";
    fossil::sys::Syscall::create_file(filename);
    int exists = fossil::sys::Syscall::file_exists(filename);
    ASSUME_ITS_TRUE(exists == 1);
    fossil::sys::Syscall::delete_file(filename);
    int not_exists = fossil::sys::Syscall::file_exists(filename);
    ASSUME_ITS_TRUE(not_exists == 0);
}

FOSSIL_TEST(cpp_test_sys_call_create_directory) {
    const std::string dirname = "test_dir";
    int result = fossil::sys::Syscall::create_directory(dirname);
    ASSUME_ITS_TRUE(result == 0);
    fossil::sys::Syscall::delete_directory(dirname, 0);
}

FOSSIL_TEST(cpp_test_sys_call_delete_directory) {
    const std::string dirname = "test_del_dir";
    fossil::sys::Syscall::create_directory(dirname);
    int result = fossil::sys::Syscall::delete_directory(dirname, 0);
    ASSUME_ITS_TRUE(result == 0);
}

FOSSIL_TEST(cpp_test_sys_call_is_directory) {
    const std::string dirname = "test_is_dir";
    fossil::sys::Syscall::create_directory(dirname);
    int is_dir = fossil::sys::Syscall::is_directory(dirname);
    ASSUME_ITS_TRUE(is_dir == 1);
    fossil::sys::Syscall::delete_directory(dirname, 0);
}

FOSSIL_TEST(cpp_test_sys_call_is_file) {
    const std::string filename = "test_is_file.txt";
    fossil::sys::Syscall::create_file(filename);
    int is_file = fossil::sys::Syscall::is_file(filename);
    ASSUME_ITS_TRUE(is_file == 1);
    fossil::sys::Syscall::delete_file(filename);
}

FOSSIL_TEST(cpp_test_sys_call_chdir_and_getcwd) {
    const std::string dirname = "test_chdir_dir";
    fossil::sys::Syscall::create_directory(dirname);
    std::string cwd_str_before(256, '\0');
    fossil::sys::Syscall::getcwd(&cwd_str_before, cwd_str_before.size());
    int chdir_result = fossil::sys::Syscall::chdir(dirname);
    ASSUME_ITS_TRUE(chdir_result == 0);
    std::string cwd_str_after(256, '\0');
    fossil::sys::Syscall::getcwd(&cwd_str_after, cwd_str_after.size());
    ASSUME_ITS_TRUE(cwd_str_after.find(dirname) != std::string::npos);
    fossil::sys::Syscall::chdir(cwd_str_before);
    fossil::sys::Syscall::delete_directory(dirname, 0);
}

FOSSIL_TEST(cpp_test_sys_call_sleep) {
    auto start = std::chrono::steady_clock::now();
    fossil::sys::Syscall::sleep(100);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    ASSUME_ITS_TRUE(elapsed >= 90); // Allow some tolerance
}

FOSSIL_TEST(cpp_test_sys_call_execute_capture) {
    std::string buffer(128, '\0');
    int result = fossil::sys::Syscall::execute_capture("echo FossilCapture", &buffer);
    ASSUME_ITS_TRUE(result == 0);
    ASSUME_ITS_TRUE(buffer.find("FossilCapture") != std::string::npos);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_syscall_tests) {
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_execute);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_getpid);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_create_file);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_execute_string);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_getpid_class);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_create_file_class);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_create_file_cstr_class);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_delete_file);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_file_exists);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_create_directory);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_delete_directory);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_is_directory);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_is_file);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_chdir_and_getcwd);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_sleep);
    FOSSIL_TEST_ADD(cpp_syscall_suite, cpp_test_sys_call_execute_capture);

    FOSSIL_TEST_REGISTER(cpp_syscall_suite);
}
