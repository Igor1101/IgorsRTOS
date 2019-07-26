/*
 * posix.h
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */

#ifndef IGORSRTOS_PORTS_POSIX_H_
#define IGORSRTOS_PORTS_POSIX_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
/* typedefs */
/* process specific */
typedef struct {
	/* TODO */
}context_t;

#ifdef __unix__
#include <unistd.h>
#else
#warning "doesn`t look like unix system "
#endif
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
/* define here RTOS_PORT_NAME port##_port_version */
#ifndef _POSIX_VERSION
#define _POSIX_VERSION 0
#endif
#if (_POSIX_C_SOURCE <= 199309L)
#warning "DEPRECATED POSIX VERSION"
#endif
#define RTOS_PORT_NAME "POSIX" STR(_POSIX_VERSION)
/* define here printing function (or implement it) */
#define pr_rtos(...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr,"\n\r");} while(0)
/* rtos timing */
/* rtos Sec per timer counts */
#define TIMER_S(X) (1000*1000*1000*(X))
#define TIMER_MS(X) (1000*1000*(X))
#define TIMER_MKS(X) (1000*(X))

/* functions you need implement */
/* cpu doze func */
void rtos_cpu_stop(void);
/* port tick timer init */
void _port_tick_timer_init(int schedfreq, void* callback);

#ifdef __cplusplus
}
#endif
#endif /* IGORSRTOS_PORTS_POSIX_H_ */
