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
#ifndef FOSSIL_SYS_COMMAND_H
#define FOSSIL_SYS_COMMAND_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute a command and return the result.
 *
 * @param process The command to be executed.
 * @return        The result of the command execution.
 */
int32_t fossil_sys_command(char * process);

/**
 * Check if a command execution was successful.
 *
 * @param process The command to be checked.
 * @return        1 if the command was successful, 0 otherwise.
 */
int32_t fossil_sys_command_success(char * process);

/**
 * Retrieve the output of a command execution.
 *
 * @param process     The command to retrieve output from.
 * @param output      Buffer to store the output.
 * @param output_size Size of the output buffer.
 * @return            The result of the command execution.
 */
int32_t fossil_sys_command_output(char * process, char * output, size_t output_size);

/**
 * Check if a command exists.
 *
 * @param process The command to be checked.
 * @return        1 if the command exists, 0 otherwise.
 */
int32_t fossil_sys_command_exists(char * process);

/**
 * Erase a command and check if it exists.
 *
 * @param path The command to be erased.
 * @return     1 if the command exists, 0 otherwise.
 */
int32_t fossil_sys_command_erase_exists(char * path);

/**
 * Safely concatenate two strings into a destination buffer.
 *
 * @param dest      The destination buffer for the concatenated strings.
 * @param src       The source string to be concatenated.
 * @param dest_size The size of the destination buffer.
 */
void fossil_sys_command_strcat_safe(char * dest, const char * src, size_t dest_size);

#ifdef __cplusplus
}

#include <string>

namespace fossil {

    namespace sys {

        /**
         * Command class to wrap C functions for command execution.
         */
        class Command {
        public:

            /**
             * Execute a command.
             *
             * @param process The command to be executed.
             * @return        The result of the command execution.
             */
            static int32_t execute(const char * process) {
                return fossil_sys_command((char *)process);
            }

            /**
             * Check if a command execution was successful.
             *
             * @param process The command to be checked.
             * @return        1 if the command was successful, 0 otherwise.
             */
            static int32_t is_success(const char * process) {
                return fossil_sys_command_success((char *)process);
            }

            /**
             * Retrieve the output of a command execution.
             *
             * @param process     The command to retrieve output from.
             * @param output      Buffer to store the output.
             * @param output_size Size of the output buffer.
             * @return            The result of the command execution.
             */
            static int32_t get_output(const char * process, char * output, size_t output_size) {
                return fossil_sys_command_output((char *)process, output, output_size);
            }

            /**
             * Check if a command exists.
             *
             * @param process The command to be checked.
             * @return        1 if the command exists, 0 otherwise.
             */
            static int32_t exists(const char * process) {
                return fossil_sys_command_exists((char *)process);
            }

            /**
             * Erase a command and check if it exists.
             *
             * @param path The command to be erased.
             * @return     1 if the command exists, 0 otherwise.
             */
            static int32_t erase_exists(const char * path) {
                return fossil_sys_command_erase_exists((char *)path);
            }

            /**
             * Safely concatenate two strings into a destination buffer.
             *
             * @param dest      The destination buffer for the concatenated strings.
             * @param src       The source string to be concatenated.
             * @param dest_size The size of the destination buffer.
             */
            static void strcat_safe(char * dest, const char * src, size_t dest_size) {
                fossil_sys_command_strcat_safe(dest, src, dest_size);
            }

            /**
             * Execute a command using std::string.
             *
             * @param process The command to be executed.
             * @return        The result of the command execution.
             */
            static int32_t execute(const std::string &process) {
                return fossil_sys_command(process.c_str());
            }

            /**
             * Check if a command execution was successful using std::string.
             *
             * @param process The command to be checked.
             * @return        1 if the command was successful, 0 otherwise.
             */
            static int32_t is_success(const std::string &process) {
                return fossil_sys_command_success(process.c_str());
            }

            /**
             * Retrieve the output of a command execution using std::string.
             *
             * @param process The command to retrieve output from.
             * @param output  String to store the output.
             * @return        The result of the command execution.
             */
            static int32_t get_output(const std::string &process, std::string &output) {
                char buffer[1024];
                int32_t result = fossil_sys_command_output(process.c_str(), buffer, sizeof(buffer));
                output = buffer;
                return result;
            }

            /**
             * Check if a command exists using std::string.
             *
             * @param process The command to be checked.
             * @return        1 if the command exists, 0 otherwise.
             */
            static int32_t exists(const std::string &process) {
                return fossil_sys_command_exists(process.c_str());
            }

            /**
             * Erase a command and check if it exists using std::string.
             *
             * @param path The command to be erased.
             * @return     1 if the command exists, 0 otherwise.
             */
            static int32_t erase_exists(const std::string &path) {
                return fossil_sys_command_erase_exists(path.c_str());
            }

            /**
             * Safely concatenate two strings into a destination buffer using std::string.
             *
             * @param dest The destination string for the concatenated strings.
             * @param src  The source string to be concatenated.
             */
            static void strcat_safe(std::string &dest, const std::string &src) {
                char buffer[1024];
                strncpy(buffer, dest.c_str(), sizeof(buffer));
                fossil_sys_command_strcat_safe(buffer, src.c_str(), sizeof(buffer));
                dest = buffer;
            }

        };
    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
