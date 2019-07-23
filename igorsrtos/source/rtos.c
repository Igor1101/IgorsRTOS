/*
 * rtos.c
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */
#include "rtos.h"

PRIVATE BOOL _initialized = FALSE;

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
	//tick_timer_init(RTOS_SCHEDULE_FREQ, schedule_callback);
	_initialized = TRUE;
}



BOOL rtos_is_initialized(void)
{
	return _initialized;
}
