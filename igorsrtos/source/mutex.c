/*
 * mutex.c
 *
 *  Created on: Jul 27, 2019
 *      Author: igor
 */
#include <rtos.h>
#include <rtos/types.h>
#include "mutex.h"

extern rtos_task_type_t __current_task;
static rtosmutex_t mxbuf[RTOS_MUTEX_MAX_AMOUNT];
static int m_max_pointer = 0;

PRIVATE int find_mutex(rtosmutex_var_t variable);

BOOL rtos_mutex_exists(rtosmutex_var_t variable)
{
	if(find_mutex(variable) >= 0) {
		return TRUE;
	}
	return FALSE;
}

int rtos_mutex_declare(rtosmutex_var_t variable)
{
	if(m_max_pointer >= RTOS_MUTEX_MAX_AMOUNT) {
		pr_err("mutex err, declaration ovf");
		return RTOS_FAILURE;
	}
	if(rtos_mutex_exists(variable)) {
		pr_err("mutex err, mutex to the same variable");
		return RTOS_FAILURE;
	}
	int m_current = m_max_pointer;
	mxbuf[m_max_pointer].state = MUTEX_UNLOCKED;
	mxbuf[m_max_pointer].variable = variable;
	m_max_pointer++;
	return m_current;
}

BOOL rtos_mutex_num_locked(int mxnum)
{
	if(mxnum < 0|| mxnum >= m_max_pointer) {
		pr_err("mutex: fake descriptor");
		return FALSE;
	}
	if(mxbuf[mxnum].state == MUTEX_LOCKED) {
		return TRUE;
	}
	if(mxbuf[mxnum].state == MUTEX_DISABLED) {
		pr_err("mutex: working with disabled instance");
	}
	return FALSE;
}

BOOL rtos_mutex_locked(rtosmutex_var_t variable)
{
	int mxn = find_mutex(variable);
	if(mxn == RTOS_FAILURE) {
		pr_err("mutex: instance not found");
		return FALSE;
	}
	if(mxbuf[mxn].state == MUTEX_LOCKED) {
		return TRUE;
	}
	if(mxbuf[mxn].state == MUTEX_UNLOCKED) {
		return FALSE;
	}
	if(mxbuf[mxn].state == MUTEX_DISABLED) {
		pr_err("mutex: disabled instance access");
		return FALSE;
	}
	pr_err("mutex: unknown state, setting to disabled");
	mxbuf[mxn].state = MUTEX_DISABLED;
	return FALSE;
}

int rtos_mutex_unsaferemove(rtosmutex_var_t variable)
{
	while(rtos_mutex_locked(variable));
	int mxn = find_mutex(variable);
	if(mxn == RTOS_FAILURE) {
		pr_err("mutex: instance not found");
		return RTOS_FAILURE;
	}
	while(rtos_mutex_locked(variable));
	mxbuf[mxn].state = MUTEX_DISABLED;
	return RTOS_SUCCESS;
}

int rtos_mutex_lock(rtosmutex_var_t variable)
{
	while(rtos_mutex_locked(variable)) {
	}
	int mxn = find_mutex(variable);
	if(mxn == RTOS_FAILURE) {
		pr_err("mutex: instance not found");
		return RTOS_FAILURE;
	}
	/* lock for task */
	if(__current_task == IS_TASK) {
		if(!rtos_task_mutex_allowed(rtos_task_current(), variable)) {
			pr_err("mutex: current task not mutex member");
			return RTOS_FAILURE;
		}
		mxbuf[mxn].lock_t = IS_TASK;
		mxbuf[mxn].lock_inst = rtos_task_current();
	} else if(__current_task == IS_MAIN_THREAD) {
		mxbuf[mxn].lock_t = IS_MAIN_THREAD;
		mxbuf[mxn].lock_inst = 0;
	} else {
		return RTOS_FAILURE;
	}
	mxbuf[mxn].state = MUTEX_LOCKED;
	return RTOS_SUCCESS;
}

int rtos_mutex_unlock(rtosmutex_var_t variable)
{
	int mxn = find_mutex(variable);
	if(mxn == RTOS_FAILURE) {
		pr_err("mutex: instance not found");
		return RTOS_FAILURE;
	}
	if(mxbuf[mxn].state == MUTEX_UNLOCKED) {
		pr_err("mutex: is already unlocked");
		return RTOS_FAILURE;
	}
	if(__current_task != mxbuf[mxn].lock_t) {
		return RTOS_FAILURE;
	}
	if(__current_task == IS_TASK) {
		if(mxbuf[mxn].lock_inst != rtos_task_current()) {
			return RTOS_FAILURE;
		}
	}
	if(__current_task == IS_MAIN_THREAD) {
		if(mxbuf[mxn].lock_inst != 0) {
			return RTOS_FAILURE;
		}
	}
	mxbuf[mxn].state = MUTEX_UNLOCKED;
	return RTOS_SUCCESS;
}

PRIVATE int find_mutex(rtosmutex_var_t variable)
{
	int i;
	for(i=0; i<m_max_pointer; i++) {
		if((uptr)mxbuf[i].variable == (uptr)variable) {
			return i;
		}
	}
	return RTOS_FAILURE;
}

int rtos_mutex_get_instance(rtosmutex_t*mxp, rtosmutex_var_t variable)
{
	int mxn = find_mutex(variable);
	if(mxn == RTOS_FAILURE) {
		pr_err("mutex: instance not found");
		return RTOS_FAILURE;
	}
	if(mxp == NULL) {
		return RTOS_FAILURE;
	}
	*mxp = mxbuf[mxn];
	return RTOS_SUCCESS;
}
