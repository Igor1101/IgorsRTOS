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

#define RTOS_TASK_SCHEDULE_FREQ	TIMER_MS(1)
#define RTOS_MAX_TASKS 20


typedef enum {
	TASK_RUNNING,
	TASK_SLEEPING,
	TASK_DEAD
} taskstate_t;

typedef struct {
	void (*function)(void*);
	void* msg;
	taskstate_t state;
} rtostask_t;

void rtos_tasks_init(void);
int rtos_add_task(rtostask_t* task);
int rtos_putmsg_task(void*msg, int tsknum);
void rtos_sleep(u32 time);
void rtos_start(void);
void _rtos_tasks_schedule_callback(void);
#ifdef __cplusplus
}
#endif
#endif /* SCHEDULER_H_ */
