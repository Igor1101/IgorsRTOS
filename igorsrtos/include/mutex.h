/*
 * mutex.h
 *
 *  Created on: Jul 27, 2019
 *      Author: igor
 */

#ifndef IGORSRTOS_INCLUDE_MUTEX_H_
#define IGORSRTOS_INCLUDE_MUTEX_H_
#ifdef __cplusplus
extern "C" {
#endif

#define RTOS_MUTEX(X) &X
#define RTOS_MUTEX_MAX_AMOUNT 100
typedef enum {
	MUTEX_DISABLED = 0,
	MUTEX_LOCKED,
	MUTEX_UNLOCKED
}rtosmutexstate_t ;
typedef struct {
	void*variable;
	rtosmutexstate_t state;
	rtos_task_type_t lock_t;
	int lock_inst;
}rtosmutex_t;

typedef void*const rtosmutex_var_t;
/* you can`t declare more than 1 mutex to the same variable
 *
 */
/* mutexes are dynamic but*/
/* variable mutex */
int rtos_mutex_declare(rtosmutex_var_t variable);
void rtos_mutex_remove (rtosmutex_var_t variable);
int rtos_mutex_lock(rtosmutex_var_t variable);
int rtos_mutex_unlock(rtosmutex_var_t variable);
BOOL rtos_mutex_exists(rtosmutex_var_t variable);
BOOL rtos_mutex_locked(rtosmutex_var_t variable);
int rtos_mutex_get_instance(rtosmutex_t*mxp, rtosmutex_var_t variable);

#ifdef __cplusplus
}
#endif
#endif /* IGORSRTOS_INCLUDE_MUTEX_H_ */
