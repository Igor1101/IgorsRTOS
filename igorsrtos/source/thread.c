/*
 * thread.c
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */

#include <rtos.h>
#include "thread.h"

rtos_thread_t thread_current;

void rtos_thread_cur_freeze(i32 time)
{
	thread_current.state = FREEZED;
	thread_current.time_freezed = time;
	while(thread_current.state == FREEZED) {
		rtos_cpu_stop();
	}
}
