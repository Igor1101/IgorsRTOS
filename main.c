#include <rtos.h>
void task_f(void*msg);
rtostask_t task1 = {
		.msg = "TASK1",
		.function = task_f
};
int main()
{
	rtos_init();
	rtos_sleep(TIMER_S(1));
	rtos_add_task(&task1);
	pr_info("starting igorsrtos" " " RTOS_PORT_NAME);
	while(1);
}

void task_f(void*msg)
{
	if(msg != NULL)
		pr_info("%s",(char*)msg);
}
