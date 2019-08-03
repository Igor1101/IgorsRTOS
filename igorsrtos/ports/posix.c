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
PRIVATE timer_t timerid;
PRIVATE struct sigevent sevp = {
		.sigev_notify = SIGEV_SIGNAL,
		.sigev_signo = SIGUSR1,
		.sigev_value.sival_ptr = &timerid
};
struct itimerspec timer_period = {
		.it_value.tv_sec = 0,
		.it_value.tv_nsec = 0,// <-- start from 0
		.it_interval.tv_sec = 0,
		.it_interval.tv_nsec = 0
};
PRIVATE struct sigaction sa = {
		.sa_flags = SA_SIGINFO,
		.sa_sigaction = __timer_has_expired,
};
PRIVATE void* _rtos_callback;
PRIVATE int _schedfreq;

void rtos_cpu_stop(void)
{
	/* nothing to do */
}

void _port_tick_timer_init(int schedfreq, void* callback)
{
	/* set interrupt */
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	/* set timer */
	timer_period.it_value.tv_sec = schedfreq / 1000000000;
	timer_period.it_value.tv_nsec = schedfreq - (schedfreq / 1000000000) * 1000000000;
	_schedfreq = schedfreq;
	timer_create(clkid, &sevp, &timerid);
	timer_settime(timerid, 0, &timer_period, NULL);
	_rtos_callback = callback;
}

PRIVATE void __timer_has_expired(union sigval timer_data)
{
    //printf("Timer expiration handler function; %d\n", *(int *) timer_data.sival_ptr);
	if(_rtos_callback != NULL)
		((void (*)(void))_rtos_callback)();
    _port_tick_timer_init(_schedfreq, _rtos_callback);
}
