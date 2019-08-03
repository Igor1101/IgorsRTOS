/*
 * rtos.c
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */
#include <tasks.h>
#include "rtos.h"

PRIVATE BOOL _initialized = FALSE;
rtos_task_type_t __current_task = IS_MAIN_THREAD;

PRIVATE void _rtos_tick_timer_callback(void);

void rtos_sleep(u32 time)
{
	rtos_thread_cur_freeze(time);
}
void rtos_init(void)
{
	if(rtos_is_initialized()) {
		pr_warn("try to initialize already initialized");
		return;
	}
	/* init tasks */
	if(RTOS_MAX_TASKS==0) {
		pr_err("rtos: opt fatal");
		return;
	}
	int i=0;
	/* init tasks */
	rtos_tasks_init();
	/* init timer */
	_port_tick_timer_init(RTOS_TASK_SCHEDULE_FREQ, _rtos_tick_timer_callback);
	_initialized = TRUE;
}

PRIVATE void _rtos_tick_timer_callback(void)
{
	_rtos_tasks_schedule_callback();
}



BOOL rtos_is_initialized(void)
{
	return _initialized;
}

rtos_task_type_t rtos_current_task(void)
{
	return __current_task;
}
