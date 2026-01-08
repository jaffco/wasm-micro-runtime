/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 * Daisy Seed Platform - Memory allocation and platform initialization
 */

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

/* External memory allocator from Daisy SDRAM */
extern void *sdram_alloc(size_t size);
extern void sdram_dealloc(void *ptr);
extern void *sdram_realloc(void *ptr, size_t size);
extern void *sdram_calloc(size_t nmemb, size_t size);

void *
os_malloc(unsigned size)
{
    return sdram_alloc(size);
}

void *
os_realloc(void *ptr, unsigned size)
{
    return sdram_realloc(ptr, size);
}

void
os_free(void *ptr)
{
    sdram_dealloc(ptr);
}

int
os_dumps_proc_mem_info(char *out, unsigned int size)
{
    /* Not implemented for embedded system */
    return -1;
}

void *
os_mmap(void *hint, size_t size, int prot, int flags, os_file_handle file)
{
    /* Just allocate memory - no actual memory mapping on bare metal */
    if ((size_t)size == size)
        return os_malloc((unsigned)size);
    return NULL;
}

void
os_munmap(void *addr, size_t size)
{
    return os_free(addr);
}

int
os_mprotect(void *addr, size_t size, int prot)
{
    /* No memory protection on bare metal - always succeed */
    return 0;
}

void
os_dcache_flush(void)
{
    /* Flush data cache on STM32H7 */
    SCB_CleanDCache();
}

void
os_icache_flush(void *start, size_t len)
{
    /* Invalidate instruction cache on STM32H7 
     * This is critical for AOT code execution from SDRAM */
    SCB_InvalidateICache();
}

int
bh_platform_init(void)
{
    /* Platform already initialized by libDaisy */
    return 0;
}

void
bh_platform_destroy(void)
{
    /* Nothing to destroy */
}

int
os_getpagesize(void)
{
    /* Return a reasonable page size for embedded system */
    return 4096;
}

void *
os_mremap(void *old_addr, size_t old_size, size_t new_size)
{
    /* Not supported on bare metal - return NULL to trigger allocation elsewhere */
    return NULL;
}

uint8 *
os_thread_get_stack_boundary(void)
{
    /* Return NULL - not tracking stack boundaries in single-threaded AOT */
    return NULL;
}

void
os_thread_jit_write_protect_np(bool enabled)
{
    /* Not used in AOT-only mode */
    (void)enabled;
}

