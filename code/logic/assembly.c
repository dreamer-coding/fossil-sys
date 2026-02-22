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

/* ------------------------------------------------------
 * Executable memory allocation macros
 * ----------------------------------------------------- */
#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#define FOSSIL_EXEC_ALLOC(sz) VirtualAlloc(NULL, sz, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE)
#define FOSSIL_EXEC_FREE(p,sz) VirtualFree(p, 0, MEM_RELEASE)

#else

#include <sys/mman.h>
#include <unistd.h>

#if !defined(MAP_ANON) && defined(MAP_ANONYMOUS)
#define MAP_ANON MAP_ANONYMOUS
#endif

#define FOSSIL_EXEC_ALLOC(sz) mmap(NULL, sz, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0)
#define FOSSIL_EXEC_FREE(p,sz) munmap(p, sz)

#endif

/* ------------------------------------------------------
 * Internal helper: write temp file
 * ----------------------------------------------------- */
static bool fossil_write_file(const char* path, const void* data, size_t size) {
    FILE* f = fopen(path, "wb");
    if (!f) return false;
    fwrite(data, 1, size, f);
    fclose(f);
    return true;
}

/* ------------------------------------------------------
 * Assemble text using system assembler
 * Strategy:
 * 1. Write source to temp file
 * 2. Invoke assembler (nasm/clang/gcc)
 * 3. Read resulting object/raw binary
 * ----------------------------------------------------- */
bool fossil_sys_asm_assemble(
    fossil_sys_asm_arch_t arch,
    const char* source,
    fossil_sys_asm_block_t* out_block)
{
    if (!source || !out_block) return false;

    const char* src_path = "fossil_tmp.asm";
    const char* bin_path = "fossil_tmp.bin";

    if (!fossil_write_file(src_path, source, strlen(source)))
        return false;

    char cmd[512] = {0};

#if defined(_WIN32) || defined(_WIN64)
    /* Windows: assume NASM available */
    snprintf(cmd, sizeof(cmd),
        "nasm -f bin %s -o %s", src_path, bin_path);
#else
    /* POSIX: try NASM first, fallback to clang inline assembly */
    snprintf(cmd, sizeof(cmd),
        "nasm -f bin %s -o %s 2>/dev/null || "
        "clang -x assembler %s -o %s",
        src_path, bin_path, src_path, bin_path);
#endif

    if (system(cmd) != 0)
        return false;

    /* read binary */
    FILE* f = fopen(bin_path, "rb");
    if (!f) return false;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t* exec_mem = (uint8_t*)FOSSIL_EXEC_ALLOC(size);
    if (!exec_mem) {
        fclose(f);
        return false;
    }

    fread(exec_mem, 1, size, f);
    fclose(f);

    out_block->id   = source;
    out_block->arch = arch;
    out_block->code = exec_mem;
    out_block->size = size;

    return true;
}

/* ------------------------------------------------------
 * Free executable block
 * ----------------------------------------------------- */
void fossil_sys_asm_free(fossil_sys_asm_block_t* block) {
    if (!block || !block->code) return;
    FOSSIL_EXEC_FREE(block->code, block->size);
    block->code = NULL;
    block->size = 0;
}

/* ------------------------------------------------------
 * Execute block
 * Convention:
 * code must be a function:
 * int func(int argc, char** argv)
 * ----------------------------------------------------- */
int fossil_sys_asm_execute(
    const fossil_sys_asm_block_t* block,
    int argc,
    char** argv)
{
    if (!block || !block->code || block->size == 0)
        return -1;

    /* Ensure instruction cache is coherent after writing code */
#if defined(__GNUC__) || defined(__clang__)
    __builtin___clear_cache(
        (char*)block->code,
        (char*)block->code + block->size);
#elif defined(_MSC_VER)
    /* Microslop has no direct builtin; rely on OS APIs if needed */
    /* FlushInstructionCache(GetCurrentProcess(), block->code, block->size); */
#endif

    /* Function pointer cast isolated for clarity */
    typedef int (*fossil_entry_fn)(int, char**);

    fossil_entry_fn fn;
    memcpy(&fn, &block->code, sizeof(fn));

    if (!fn)
        return -2;

    return fn(argc, argv);
}

/* ------------------------------------------------------
 * Dump code to hex string
 * Caller must free returned string
 * ----------------------------------------------------- */
char* fossil_sys_asm_dump_hex(const fossil_sys_asm_block_t* block) {
    if (!block || !block->code || block->size == 0) return NULL;

    const char* hex = "0123456789ABCDEF";
    size_t out_sz = block->size * 2 + 1;
    char* out = (char*)malloc(out_sz);
    if (!out) return NULL;

    for (size_t i = 0; i < block->size; ++i) {
        out[i*2]   = hex[(block->code[i] >> 4) & 0xF];
        out[i*2+1] = hex[block->code[i] & 0xF];
    }
    out[out_sz-1] = '\0';
    return out;
}
