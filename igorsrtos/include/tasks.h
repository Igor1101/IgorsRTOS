/*
 * scheduler.h
 *
 *  Created on: Jul 16, 2019
 *      Author: Igor
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <rtos.h>
#include <mutex.h>

#define RTOS_TASK_SCHEDULE_FREQ	TIMER_MS(1)
#define RTOS_MAX_TASKS 20
#define RTOS_TASK_MAX_MUTEXES 10


typedef enum {
	TASK_RUNNING,
	TASK_SLEEPING,
	TASK_DEAD
} taskstate_t;

typedef struct {
	void (*function)(void*);
	void* msg;
	taskstate_t state;
	void* mutexes[RTOS_TASK_MAX_MUTEXES];
	int mutexamount;
} rtostask_t;

void rtos_tasks_init(void);
int rtos_add_task(rtostask_t* task);
int rtos_task_putmsg(int tsknum, void*msg);
void rtos_sleep(u32 time);
void rtos_start(void);
void _rtos_tasks_schedule_callback(void);
int rtos_task_current(void);
BOOL rtos_task_mutex_allowed(int tskdesc, rtosmutex_var_t mx);
int rtos_task_allow_mutex(int tskdesc, rtosmutex_var_t mx);
BOOL rtos_task_mutexes_locked(int tskdesc);
#ifdef __cplusplus
}
#endif
#endif /* SCHEDULER_H_ */
