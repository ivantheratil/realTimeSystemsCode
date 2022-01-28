/** RTOS2 mutex  **/
#include <cmsis_os2.h>
#include <LPC17xx.h>
#include <stdbool.h>
#include <stdio.h>

osMutexId_t mut;
bool b = true;
	
void t1(void *arg) {
	osThreadSetPriority(osThreadGetId(), osPriorityHigh);
	while(true) {
		osDelay(osKernelGetTickFreq()/20);
		osMutexAcquire(mut, osWaitForever); {
			printf("%s\n", b ? "true" : "false");
		} osMutexRelease(mut);
	}
}
void t2(void *arg) {
	while(true) {
		osMutexAcquire(mut, osWaitForever); {
			b = !b;
			} osMutexRelease(mut);
	}
}
int main(void) {
	osKernelInitialize();
	osMutexAttr_t mAttr = { .attr_bits = osMutexPrioInherit |
osMutexRobust };
	mut = osMutexNew(&mAttr);
	osThreadId_t tid1 = osThreadNew(t1, NULL, NULL);
	osThreadId_t tid2 = osThreadNew(t2, NULL, NULL);
	if(!mut || !tid1 || !tid2) {
		printf("failure\n");
	} else {
		osKernelStart();
	}
	for( ; ; ) ;
}
