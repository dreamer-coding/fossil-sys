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
#include "fossil/sys/memory.h"
#include <stdlib.h> // Needed for posix_memalign
#include <string.h>
#include <stdio.h>

// Internal counters for memory stats (optional, for debug)
static size_t g_alloc_count = 0;
static size_t g_alloc_bytes = 0;


// ----------------------- Aligned Memory -----------------------

fossil_sys_memory_t fossil_sys_memory_alloc(size_t size) {
    if (size == 0) {
         fprintf(stderr, "Error: fossil_sys_memory_alloc() - Cannot allocate zero bytes.\n");
        return NULL;
    }
    
    fossil_sys_memory_t ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_alloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

fossil_sys_memory_t fossil_sys_memory_realloc(fossil_sys_memory_t ptr, size_t size) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: fossil_sys_memory_realloc() - Pointer is NULL.\n");
        return NULL;
    }

    fossil_sys_memory_t new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0) {
        fprintf(stderr, "Error: fossil_sys_memory_realloc() - Memory reallocation failed.\n");
        return NULL;
    }
    return new_ptr;
}

fossil_sys_memory_t fossil_sys_memory_calloc(size_t num, size_t size) {
    if (num == 0 || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_calloc() - Cannot allocate zero elements or zero bytes.\n");
        return NULL;
    }

    fossil_sys_memory_t ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_calloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

fossil_sys_memory_t fossil_sys_memory_init(fossil_sys_memory_t ptr, size_t size, int32_t value) {
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_init() - Pointer is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_init() - Cannot initialize zero bytes.\n");
        return NULL;
    }

    return memset(ptr, value, size);
}

void fossil_sys_memory_free(fossil_sys_memory_t ptr) {
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_free() - Pointer is NULL.\n");
        return;
    }
    free(ptr); // No need for NULL check, free() already handles NULL.
}

fossil_sys_memory_t fossil_sys_memory_copy(fossil_sys_memory_t dest, const fossil_sys_memory_t src, size_t size) {
    if (!dest || !src) {
        fprintf(stderr, "Error: fossil_sys_memory_copy() - Source or destination is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_copy() - Cannot copy zero bytes.\n");
        return NULL;
    }
    
    return memcpy(dest, src, size);
}

fossil_sys_memory_t fossil_sys_memory_set(fossil_sys_memory_t ptr, int32_t value, size_t size) {
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_set() - Pointer is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_set() - Cannot set zero bytes.\n");
        return NULL;
    }
    
    return memset(ptr, value, size);
}

fossil_sys_memory_t fossil_sys_memory_dup(const fossil_sys_memory_t src, size_t size) {
    if (!src || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_dup() - Invalid source or zero size.\n");
        return NULL;
    }

    fossil_sys_memory_t dest = fossil_sys_memory_alloc(size);
    if (!dest) {
        return NULL;  // Error already handled in fossil_sys_memory_alloc
    }

    return memcpy(dest, src, size);
}

void fossil_sys_memory_zero(fossil_sys_memory_t ptr, size_t size) {
    if (!ptr || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_zero() - Invalid pointer or zero size.\n");
        return;
    }
    
    memset(ptr, 0, size);
}

int fossil_sys_memory_compare(const fossil_sys_memory_t ptr1, const fossil_sys_memory_t ptr2, size_t size) {
    if (!ptr1 || !ptr2 || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_compare() - Invalid pointers or zero size.\n");
        return -1;  // Return -1 for invalid input
    }

    return memcmp(ptr1, ptr2, size);
}

fossil_sys_memory_t fossil_sys_memory_move(fossil_sys_memory_t dest, const fossil_sys_memory_t src, size_t size) {
    if (!dest || !src || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_move() - Invalid source or destination pointers, or zero size.\n");
        return NULL;
    }

    return memmove(dest, src, size);
}

fossil_sys_memory_t fossil_sys_memory_resize(fossil_sys_memory_t ptr, size_t old_size, size_t new_size) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: fossil_sys_memory_resize() - Pointer is NULL.\n");
        return NULL;
    }

    if (new_size == 0) {
        fossil_sys_memory_free(ptr);
        return NULL;
    }

    // allocate new buffer
    fossil_sys_memory_t new_ptr = malloc(new_size);
    if (!new_ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_resize() - Memory allocation failed.\n");
        return ptr; // keep old buffer
    }

    // copy the smaller of old/new size
    size_t copy_size = (new_size < old_size) ? new_size : old_size;
    memcpy(new_ptr, ptr, copy_size);

    // free old memory
    fossil_sys_memory_free(ptr);

    return new_ptr;
}

