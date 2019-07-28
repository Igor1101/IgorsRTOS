/*
 * mutex.c
 *
 *  Created on: Jul 27, 2019
 *      Author: igor
 */
#include <rtos.h>
#include <rtos/types.h>
#include "mutex.h"

static rtosmutex_t mutexbuf[RTOS_MUTEX_MAX_AMOUNT];
static int m_max_pointer = 0;
BOOL rtos_mutex_exists(void* const variable)
{
	int i=0;
	for(i=0; i<RTOS_MUTEX_MAX_AMOUNT; i++) {
		if((uptr)mutexbuf[i].variable == (uptr)variable) {
			return TRUE;
		}
	}
	return FALSE;
}
int rtos_mutex_declare(void* const variable)
{
	if(m_max_pointer >= RTOS_MUTEX_MAX_AMOUNT) {
		pr_err("mutex err, declaration ovf");
		return RTOS_FAILURE;
	}
	if(rtos_mutex_exists(variable)) {
		pr_err("mutex err, mutex to the same variable");
		return RTOS_FAILURE;
	}
	mutexbuf[m_max_pointer].state = MUTEX_UNLOCKED;
	mutexbuf[m_max_pointer].variable = variable;
	m_max_pointer++;
	return RTOS_SUCCESS;
}
void rtos_mutex_unsaferemove(void* const variable)
{
	//TODO
}
void rtos_mutex_lock(void*const variable)
{
	//TODO
}
void rtos_mutex_unlock(void*const variable)
{
	//TODO
}
