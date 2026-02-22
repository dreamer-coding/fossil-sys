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
#include "fossil/sys/assembly.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <sys/mman.h>
    #include <unistd.h>
#endif

/* ======================================================
 * Config
 * ====================================================== */

#define FOSSIL_ASM_MAX_SIZE (1024 * 1024) /* 1 MB safety cap */

/* ======================================================
 * Hash (FNV-1a for audit metadata)
 * ====================================================== */

static uint64_t fossil_hash_block(const uint8_t* data, size_t len) {
    uint64_t hash = 1469598103934665603ULL;
    for (size_t i = 0; i < len; ++i) {
        hash ^= data[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

/* ======================================================
 * Executable memory handling (W^X)
 * ====================================================== */

static void* fossil_exec_alloc_rw(size_t size) {
#if defined(_WIN32)
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
    void* ptr = mmap(NULL, size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);
    return (ptr == MAP_FAILED) ? NULL : ptr;
#endif
}

static void fossil_exec_make_rx(void* ptr, size_t size) {
#if defined(_WIN32)
    DWORD old;
    VirtualProtect(ptr, size, PAGE_EXECUTE_READ, &old);
#else
    mprotect(ptr, size, PROT_READ | PROT_EXEC);
#endif
}

static void fossil_exec_free(void* ptr, size_t size) {
#if defined(_WIN32)
    (void)size;
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    munmap(ptr, size);
#endif
}

/* Flush instruction cache when needed */
static void fossil_exec_flush(void* ptr, size_t size) {
#if defined(__GNUC__) || defined(__clang__)
    __builtin___clear_cache((char*)ptr, (char*)ptr + size);
#elif defined(_WIN32)
    FlushInstructionCache(GetCurrentProcess(), ptr, size);
#else
    (void)ptr;
    (void)size;
#endif
}

/* ======================================================
 * Hex parser
 * Accepts:
 *   B8 01 00 00 00 C3
 *   0xB8,0x01,0xC3
 *   newline separated
 * ====================================================== */

static int fossil_parse_hex(const char* src, uint8_t** out_buf, size_t* out_size) {
    size_t cap = strlen(src) + 1;
    if (cap > FOSSIL_ASM_MAX_SIZE) return 0;

    uint8_t* buf = malloc(cap);
    if (!buf) return 0;

    size_t count = 0;
    const char* p = src;

    while (*p) {
        while (*p && !isxdigit(*p)) p++;
        if (!*p) break;

        unsigned int byte;
        if (sscanf(p, "%2x", &byte) != 1) {
            free(buf);
            return 0;
        }

        buf[count++] = (uint8_t)byte;

        while (isxdigit(*p)) p++;
    }

    *out_buf = buf;
    *out_size = count;
    return 1;
}

/* ======================================================
 * Host architecture detection
 * ====================================================== */

static fossil_sys_asm_arch_t fossil_host_arch(void) {
#if defined(__x86_64__) || defined(_M_X64)
    return FOSSIL_ASM_TYPE_X64;
#elif defined(__i386__) || defined(_M_IX86)
    return FOSSIL_ASM_TYPE_X86;
#elif defined(__aarch64__)
    return FOSSIL_ASM_TYPE_ARM64;
#elif defined(__arm__)
    return FOSSIL_ASM_TYPE_ARM;
#else
    return FOSSIL_ASM_TYPE_NONE;
#endif
}

/* ======================================================
 * Assemble
 * ====================================================== */

bool fossil_sys_asm_assemble(
    fossil_sys_asm_arch_t arch,
    const char* source,
    fossil_sys_asm_block_t* out_block)
{
    if (!source || !out_block) return false;

    /* reject incompatible arch for now */
    fossil_sys_asm_arch_t host = fossil_host_arch();
    if (arch != host) {
        /* future: allow cross-arch blobs for serialization */
        return false;
    }

    uint8_t* parsed = NULL;
    size_t parsed_size = 0;

    if (!fossil_parse_hex(source, &parsed, &parsed_size))
        return false;

    if (parsed_size == 0 || parsed_size > FOSSIL_ASM_MAX_SIZE) {
        free(parsed);
        return false;
    }

    void* exec = fossil_exec_alloc_rw(parsed_size);
    if (!exec) {
        free(parsed);
        return false;
    }

    memcpy(exec, parsed, parsed_size);
    free(parsed);

    fossil_exec_make_rx(exec, parsed_size);
    fossil_exec_flush(exec, parsed_size);

    out_block->id   = "assembled";
    out_block->arch = arch;
    out_block->code = exec;
    out_block->size = parsed_size;

    return true;
}

/* ======================================================
 * Free
 * ====================================================== */

void fossil_sys_asm_free(fossil_sys_asm_block_t* block) {
    if (!block || !block->code) return;
    fossil_exec_free(block->code, block->size);
    block->code = NULL;
    block->size = 0;
}

/* ======================================================
 * Execute
 * ====================================================== */

typedef int (*fossil_entry_fn)(int, char**);

int fossil_sys_asm_execute(const fossil_sys_asm_block_t* block, int argc, char** argv) {
    if (!block || !block->code) return -1;

    fossil_entry_fn fn = (fossil_entry_fn)block->code;
    return fn(argc, argv);
}

/* ======================================================
 * Dump hex
 * ====================================================== */

char* fossil_sys_asm_dump_hex(const fossil_sys_asm_block_t* block) {
    if (!block || !block->code || block->size == 0) return NULL;

    size_t out_len = block->size * 3 + 1;
    char* out = malloc(out_len);
    if (!out) return NULL;

    char* p = out;
    for (size_t i = 0; i < block->size; ++i) {
        sprintf(p, "%02X ", block->code[i]);
        p += 3;
    }

    *p = '\0';
    return out;
}

/* ======================================================
 * Optional: expose block hash for auditing
 * ====================================================== */

uint64_t fossil_sys_asm_hash(const fossil_sys_asm_block_t* block) {
    if (!block || !block->code) return 0;
    return fossil_hash_block(block->code, block->size);
}
