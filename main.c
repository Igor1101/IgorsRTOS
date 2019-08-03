#include <rtos.h>
void task_f(void*msg);
rtostask_t task1 = {
		.msg = "TASK1",
		.function = task_f
};
int myvar;
int main()
{
	rtos_init();
	rtos_mutex_declare(RTOS_MUTEX(myvar));
	rtos_sleep(TIMER_S(1));
	int tsk1 = rtos_add_task(&task1);
	rtos_task_allow_mutex(tsk1, RTOS_MUTEX(myvar));
	pr_info("starting igorsrtos" " " RTOS_PORT_NAME);
	while(1) {
		rtos_sleep(TIMER_S(1));
		pr_info("lock mutex...");
		rtos_mutex_lock(RTOS_MUTEX(myvar));
		pr_info("done");
		pr_info("myvar=%d", myvar);
		pr_info("unlock...");
		rtos_mutex_unlock(RTOS_MUTEX(myvar));
		pr_info("done");
	}
}

void task_f(void*msg)
{
	if(msg != NULL)
		pr_info("%s",(char*)msg);
	rtos_assert(rtos_mutex_lock(RTOS_MUTEX(myvar)) == RTOS_SUCCESS);
	myvar++;
	rtos_assert(rtos_mutex_unlock(RTOS_MUTEX(myvar)) == RTOS_SUCCESS);
}
