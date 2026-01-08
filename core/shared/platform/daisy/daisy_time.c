/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 * Daisy Seed Platform - Time functions
 */

#include "platform_api_vmcore.h"

/* External function from STM32 HAL - gets system tick in milliseconds */
extern unsigned long HAL_GetTick(void);

uint64
os_time_get_boot_us(void)
{
    /* HAL_GetTick returns milliseconds, convert to microseconds */
    return (uint64)HAL_GetTick() * 1000ULL;
}

uint64
os_time_thread_cputime_us(void)
{
    /* Single-threaded - same as boot time */
    return os_time_get_boot_us();
}

void
os_usleep(uint32 usec)
{
    /* Simple busy-wait delay
     * TODO: Could use HAL_Delay for ms-level delays */
    uint64 start = os_time_get_boot_us();
    while ((os_time_get_boot_us() - start) < usec) {
        /* Busy wait */
    }
}
