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
#ifndef FOSSIL_SYS_ASM_OPS_H
#define FOSSIL_SYS_ASM_OPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ------------------------------------------------------
 * Architecture + backend identifiers (string based)
 * ----------------------------------------------------- */

/* Examples:
 *  "x86"
 *  "x64"
 *  "arm"
 *  "arm64"
 *  "riscv64"
 *  "wasm"
 */
typedef const char* fossil_sys_asm_arch_id_t;

/* Examples:
 *  "native"
 *  "jit"
 *  "interpreter"
 *  "sandbox"
 */
typedef const char* fossil_sys_asm_backend_id_t;


/* ------------------------------------------------------
 * Instruction representation
 * ----------------------------------------------------- */

typedef struct {

    const char* id;              /* AI/meta identifier */
    const char* mnemonic;        /* e.g. "mov", "add" */
    const char* operands;        /* raw operand string */

} fossil_sys_asm_instruction_t;


/* ------------------------------------------------------
 * Instruction stream (text level)
 * ----------------------------------------------------- */

typedef struct {

    const char* id;                  /* AI/meta identifier */
    fossil_sys_asm_arch_id_t arch;   /* target architecture */

    fossil_sys_asm_instruction_t* instructions;
    size_t instruction_count;

} fossil_sys_asm_stream_t;


/* ------------------------------------------------------
 * Executable machine block
 * ----------------------------------------------------- */

typedef struct {

    const char* id;                  /* AI/meta identifier */
    fossil_sys_asm_arch_id_t arch;
    fossil_sys_asm_backend_id_t backend;

    uint8_t* code;
    size_t size;

    bool executable;

} fossil_sys_asm_block_t;


/* ------------------------------------------------------
 * Execution context
 * ----------------------------------------------------- */

typedef struct {

    const char* id;              /* AI/meta identifier */
    fossil_sys_asm_arch_id_t arch;

    void* user_data;
    size_t user_size;

    int argc;
    char** argv;

} fossil_sys_asm_context_t;


/* ------------------------------------------------------
 * Lifecycle
 * ----------------------------------------------------- */

/* Initialize assembly subsystem */
bool fossil_sys_asm_init(void);

/* Shutdown subsystem */
void fossil_sys_asm_shutdown(void);


/* ------------------------------------------------------
 * Instruction stream handling
 * ----------------------------------------------------- */

/* Create instruction stream */
bool fossil_sys_asm_stream_create(
    fossil_sys_asm_arch_id_t arch,
    fossil_sys_asm_stream_t* out_stream);

/* Append instruction */
bool fossil_sys_asm_stream_add(
    fossil_sys_asm_stream_t* stream,
    const char* mnemonic,
    const char* operands);

/* Destroy stream */
void fossil_sys_asm_stream_destroy(
    fossil_sys_asm_stream_t* stream);


/* ------------------------------------------------------
 * Assembly / translation
 * ----------------------------------------------------- */

/* Assemble instruction stream → machine block */
bool fossil_sys_asm_assemble_stream(
    const fossil_sys_asm_stream_t* stream,
    fossil_sys_asm_backend_id_t backend,
    fossil_sys_asm_block_t* out_block);

/* Assemble raw text */
bool fossil_sys_asm_assemble_text(
    fossil_sys_asm_arch_id_t arch,
    fossil_sys_asm_backend_id_t backend,
    const char* source,
    fossil_sys_asm_block_t* out_block);

/* Free machine block */
void fossil_sys_asm_block_free(
    fossil_sys_asm_block_t* block);


/* ------------------------------------------------------
 * Execution
 * ----------------------------------------------------- */

/* Execute machine block */
int fossil_sys_asm_execute(
    const fossil_sys_asm_block_t* block,
    fossil_sys_asm_context_t* ctx);


/* ------------------------------------------------------
 * Introspection / diagnostics
 * ----------------------------------------------------- */

/* Dump block to hex string */
char* fossil_sys_asm_dump_hex(
    const fossil_sys_asm_block_t* block);

/* Get last assembler error */
const char* fossil_sys_asm_error(void);

/* Query backend availability */
bool fossil_sys_asm_backend_supported(
    fossil_sys_asm_backend_id_t backend);

/* Query architecture support */
bool fossil_sys_asm_arch_supported(
    fossil_sys_asm_arch_id_t arch);


#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_SYS_ASM_OPS_H */
