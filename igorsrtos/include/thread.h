/*
 * thread.h
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */

#ifndef IGORSRTOS_INCLUDE_THREAD_H_
#define IGORSRTOS_INCLUDE_THREAD_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <rtos.h>
typedef enum {
	RUNNING,
	CONTEXT_SAVED,
	FREEZED,
	FREEZED_CONTEXT_SAVED,
	FINISHED
} rtos_thread_state_t;

typedef struct {
	/* TODO */
}thread_mem_t;

typedef struct {
	u16 uniq_num;
	rtos_thread_state_t state;
	/* port specific */
	context_t context;
	uptr current_stack;
	thread_mem_t mem;
	i32 time_freezed;
}rtos_thread_t;

extern rtos_thread_t thread_current;
void rtos_thread_cur_freeze(i32 time);

#ifdef __cplusplus
}
#endif
#endif /* IGORSRTOS_INCLUDE_THREAD_H_ */
