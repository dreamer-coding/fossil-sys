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
#ifndef FOSSIL_SYS_JOINPATH_H
#define FOSSIL_SYS_JOINPATH_H

#include "cnullptr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the system-specific path separator character.
 * For example, '/' on Unix-like systems and '\\' on Windows.
 */
char fossil_sys_path_separator(void);

/**
 * Returns the environment variable used for path separation.
 * For example, ':' on Unix-like systems and ';' on Windows.
 */
const char *fossil_sys_path_envvar(void);

/**
 * Joins two paths into a single path.
 * 
 * @param a The first path.
 * @param b The second path to append to the first.
 * @return A newly allocated string containing the joined path.
 */
char *fossil_sys_path_join(const char *a, const char *b);

/**
 * Joins multiple paths into a single path.
 * 
 * @param count The number of paths to join.
 * @param paths An array of paths to join.
 * @return A newly allocated string containing the joined path.
 */
char *fossil_sys_path_joinv(size_t count, const char **paths);

/**
 * Normalizes a given path by resolving redundant separators and relative segments.
 * 
 * @param path The path to normalize.
 * @return A newly allocated string containing the normalized path.
 */
char *fossil_sys_path_normalize(const char *path);

/**
 * Extracts the base name (file name) from a given path.
 * 
 * @param path The path to extract the base name from.
 * @return A newly allocated string containing the base name.
 */
char *fossil_sys_path_basename(const char *path);

/**
 * Extracts the directory name from a given path.
 * 
 * @param path The path to extract the directory name from.
 * @return A newly allocated string containing the directory name.
 */
char *fossil_sys_path_dirname(const char *path);

/**
 * Extracts the file extension from a given path.
 * 
 * @param path The path to extract the extension from.
 * @return A newly allocated string containing the file extension.
 */
char *fossil_sys_path_extname(const char *path);

/**
 * Removes the file extension from a given path.
 * 
 * @param path The path to strip the extension from.
 * @return A newly allocated string containing the path without the extension.
 */
char *fossil_sys_path_strip_ext(const char *path);

/**
 * Checks if a given path is absolute.
 * 
 * @param path The path to check.
 * @return Non-zero if the path is absolute, zero otherwise.
 */
int fossil_sys_path_isabs(const char *path);

/**
 * Checks if a given path exists in the file system.
 * 
 * @param path The path to check.
 * @return Non-zero if the path exists, zero otherwise.
 */
int fossil_sys_path_exists(const char *path);

/**
 * Checks if a given path is a directory.
 * 
 * @param path The path to check.
 * @return Non-zero if the path is a directory, zero otherwise.
 */
int fossil_sys_path_isdir(const char *path);

/**
 * Checks if a given path is a file.
 * 
 * @param path The path to check.
 * @return Non-zero if the path is a file, zero otherwise.
 */
int fossil_sys_path_isfile(const char *path);

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
         * A utility class for handling file system paths.
         */
        class Path {
        public:
            /**
             * Retrieves the system-specific path separator.
             * 
             * @return A string containing the path separator character.
             */
            static std::string separator() {
                return std::string(1, fossil_sys_path_separator());
            }

            /**
             * Retrieves the environment variable used for path separation.
             * 
             * @return A string containing the environment variable for path separation.
             */
            static std::string envvar() {
                return fossil_sys_path_envvar();
            }

            /**
             * Joins two paths into a single path.
             * 
             * @param a The first path.
             * @param b The second path to append to the first.
             * @return A string containing the joined path.
             */
            static std::string join(const std::string &a, const std::string &b) {
                return fossil_sys_path_join(a.c_str(), b.c_str());
            }

            /**
             * Joins multiple paths into a single path.
             * 
             * @param count The number of paths to join.
             * @param paths An array of paths to join.
             * @return A string containing the joined path.
             */
            static std::string joinv(size_t count, const char **paths) {
                return fossil_sys_path_joinv(count, paths);
            }

            /**
             * Normalizes a given path by resolving redundant separators and relative segments.
             * 
             * @param path The path to normalize.
             * @return A string containing the normalized path.
             */
            static std::string normalize(const std::string &path) {
                return fossil_sys_path_normalize(path.c_str());
            }

            /**
             * Extracts the base name (file name) from a given path.
             * 
             * @param path The path to extract the base name from.
             * @return A string containing the base name.
             */
            static std::string basename(const std::string &path) {
                return fossil_sys_path_basename(path.c_str());
            }

            /**
             * Extracts the directory name from a given path.
             * 
             * @param path The path to extract the directory name from.
             * @return A string containing the directory name.
             */
            static std::string dirname(const std::string &path) {
                return fossil_sys_path_dirname(path.c_str());
            }

            /**
             * Extracts the file extension from a given path.
             * 
             * @param path The path to extract the extension from.
             * @return A string containing the file extension.
             */
            static std::string extname(const std::string &path) {
                return fossil_sys_path_extname(path.c_str());
            }

            /**
             * Removes the file extension from a given path.
             * 
             * @param path The path to strip the extension from.
             * @return A string containing the path without the extension.
             */
            static std::string strip_ext(const std::string &path) {
                return fossil_sys_path_strip_ext(path.c_str());
            }

            /**
             * Checks if a given path is absolute.
             * 
             * @param path The path to check.
             * @return True if the path is absolute, false otherwise.
             */
            static bool isabs(const std::string &path) {
                return fossil_sys_path_isabs(path.c_str());
            }

            /**
             * Checks if a given path exists in the file system.
             * 
             * @param path The path to check.
             * @return True if the path exists, false otherwise.
             */
            static bool exists(const std::string &path) {
                return fossil_sys_path_exists(path.c_str());
            }

            /**
             * Checks if a given path is a directory.
             * 
             * @param path The path to check.
             * @return True if the path is a directory, false otherwise.
             */
            static bool isdir(const std::string &path) {
                return fossil_sys_path_isdir(path.c_str());
            }

            /**
             * Checks if a given path is a file.
             * 
             * @param path The path to check.
             * @return True if the path is a file, false otherwise.
             */
            static bool isfile(const std::string &path) {
                return fossil_sys_path_isfile(path.c_str());
            }

        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
