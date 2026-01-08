/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 * Daisy Seed Platform - Based on RIOT OS platform implementation
 */

#ifndef _PLATFORM_INTERNAL_H
#define _PLATFORM_INTERNAL_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef BH_PLATFORM_DAISY
#define BH_PLATFORM_DAISY
#endif

/* For runtime internal code, BH_MALLOC should map to wasm_runtime_malloc */
#undef BH_MALLOC
#undef BH_FREE
#define BH_MALLOC wasm_runtime_malloc
#define BH_FREE wasm_runtime_free

#define BH_APPLET_PRESERVED_STACK_SIZE (2 * 1024)

/* Default thread priority (unused in single-threaded AOT) */
#define BH_THREAD_DEFAULT_PRIORITY 7

/* Single-threaded AOT stubs - minimal types */
typedef int korp_tid;
typedef int korp_thread;

/* Mutex and condition variable stubs */
struct os_thread_wait_node;
typedef struct os_thread_wait_node *os_thread_wait_list;

typedef struct korp_mutex {
    int dummy;
} korp_mutex;

typedef struct korp_cond {
    int wait_list_lock;
    os_thread_wait_list thread_wait_list;
} korp_cond;

typedef struct {
    int dummy;
} korp_rwlock;

typedef unsigned int korp_sem;

#define os_printf printf
#define os_vprintf vprintf

/* The below types are used in platform_api_extension.h,
   we just define them to make the compiler happy */
typedef int os_file_handle;
typedef void *os_dir_stream;
typedef int os_raw_file_handle;
typedef int os_poll_file_handle;
typedef unsigned int os_nfds_t;
typedef int os_timespec;

/* Math functions */
double sqrt(double x);
double floor(double x);
double ceil(double x);
double fmin(double x, double y);
double fmax(double x, double y);
double rint(double x);
double fabs(double x);
double trunc(double x);
float sqrtf(float x);
float floorf(float x);
float ceilf(float x);
float fminf(float x, float y);
float fmaxf(float x, float y);
float rintf(float x);
float fabsf(float x);
float truncf(float x);

static inline os_file_handle
os_get_invalid_handle(void)
{
    return -1;
}

#endif /* end of _PLATFORM_INTERNAL_H */