bool fossil_sys_memory_is_valid(const fossil_sys_memory_t ptr) {
    if (!ptr) {
        return false;
    }
    // Optional: Add more validation logic if needed, but normally you'd rely on the caller to manage validity.
    return true;
}

// ----------------------- Aligned Memory -----------------------

fossil_sys_memory_t fossil_sys_memory_aligned_alloc(size_t size, size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
        fprintf(stderr, "Error: fossil_sys_memory_aligned_alloc() - Alignment must be a power of two.\n");
        return NULL;
    }

    void *ptr = NULL;
#if defined(_MSC_VER)
    ptr = _aligned_malloc(size, alignment);
    if (!ptr) {
        fprintf(stderr, "Error: fossil_sys_memory_aligned_alloc() - Aligned allocation failed.\n");
        return NULL;
    }
#else
    if (posix_memalign(&ptr, alignment, size) != 0) {
        fprintf(stderr, "Error: fossil_sys_memory_aligned_alloc() - Aligned allocation failed.\n");
        return NULL;
    }
#endif

    g_alloc_count++;
    g_alloc_bytes += size;
    return ptr;
}

void fossil_sys_memory_aligned_free(fossil_sys_memory_t ptr) {
    if (!ptr) return;

#if defined(_MSC_VER)
    _aligned_free(ptr);
#else
    free(ptr);
#endif
    // Note: g_alloc_count and g_alloc_bytes tracking could be refined with actual size bookkeeping
}

// ----------------------- Memory Fill -----------------------

fossil_sys_memory_t fossil_sys_memory_fill(fossil_sys_memory_t ptr,
                                           const void *pattern,
                                           size_t pattern_size,
                                           size_t total_size) {
    if (!ptr || !pattern || pattern_size == 0 || total_size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_fill() - Invalid arguments.\n");
        return NULL;
    }

    uint8_t *dst = (uint8_t *)ptr;
    size_t offset = 0;
    while (offset + pattern_size <= total_size) {
        memcpy(dst + offset, pattern, pattern_size);
        offset += pattern_size;
    }
    // Copy remaining bytes if any
    if (offset < total_size) {
        memcpy(dst + offset, pattern, total_size - offset);
    }
    return ptr;
}

// ----------------------- Secure Zero -----------------------

void fossil_sys_memory_secure_zero(fossil_sys_memory_t ptr, size_t size) {
    if (!ptr) return;
#if defined(_MSC_VER)
    SecureZeroMemory(ptr, size);
#elif defined(__GNUC__) || defined(__clang__)
    volatile uint8_t *p = (volatile uint8_t *)ptr;
    while (size--) *p++ = 0;
#else
    memset(ptr, 0, size); // Fallback (not guaranteed secure)
#endif
}

// ----------------------- Swap Memory -----------------------

void fossil_sys_memory_swap(fossil_sys_memory_t a, fossil_sys_memory_t b, size_t size) {
    if (!a || !b || size == 0) {
        fprintf(stderr, "Error: fossil_sys_memory_swap() - Invalid arguments.\n");
        return;
    }

    uint8_t *pa = (uint8_t *)a;
    uint8_t *pb = (uint8_t *)b;
    for (size_t i = 0; i < size; i++) {
        uint8_t tmp = pa[i];
        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

// ----------------------- Find Memory -----------------------

void *fossil_sys_memory_find(const fossil_sys_memory_t ptr, uint8_t value, size_t size) {
    if (!ptr || size == 0) return NULL;

    uint8_t *p = (uint8_t *)ptr;
    for (size_t i = 0; i < size; i++) {
        if (p[i] == value) return p + i;
    }
    return NULL;
}

// ----------------------- strdup -----------------------

char *fossil_sys_memory_strdup(const char *str) {
    if (!str) {
        fprintf(stderr, "Error: fossil_sys_memory_strdup() - NULL pointer passed.\n");
        return NULL;
    }

    size_t len = strlen(str) + 1;
    char *copy = (char *)fossil_sys_memory_alloc(len);
    memcpy(copy, str, len);
    return copy;
}

// ----------------------- Memory Stats -----------------------

void fossil_sys_memory_stats(size_t *out_allocs, size_t *out_bytes) {
    if (out_allocs) *out_allocs = g_alloc_count;
    if (out_bytes) *out_bytes = g_alloc_bytes;
}
