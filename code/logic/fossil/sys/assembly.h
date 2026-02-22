/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_SYS_ASM_H
#define FOSSIL_SYS_ASM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------
 * Types
 * ----------------------------------------------------- */
typedef enum {
    FOSSIL_ASM_TYPE_NONE = 0,
    FOSSIL_ASM_TYPE_X86,
    FOSSIL_ASM_TYPE_X64,
    FOSSIL_ASM_TYPE_ARM,
    FOSSIL_ASM_TYPE_ARM64
} fossil_sys_asm_arch_t;

typedef struct {
    const char* id;           /* string ID for AI/meta usage */
    fossil_sys_asm_arch_t arch;
    uint8_t* code;
    size_t size;
} fossil_sys_asm_block_t;

/* ------------------------------------------------------
 * Functions
 * ----------------------------------------------------- */

/* Assemble text into machine code */
bool fossil_sys_asm_assemble(fossil_sys_asm_arch_t arch, const char* source, fossil_sys_asm_block_t* out_block);

/* Free memory allocated by assemble */
void fossil_sys_asm_free(fossil_sys_asm_block_t* block);

/* Execute assembled code */
int fossil_sys_asm_execute(const fossil_sys_asm_block_t* block, int argc, char** argv);

/* Dump assembled code to hex string */
char* fossil_sys_asm_dump_hex(const fossil_sys_asm_block_t* block);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_SYS_ASM_H */
