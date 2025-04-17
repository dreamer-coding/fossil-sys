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
#include "fossil/sys/bitwise.h"
#include <string.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t fossil_sys_bitwise_parse(const char *input, const fossil_sys_bitwise_table_t *table) {
    uint64_t result = 0;
    size_t input_len = strlen(input);
    char *input_copy = (char *)malloc(input_len + 1);
    if (!input_copy) {
        return 0; // Memory allocation failed
    }
    strcpy(input_copy, input);
    char *token = strtok(input_copy, "|");
    while (token != NULL) {
        for (size_t i = 0; i < table->count; ++i) {
            if (strcmp(token, table->entries[i].name) == 0) {
                result |= table->entries[i].bit;
                break;
            }
        }
        token = strtok(NULL, "|");
    }
    free(input_copy);
    return result;
}

int fossil_sys_bitwise_format(uint64_t bits, const fossil_sys_bitwise_table_t *table, char *out, size_t out_size) {
    size_t offset = 0;
    for (size_t i = 0; i < table->count; ++i) {
        if (bits & table->entries[i].bit) {
            size_t len = strlen(table->entries[i].name);
            if (offset + len + 1 < out_size) {
                if (offset > 0) {
                    out[offset++] = '|';
                }
                strcpy(out + offset, table->entries[i].name);
                offset += len;
            } else {
                return -1; // Buffer too small
            }
        }
    }
    if (offset < out_size) {
        out[offset] = '\0'; // Null-terminate the string
    } else {
        return -1; // Buffer too small
    }
    return 0;
}

int fossil_sys_bitwise_lookup(const char *name, const fossil_sys_bitwise_table_t *table, uint64_t *out_bit) {
    for (size_t i = 0; i < table->count; ++i) {
        if (strcmp(name, table->entries[i].name) == 0) {
            *out_bit = table->entries[i].bit;
            return 0; // Found
        }
    }
    return -1; // Not found
}
