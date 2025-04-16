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
#ifndef FOSSIL_SYS_BITWISE_H
#define FOSSIL_SYS_BITWISE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// A bitwise table entry
typedef struct {
    const char *name;   // e.g., "read"
    uint64_t     bit;   // e.g., 1 << 0
} fossil_sys_bitwise_entry_t;

// A table of bitwise names <-> values
typedef struct {
    const fossil_sys_bitwise_entry_t *entries;
    size_t count;
} fossil_sys_bitwise_table_t;

//
// Flag parsing/formatting
//

/**
 * Parses a string like "read|write" into a bitmask using the given table.
 * 
 * @param input The input string to parse. It should contain bitwise names
 *              separated by '|'.
 * @param table The bitwise table that maps names to bit values.
 * @return The resulting bitmask as a uint64_t value.
 */
uint64_t fossil_sys_bitwise_parse(const char *input, const fossil_sys_bitwise_table_t *table);

/**
 * Formats a bitmask into a string like "read|write".
 * 
 * @param bits The bitmask to format into a human-readable string.
 * @param table The bitwise table that maps bit values to names.
 * @param out The output buffer where the formatted string will be written.
 * @param out_size The size of the output buffer. The resulting string will
 *                 be null-terminated.
 * @return 0 on success, or a non-zero error code on failure.
 */
int fossil_sys_bitwise_format(uint64_t bits, const fossil_sys_bitwise_table_t *table, char *out, size_t out_size);

/**
 * Checks if a string corresponds to a known bit in the table.
 * 
 * @param name The name to look up in the bitwise table.
 * @param table The bitwise table that maps names to bit values.
 * @param out_bit Pointer to a uint64_t where the corresponding bit value
 *                will be stored if the name is found.
 * @return 0 on success, or a non-zero error code if the name is not found.
 */
int fossil_sys_bitwise_lookup(const char *name, const fossil_sys_bitwise_table_t *table, uint64_t *out_bit);

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

        class Bitwise {
        public:
            /**
             * Parses a string like "read|write" into a bitmask using the given table.
             * 
             * @param input The input string to parse.
             * @param table The bitwise table to use for parsing.
             * @return The parsed bitmask.
             */
            static uint64_t parse(const std::string &input, const fossil_sys_bitwise_table_t *table) {
                return fossil_sys_bitwise_parse(input.c_str(), table);
            }

            /**
             * Formats a bitmask into a string like "read|write".
             * 
             * @param bits The bitmask to format.
             * @param table The bitwise table to use for formatting.
             * @param out The output buffer to write the formatted string into.
             * @param out_size The size of the output buffer.
             * @return 0 on success, or an error code on failure.
             */
            static int format(uint64_t bits, const fossil_sys_bitwise_table_t *table, char *out, size_t out_size) {
                return fossil_sys_bitwise_format(bits, table, out, out_size);
            }

            /**
             * Looks up a string in the bitwise table and returns the corresponding bit.
             * 
             * @param name The name to look up.
             * @param table The bitwise table to use for lookup.
             * @param out_bit Pointer to store the resulting bit.
             * @return 0 on success, or an error code on failure.
             */
            static int lookup(const std::string &name, const fossil_sys_bitwise_table_t *table, uint64_t &out_bit) {
                return fossil_sys_bitwise_lookup(name.c_str(), table, &out_bit);
            }
        };

    }

}

#endif

#endif /* FOSSIL_SYS_FRAMEWORK_H */
