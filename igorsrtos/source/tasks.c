/*
 *
 *  Created on: Jul 16, 2019
 *      Author: Igor
 */


#include <rtos.h>
#include "tasks.h"

PRIVATE void schedule_callback(void);
PRIVATE void empty_task_callback(void* msg);

PRIVATE rtostask_t taskarray[RTOS_MAX_TASKS];
PRIVATE int task_current;
PRIVATE int task_max;

extern rtos_task_type_t __current_task;


int rtos_add_task(rtostask_t* task)
{
	if(task_max >= RTOS_MAX_TASKS - 1) {
		pr_err("rtos:tasks ovf");
		return -1;
	}
	int task_num = task_max;
	taskarray[task_max] = *task;
	task_max++;
	return task_num;
}

int rtos_putmsg_task(void*msg, int tsknum)
{
    if(tsknum<0 || tsknum >= task_max) {
        return tsknum;
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
	if(taskarray[task_current].function == NULL) {
		/* looks like NULL pointer
		 *  fix it! */
		taskarray[task_current].function = empty_task_callback;
	}
	taskarray[task_current].function(taskarray[task_current].msg);
	taskarray[task_current].msg = NULL;
	task_current++;
	if(task_current>= task_max) {
		task_current = 0;
	}
}

PRIVATE void empty_task_callback(void* msg)
{
	(void)msg;
}
