/*
 *
 *  Created on: Jul 16, 2019
 *      Author: Igor
 */


#include <rtos.h>
#include <mutex.h>
#include <string.h>
#include "tasks.h"

PRIVATE void empty_task_callback(void* msg);

PRIVATE rtostask_t taskarray[RTOS_MAX_TASKS];
PRIVATE int task_current;
PRIVATE int task_max;

extern rtos_task_type_t __current_task;


int rtos_add_task(rtostask_t* task)
{
	if(task_max >= RTOS_MAX_TASKS - 1) {
		pr_err("tasks ovf");
		return -1;
	}
	int task_num = task_max;
	memcpy(&taskarray[task_max], task, sizeof(rtostask_t));
	taskarray[task_max].mutexamount = 0;
	task_max++;
	return task_num;
}

int rtos_task_putmsg(int tsknum, void*msg)
{
    if(tsknum<0 || tsknum >= task_max) {
    	pr_err("task: invalid desc");
        return RTOS_FAILURE;
    }
    taskarray[tsknum].msg = msg;
    return tsknum;
}


void rtos_stop(void)
{
	/* stop timer here */
	/*
	 * TODO
	if(rtos_is_initialized())
		*/
}

void rtos_start(void)
{
	/* start tick timer here
	 * TODO
	 */
	/*if(rtos_is_initialized())*/
}

void rtos_tasks_init(void)
{
	int i;
	for(i=0; i<RTOS_MAX_TASKS; i++) {
		taskarray[i].function = empty_task_callback;
		taskarray[i].msg = NULL;
	}
	task_current = 0;
	task_max = 0;
}

void _rtos_tasks_schedule_callback(void)
{
	/* current thread changes */
	if(thread_current.state == FREEZED|| thread_current.state == FREEZED_CONTEXT_SAVED) {
		thread_current.time_freezed -= RTOS_TASK_SCHEDULE_FREQ;
	}
	if(thread_current.time_freezed <= 0) {
		thread_current.state = RUNNING;
	}
	if(task_max == 0) {
		return;/* no tasks running */
	}
	if(taskarray[task_current].function == NULL) {
		/* looks like NULL pointer
		 *  fix it! */
		taskarray[task_current].function = empty_task_callback;
	}
	/* run task if only it has no locked mutexes
	 * by other tasks/processes */
	if(!rtos_task_mutexes_locked(task_current)) {
		__current_task = IS_TASK;
		taskarray[task_current].function(taskarray[task_current].msg);
		__current_task = IS_MAIN_THREAD;
	}
	taskarray[task_current].msg = NULL;
	task_current++;
	if(task_current >= task_max) {
		task_current = 0;
	}
}

BOOL rtos_task_mutex_allowed(int tskdesc, rtosmutex_var_t mx)
{
    if(tskdesc<0 || tskdesc >= task_max) {
    	pr_err("task: invalid desc");
        return FALSE;
    }
 	int i;
	for(i=0; i<taskarray[tskdesc].mutexamount; i++) {
		if(taskarray[tskdesc].mutexes[i] == mx) {
			return TRUE;
		}
	}
	return FALSE;
}

int rtos_task_current(void)
{
	if(__current_task != IS_TASK) {
		return RTOS_FAILURE;
	}
	return task_current;
}

int rtos_task_allow_mutex(int tskdesc, rtosmutex_var_t mx)
{
	if(tskdesc<0 || tskdesc >= task_max) {
    	pr_err("task: invalid desc");
        return RTOS_FAILURE;
    }
	if(taskarray[tskdesc].mutexamount >= RTOS_TASK_MAX_MUTEXES) {
		return RTOS_FAILURE;
	}
	taskarray[tskdesc].mutexes[taskarray[tskdesc].mutexamount] = mx;
	taskarray[tskdesc].mutexamount++;
	return RTOS_SUCCESS;
}

BOOL rtos_task_mutexes_locked(int tskdesc)
{
	static rtosmutex_t mxcopy;
	if(tskdesc<0 || tskdesc >= task_max) {
    	pr_err("task mutex locked: invalid desc");
        return RTOS_FAILURE;
    }
	int i;
	for(i=0; i<taskarray[tskdesc].mutexamount; i++) {
		rtos_assert( rtos_mutex_get_instance(&mxcopy,
						taskarray[tskdesc].mutexes[i]) == RTOS_SUCCESS);
		if(mxcopy.state == MUTEX_LOCKED &&
				(mxcopy.lock_t != IS_TASK ||
				mxcopy.lock_inst != tskdesc)
				) {
			return TRUE;
		}
	}
	return FALSE;
}

PRIVATE void empty_task_callback(void* msg)
{
	(void)msg;
}
