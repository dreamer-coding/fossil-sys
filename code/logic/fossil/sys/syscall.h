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
#ifndef FOSSIL_SYS_CALL_H
#define FOSSIL_SYS_CALL_H

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Function to execute a system command.
 * This function takes a command string as input and executes it using the 
 * system's command processor. The return value is the exit status of the 
 * command.
 */
int fossil_sys_call_execute(const char *command);

/* 
 * Function to get the current process ID.
 * This function returns the process ID of the calling process. 
 * The process ID is a unique identifier for the process.
 */
int fossil_sys_call_getpid(void);

/* 
 * Function to sleep for a specified number of milliseconds.
 * This function suspends the execution of the calling thread for the specified 
 * number of milliseconds.
 */
void fossil_sys_call_sleep(int milliseconds);

/* 
 * Function to create a new file.
 * This function creates a new file with the specified filename. 
 * The return value is 0 on success, or a negative error code on failure.
 */
int fossil_sys_call_create_file(const char *filename);

/**
 * @brief Delete a file.
 *
 * Removes a file from the filesystem.
 *
 * @param filename Path to the file to delete.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_delete_file(const char *filename);

/**
 * @brief Check if a file exists.
 *
 * @param filename Path to the file.
 * @return 1 if the file exists, 0 if not.
 */
int fossil_sys_call_file_exists(const char *filename);

/**
 * @brief Create a directory.
 *
 * @param dirname Path of the directory to create.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_create_directory(const char *dirname);

/**
 * @brief Delete a directory (optionally recursive).
 *
 * @param dirname Path of the directory to delete.
 * @param recursive If non-zero, delete all contents recursively.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_delete_directory(const char *dirname, int recursive);

/**
 * @brief Get the current working directory.
 *
 * @param buffer Buffer to receive the current path.
 * @param size Size of the buffer.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_getcwd(char *buffer, size_t size);

/**
 * @brief Change the current working directory.
 *
 * @param path Path to set as current working directory.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_chdir(const char *path);

/**
 * @brief List files in a directory.
 *
 * Returns a list of filenames in a given directory.
 * (Could return a dynamically allocated array of strings, or take a callback function.)
 *
 * @param dirname Path to the directory.
 * @param out_list Pointer to array of strings (allocated by function).
 * @param out_count Pointer to receive the number of entries.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_list_directory(const char *dirname, char ***out_list, size_t *out_count);

/**
 * @brief Check if a path is a directory.
 *
 * @param path Path to check.
 * @return 1 if directory, 0 if not.
 */
int fossil_sys_call_is_directory(const char *path);

/**
 * @brief Check if a path is a regular file.
 *
 * @param path Path to check.
 * @return 1 if regular file, 0 if not.
 */
int fossil_sys_call_is_file(const char *path);

/**
 * @brief Terminate the current process.
 *
 * @param exit_code Exit code to return to the operating system.
 */
void fossil_sys_call_exit(int exit_code);

/**
 * @brief Execute a command and capture output.
 *
 * Runs a command and stores stdout in a buffer (similar to popen).
 *
 * @param command Command string to execute.
 * @param buffer Buffer to store output.
 * @param size Size of the buffer.
 * @return 0 on success, negative error code on failure.
 */
int fossil_sys_call_execute_capture(const char *command, char *buffer, size_t size);

/**
 * @brief Get the parent process ID.
 *
 * @return PID of the parent process.
 */
int fossil_sys_call_getppid(void);

#ifdef __cplusplus
}
#include <string>

/**
 * Fossil namespace.
 */
namespace fossil {

    /**
     * System namespace.
     */
    namespace sys {

        /**
         * Syscall class.
         */
        class Syscall {
        public:

            /**
             * Execute a system command.
             *
             * @param command The command to execute.
             * @return The return value of the system command.
             */
            static int execute(const char *command) {
                return fossil_sys_call_execute(command);
            }

            /**
             * Execute a system command.
             *
             * @param command The command to execute
             * @return The return value of the system command.
             */
            static int execute(const std::string &command) {
                return fossil_sys_call_execute(command.c_str());
            }

            /**
             * Get the current process ID.
             *
             * @return The current process ID.
             */
            static int getpid() {
                return fossil_sys_call_getpid();
            }

            /**
             * Sleep for a specified number of milliseconds.
             *
             * @param milliseconds The number of milliseconds to sleep.
             */
            static void sleep(int milliseconds) {
                fossil_sys_call_sleep(milliseconds);
            }

            /**
             * Create a new file.
             *
             * @param filename The name of the file to create.
             * @return 0 on success, or a negative error code on failure.
             */
            static int create_file(const char *filename) {
                return fossil_sys_call_create_file(filename);
            }

            /**
             * Create a new file.
             *
             * @param filename The name of the file to create.
             * @return 0 on success, or a negative error code on failure.
             */
            static int create_file(const std::string &filename) {
                return fossil_sys_call_create_file(filename.c_str());
            }

        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
