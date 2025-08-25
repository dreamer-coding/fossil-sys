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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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
