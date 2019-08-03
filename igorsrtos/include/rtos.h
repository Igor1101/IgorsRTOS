/*
 * rtos.h
 *
 *  Created on: Jul 21, 2019
 *      Author: igor
 */

#ifndef RTOS_RTOS_H_
#define RTOS_RTOS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <rtos/types.h>
/* here we define ports file */
#if (defined PORT_POSIX)
#include <ports/posix.h>
#endif /* ports */
/* types defined here */
typedef enum {
	IS_TASK,
	IS_THREAD,
	IS_MAIN_THREAD,
	IS_PROCESS,
	IS_INTERRUPT,
	IS_UNKNOWN
} rtos_task_type_t;
extern rtos_task_type_t __current_task;
/* functions those must be defined with ports */
#if !(defined pr_rtos)
#error "couldn`t find pr_rtos function"
#endif
#define pr_debug(...) pr_rtos("RTOS DEBUG: " __VA_ARGS__)
#define pr_info(...) pr_rtos("RTOS: " __VA_ARGS__)
#define pr_warn(...) pr_rtos("RTOS WARNING: " __VA_ARGS__)
#define pr_err(...) pr_rtos("RTOS ERROR: " __VA_ARGS__)
#define pr_fatal(...) pr_rtos("RTOS FATAL: " __VA_ARGS__)

#define rtos_assert(expr) \
	if (!(expr)) \
	pr_err("assertion failed file %s, line %d",__FILE__, __LINE__)
/* general rtos functions */
BOOL rtos_is_initialized(void);
void rtos_init(void);

#include <thread.h>
#include <tasks.h>
#ifdef __cplusplus
}
#endif
#endif /* RTOS_RTOS_H_ */
