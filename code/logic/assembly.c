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
 * Internal state
 * ====================================================== */

static char g_last_error[256] = {0};
static bool g_initialized = false;

/* ======================================================
 * Helpers
 * ====================================================== */

static void fossil_set_error(const char* msg)
{
    strncpy(g_last_error, msg, sizeof(g_last_error) - 1);
}

const char* fossil_sys_asm_error(void)
{
    return g_last_error[0] ? g_last_error : NULL;
}

/* ------------------------------------------------------
 * Executable memory helpers (W^X)
 * ----------------------------------------------------- */

static void* fossil_exec_alloc(size_t size)
{
#if defined(_WIN32)
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
    void* p = mmap(NULL, size,
                   PROT_READ | PROT_WRITE,
                   MAP_PRIVATE
#if defined(MAP_ANON)
                   | MAP_ANON
#else
                   | MAP_ANONYMOUS
#endif
                   , -1, 0);
    return (p == MAP_FAILED) ? NULL : p;
#endif
}

static void fossil_exec_make_rx(void* ptr, size_t size)
{
#if defined(_WIN32)
    DWORD old;
    VirtualProtect(ptr, size, PAGE_EXECUTE_READ, &old);
#else
    mprotect(ptr, size, PROT_READ | PROT_EXEC);
#endif
}

static void fossil_exec_free(void* ptr, size_t size)
{
#if defined(_WIN32)
    (void)size;
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    munmap(ptr, size);
#endif
}

static void fossil_exec_flush(void* ptr, size_t size)
{
#if defined(__GNUC__) || defined(__clang__)
    __builtin___clear_cache((char*)ptr, (char*)ptr + size);
#elif defined(_WIN32)
    FlushInstructionCache(GetCurrentProcess(), ptr, size);
#else
    (void)ptr; (void)size;
#endif
}

/* ======================================================
 * Lifecycle
 * ====================================================== */

bool fossil_sys_asm_init(void)
{
    g_initialized = true;
    return true;
}

void fossil_sys_asm_shutdown(void)
{
    g_initialized = false;
}

/* ======================================================
 * Stream handling
 * ====================================================== */

bool fossil_sys_asm_stream_create(
    fossil_sys_asm_arch_id_t arch,
    fossil_sys_asm_stream_t* out)
{
    if (!out) return false;

    memset(out, 0, sizeof(*out));
    out->arch = arch;
    out->id = "stream";

    return true;
}

bool fossil_sys_asm_stream_add(
    fossil_sys_asm_stream_t* s,
    const char* mnemonic,
    const char* operands)
{
    if (!s || !mnemonic) return false;

    size_t n = s->instruction_count + 1;

    fossil_sys_asm_instruction_t* tmp =
        realloc(s->instructions, n * sizeof(*tmp));

    if (!tmp) return false;

    s->instructions = tmp;

    tmp[n-1].id = "inst";
    tmp[n-1].mnemonic = mnemonic;
    tmp[n-1].operands = operands;

    s->instruction_count = n;
    return true;
}

void fossil_sys_asm_stream_destroy(
    fossil_sys_asm_stream_t* s)
{
    if (!s) return;
    free(s->instructions);
    memset(s, 0, sizeof(*s));
}

/* ======================================================
 * Hex parser (used by text assembler stub)
 * ====================================================== */

static int fossil_parse_hex(
    const char* src,
    uint8_t** out,
    size_t* out_size)
{
    size_t cap = strlen(src) + 1;
    uint8_t* buf = malloc(cap);
    if (!buf) return 0;

    size_t count = 0;

    while (*src) {
        while (*src && !isxdigit(*src)) src++;
        if (!*src) break;

        unsigned int b;
        if (sscanf(src, "%2x", &b) != 1) {
            free(buf);
            return 0;
        }

        buf[count++] = (uint8_t)b;
        while (isxdigit(*src)) src++;
    }

    *out = buf;
    *out_size = count;
    return 1;
}

/* ======================================================
 * Assembly stubs
 * ====================================================== */

bool fossil_sys_asm_assemble_text(
    fossil_sys_asm_arch_id_t arch,
    fossil_sys_asm_backend_id_t backend,
    const char* source,
    fossil_sys_asm_block_t* out)
{
    (void)arch;

    if (!source || !out) return false;

    uint8_t* buf;
    size_t size;

    if (!fossil_parse_hex(source, &buf, &size)) {
        fossil_set_error("hex parse failed");
        return false;
    }

    void* exec = fossil_exec_alloc(size);
    if (!exec) {
        free(buf);
        fossil_set_error("exec alloc failed");
        return false;
    }

    memcpy(exec, buf, size);
    free(buf);

    fossil_exec_make_rx(exec, size);
    fossil_exec_flush(exec, size);

    out->id = "block";
    out->arch = arch;
    out->backend = backend;
    out->code = exec;
    out->size = size;
    out->executable = true;

    return true;
}

bool fossil_sys_asm_assemble_stream(
    const fossil_sys_asm_stream_t* stream,
    fossil_sys_asm_backend_id_t backend,
    fossil_sys_asm_block_t* out)
{
    (void)backend;

    if (!stream || stream->instruction_count == 0)
        return false;

    fossil_set_error("stream assembler not implemented yet");
    return false;
}

/* ======================================================
 * Block lifecycle
 * ====================================================== */

void fossil_sys_asm_block_free(
    fossil_sys_asm_block_t* b)
{
    if (!b || !b->code) return;

    fossil_exec_free(b->code, b->size);
    memset(b, 0, sizeof(*b));
}

/* ======================================================
 * Execute
 * ====================================================== */

typedef int (*fossil_entry_fn)(int, char**);

int fossil_sys_asm_execute(
    const fossil_sys_asm_block_t* b,
    fossil_sys_asm_context_t* ctx)
{
    if (!b || !b->code || !b->executable)
        return -1;

    fossil_entry_fn fn = (fossil_entry_fn)b->code;

    if (!ctx)
        return fn(0, NULL);

    return fn(ctx->argc, ctx->argv);
}

/* ======================================================
 * Dump hex
 * ====================================================== */

char* fossil_sys_asm_dump_hex(
    const fossil_sys_asm_block_t* b)
{
    if (!b || !b->code || b->size == 0)
        return NULL;

    size_t len = b->size * 3 + 1;
    char* out = malloc(len);
    if (!out) return NULL;

    char* p = out;
    for (size_t i = 0; i < b->size; ++i) {
        sprintf(p, "%02X ", b->code[i]);
        p += 3;
    }
    *p = 0;

    return out;
}

/* ======================================================
 * Capability queries
 * ====================================================== */

bool fossil_sys_asm_backend_supported(
    fossil_sys_asm_backend_id_t backend)
{
    if (!backend) return false;

    return strcmp(backend, "native") == 0 ||
           strcmp(backend, "jit") == 0 ||
           strcmp(backend, "interpreter") == 0 ||
           strcmp(backend, "sandbox") == 0;
}

bool fossil_sys_asm_arch_supported(
    fossil_sys_asm_arch_id_t arch)
{
    if (!arch) return false;

#if defined(__x86_64__) || defined(_M_X64)
    return strcmp(arch, "x64") == 0;
#elif defined(__aarch64__)
    return strcmp(arch, "arm64") == 0;
#else
    return true;
#endif
}
