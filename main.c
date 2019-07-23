#include <rtos.h>
int main()
{
	rtos_init();
	pr_info("starting igorsrtos" " " RTOS_PORT_NAME);
}
