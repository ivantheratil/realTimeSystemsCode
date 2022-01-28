#include <cmsis_os2.h>
#include <LPC17xx.h>
#include <stdbool.h>
#include <stdio.h>

osSemaphoreId_t sem;

void t1(void *arg) {
	while(true) {
		osDelay(osKernelGetTickFreq()/10);
		if(osSemaphoreRelease(sem) != osOK)
			return;
}
}
void t2(void *arg) {
	while(true) {
		switch(osSemaphoreAcquire(sem, osWaitForever)) {
			case osOK: printf("tick\n"); break;
			case osErrorTimeout: printf("timeout\n"); return;
			case osErrorResource: printf("not available\n"); return;
			case osErrorParameter: printf("bad sem id\n"); return;
			default: printf("shouldn't get here\n"); return;
		}
	}
}
int main(void) {
	osKernelInitialize();
	
	sem = osSemaphoreNew(1, 0, NULL);
	osThreadId_t tid1 = osThreadNew(t1, NULL, NULL);
	osThreadId_t tid2 = osThreadNew(t2, NULL, NULL);
	if(!sem || !tid1 || !tid2) {
		printf("failure\n");
	} else {
	osKernelStart();
	}
	for( ; ; ) ;
}

