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

#define RTOS_MUTEX_MAX_AMOUNT 100
typedef enum {
	MUTEX_DISABLED = 0,
	MUTEX_LOCKED,
	MUTEX_UNLOCKED
}rtosmutexstate_t ;
typedef struct {
	void*variable;
	rtosmutexstate_t state;
}rtosmutex_t;
/* you can`t declare more than 1 mutex to the same variable
 *
 */
/* mutexes are dynamic but*/
/* variable mutex */
int rtos_mutex_declare(void* const variable);
void rtos_mutex_remove (void* const variable);
void rtos_mutex_lock(void*const variable);
void rtos_mutex_unlock(void*const variable);
BOOL rtos_mutex_exists(void* const variable);

#ifdef __cplusplus
}
#endif
#endif /* IGORSRTOS_INCLUDE_MUTEX_H_ */
