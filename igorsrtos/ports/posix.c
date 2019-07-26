/*
 * posix.c
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */
#include <signal.h>
#include <time.h>
#include "posix.h"
#include <rtos/types.h>

PRIVATE void __timer_has_expired(union sigval timer_data);
PRIVATE const clockid_t clkid = CLOCK_REALTIME;
PRIVATE struct sigevent sevp = {
		.sigev_notify = SIGEV_THREAD,
		.sigev_notify_function = __timer_has_expired,
		.sigev_notify_attributes = NULL
};
PRIVATE timer_t timerid;
struct itimerspec timer_period = {
		.it_value.tv_sec = 0,
		.it_value.tv_nsec = 0,// <-- start from 0
		.it_interval.tv_sec = 0,
		.it_interval.tv_nsec = 0
};
PRIVATE void* _rtos_callback;
PRIVATE int _schedfreq;

void rtos_cpu_stop(void)
{
	/* nothing to do */
}

void _port_tick_timer_init(int schedfreq, void* callback)
{
	timer_period.it_value.tv_nsec = schedfreq ;
	_schedfreq = schedfreq;
	pr_rtos("creating timer");
	timer_create(clkid, &sevp, &timerid);
	pr_rtos("setting time");
	timer_settime(timerid, 0, &timer_period, NULL);
	_rtos_callback = callback;
}

PRIVATE void __timer_has_expired(union sigval timer_data)
{
    //printf("Timer expiration handler function; %d\n", *(int *) timer_data.sival_ptr);
	puts("timer expired");
    ((void (*)(void))_rtos_callback)();
    _port_tick_timer_init(_schedfreq, _rtos_callback);
}
