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
#include "fossil/sys/joinpath.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h> // For realpath
#include <stdlib.h> // For realpath declaration

#ifndef MAX_PATH
#define MAX_PATH 4096 // Define MAX_PATH if not already defined
#endif

#if defined(_WIN32)
#include <windows.h>
#define PATH_SEP '\\'
#define PATH_ENV "Path"
#else
#include <unistd.h>
#include <sys/stat.h>
#define PATH_SEP '/'
#define PATH_ENV "PATH"
#endif


char *_custom_strdup(const char *str) {
    if (!str) {
        return NULL;
    }
    size_t len = strlen(str);
    char *copy = (char *)malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, str);
    return copy;
}

char fossil_sys_path_separator(void) {
    return PATH_SEP;
}

const char *fossil_sys_path_envvar(void) {
    return PATH_ENV;
}

char *fossil_sys_path_join(const char *a, const char *b) {
    if (!a || !b) {
        return NULL;
    }

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t sep_len = (len_a > 0 && a[len_a - 1] != PATH_SEP) ? 1 : 0;

    char *result = (char *)malloc(len_a + len_b + sep_len + 1);
    if (!result) {
        return NULL;
    }

    strcpy(result, a);
    if (sep_len) {
        result[len_a] = PATH_SEP;
        strcpy(result + len_a + sep_len, b);
    } else {
        strcpy(result + len_a, b);
    }

    return result;
}

char *fossil_sys_path_joinv(size_t count, const char **paths) {
    if (count == 0 || !paths) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        if (paths[i]) {
            total_length += strlen(paths[i]);
            if (i < count - 1) {
                total_length += 1; // For the separator
            }
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (!result) {
        return NULL;
    }

    result[0] = '\0';
    for (size_t i = 0; i < count; ++i) {
        if (paths[i]) {
            strcat(result, paths[i]);
            if (i < count - 1) {
                char sep_str[2] = {PATH_SEP, '\0'};
                strcat(result, sep_str);
            }
        }
    }

    return result;
}

char *fossil_sys_path_normalize(const char *path) {
    if (!path) {
        return NULL;
    }

    size_t len = strlen(path);
    char *normalized = (char *)malloc(len + 1);
    if (!normalized) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (path[i] == PATH_SEP && (i == 0 || path[i - 1] == PATH_SEP)) {
            continue; // Skip redundant separators
        }
        normalized[j++] = path[i];
    }
    normalized[j] = '\0';

    return normalized;
}

char *fossil_sys_path_abspath(const char *path) {
    if (!path) {
        return NULL;
    }

    char *abs_path = (char *)malloc(MAX_PATH);
    if (!abs_path) {
        return NULL;
    }
#if defined(_WIN32)
    if (_fullpath(abs_path, path, MAX_PATH) == NULL) {
        free(abs_path);
        return NULL;
    }
#else
    if (realpath(path, abs_path) == NULL) {
        free(abs_path);
        return NULL;
    }
#endif
    return abs_path;
}

char *fossil_sys_path_relpath(const char *path, const char *start) {
    if (!path || !start) {
        return NULL;
    }

    char *abs_path = fossil_sys_path_abspath(path);
    if (!abs_path) {
        return NULL;
    }

    char *abs_start = fossil_sys_path_abspath(start);
    if (!abs_start) {
        free(abs_path);
        return NULL;
    }

    char *rel_path = (char *)malloc(MAX_PATH);
    if (!rel_path) {
        free(abs_path);
        free(abs_start);
        return NULL;
    }
#if defined(_WIN32)
    if (strncmp(abs_path, abs_start, strlen(abs_start)) != 0) {
        free(abs_path);
        free(abs_start);
        free(rel_path);
        return NULL;
    }
    snprintf(rel_path, MAX_PATH, "%s", abs_path + strlen(abs_start));
#else
    if (realpath(abs_path, rel_path) == NULL) {
        free(abs_path);
        free(abs_start);
        free(rel_path);
        return NULL;
    }
    if (strncmp(rel_path, abs_start, strlen(abs_start)) != 0) {
        free(abs_path);
        free(abs_start);
        free(rel_path);
        return NULL;
    }
    memmove(rel_path, rel_path + strlen(abs_start), strlen(rel_path) - strlen(abs_start) + 1);
#endif
    free(abs_path);
    free(abs_start);
    return rel_path;
}

char *fossil_sys_path_basename(const char *path) {
    if (!path) {
        return NULL;
    }

    const char *base = strrchr(path, PATH_SEP);
    if (base) {
        base++;
    } else {
        base = path;
    }

    return _custom_strdup(base);
}

char *fossil_sys_path_dirname(const char *path) {
    if (!path) {
        return NULL;
    }

    char *dir = _custom_strdup(path);
    if (!dir) {
        return NULL;
    }

    char *last_sep = strrchr(dir, PATH_SEP);
    if (last_sep) {
        *last_sep = '\0';
    } else {
        free(dir);
        return NULL;
    }

    return dir;
}

char *fossil_sys_path_extname(const char *path) {
    if (!path) {
        return NULL;
    }

    const char *ext = strrchr(path, '.');
    if (ext) {
        return _custom_strdup(ext);
    } else {
        return NULL;
    }
}

char *fossil_sys_path_strip_ext(const char *path) {
    if (!path) {
        return NULL;
    }

    char *stripped = _custom_strdup(path);
    if (!stripped) {
        return NULL;
    }

    char *last_dot = strrchr(stripped, '.');
    if (last_dot) {
        *last_dot = '\0';
    }

    return stripped;
}

int fossil_sys_path_isabs(const char *path) {
    if (!path) {
        return 0;
    }
#if defined(_WIN32)
    return (path[0] == '/' || path[0] == '\\' || (path[1] == ':' && (path[2] == '/' || path[2] == '\\')));
#else
    return (path[0] == '/');
#endif
}

int fossil_sys_path_exists(const char *path) {
    if (!path) {
        return 0;
    }
#if defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES);
#else
    struct stat buffer;
    return (stat(path, &buffer) == 0);
#endif
}

int fossil_sys_path_isdir(const char *path) {
    if (!path) {
        return 0;
    }
#if defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat buffer;
    return (stat(path, &buffer) == 0 && S_ISDIR(buffer.st_mode));
#endif
}

int fossil_sys_path_isfile(const char *path) {
    if (!path) {
        return 0;
    }
#if defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat buffer;
    return (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode));
#endif
}
