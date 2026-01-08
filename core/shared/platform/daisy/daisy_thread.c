/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 * Daisy Seed Platform - Thread stubs (single-threaded AOT)
 */

#include "platform_api_vmcore.h"
#include "platform_api_extension.h"

/* Single-threaded AOT doesn't need real threading,
   but WAMR expects these functions to exist */

int
os_mutex_init(korp_mutex *mutex)
{
    if (!mutex)
        return BHT_ERROR;
    mutex->dummy = 0;
    return BHT_OK;
}

int
os_mutex_destroy(korp_mutex *mutex)
{
    if (!mutex)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_mutex_lock(korp_mutex *mutex)
{
    if (!mutex)
        return BHT_ERROR;
    /* Single-threaded - always succeeds */
    return BHT_OK;
}

int
os_mutex_unlock(korp_mutex *mutex)
{
    if (!mutex)
        return BHT_ERROR;
    /* Single-threaded - always succeeds */
    return BHT_OK;
}

int
os_cond_init(korp_cond *cond)
{
    if (!cond)
        return BHT_ERROR;
    cond->thread_wait_list = NULL;
    return BHT_OK;
}

int
os_cond_destroy(korp_cond *cond)
{
    if (!cond)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_cond_wait(korp_cond *cond, korp_mutex *mutex)
{
    /* Single-threaded - shouldn't actually wait */
    return BHT_OK;
}

int
os_cond_reltimedwait(korp_cond *cond, korp_mutex *mutex, uint64 useconds)
{
    /* Single-threaded - shouldn't actually wait */
    return BHT_OK;
}

int
os_cond_signal(korp_cond *cond)
{
    if (!cond)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_cond_broadcast(korp_cond *cond)
{
    if (!cond)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_sem_init(korp_sem *sem, unsigned int count)
{
    if (!sem)
        return BHT_ERROR;
    *sem = count;
    return BHT_OK;
}

int
os_sem_destroy(korp_sem *sem)
{
    if (!sem)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_sem_wait(korp_sem *sem)
{
    if (!sem)
        return BHT_ERROR;
    /* Single-threaded - decrement only */
    if (*sem > 0) {
        (*sem)--;
        return BHT_OK;
    }
    return BHT_ERROR;
}

int
os_sem_reltimedwait(korp_sem *sem, uint64 useconds)
{
    return os_sem_wait(sem);
}

int
os_sem_post(korp_sem *sem)
{
    if (!sem)
        return BHT_ERROR;
    (*sem)++;
    return BHT_OK;
}

int
os_rwlock_init(korp_rwlock *lock)
{
    if (!lock)
        return BHT_ERROR;
    lock->dummy = 0;
    return BHT_OK;
}

int
os_rwlock_rdlock(korp_rwlock *lock)
{
    if (!lock)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_rwlock_wrlock(korp_rwlock *lock)
{
    if (!lock)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_rwlock_unlock(korp_rwlock *lock)
{
    if (!lock)
        return BHT_ERROR;
    return BHT_OK;
}

int
os_rwlock_destroy(korp_rwlock *lock)
{
    if (!lock)
        return BHT_ERROR;
    return BHT_OK;
}

/* Thread creation stubs - not used in AOT but may be referenced */
int
os_thread_create(korp_tid *tid, thread_start_routine_t start, void *arg,
                 unsigned int stack_size)
{
    /* Single-threaded AOT doesn't create threads */
    return BHT_ERROR;
}

int
os_thread_create_with_prio(korp_tid *tid, thread_start_routine_t start,
                            void *arg, unsigned int stack_size, int prio)
{
    return BHT_ERROR;
}

korp_tid
os_self_thread(void)
{
    return 0;
}

int
os_thread_join(korp_tid thread, void **retval)
{
    return BHT_OK;
}

int
os_thread_detach(korp_tid thread)
{
    return BHT_OK;
}

void
os_thread_exit(void *retval)
{
    /* Nothing to do */
}

void *
os_thread_get_data(void)
{
    return NULL;
}

void
os_thread_set_data(void *data)
{
    /* Nothing to do */
}
