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

PRIVATE const clockid_t clkid = CLOCK_REALTIME;
PRIVATE struct sigevent sevp = {
		.sigev_notify = SIGEV_SIGNAL
};
PRIVATE timer_t timerid;
void rtos_cpu_stop(void)
{
	/* nothing to do */
}

void _port_tick_timer_init(int schedfreq, void* callback)
{
	timer_create(clkid, &sevp, timerid);
}
