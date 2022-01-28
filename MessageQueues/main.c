#include <cmsis_os2.h>
#include <LPC17xx.h>
#include "random.h"
#include <stdbool.h>
#include <stdio.h>

// Define number of queues
# define numQueues 2

// Array of message queue IDs
osMessageQueueId_t q_id[numQueues];

// Array of sent, received, & overflows counters
int sent[numQueues];
int received[numQueues];
int overflows[numQueues];

// The message
int message = 19;

// Client Thread
void client (void *arg) {
	osStatus_t status;
	int delaySeconds = 0;
	int avgDelayTicks = 0;
	int nTicks = 0;
	int ticksPerSecond = osKernelGetTickFreq();	
	while (true) {
		for (int i = 0; i < numQueues; i++) {
			delaySeconds = next_event();
			// Arrival rate is 9Hz at EACH queue => 9*2
			avgDelayTicks = delaySeconds*ticksPerSecond/(9*2);
			nTicks = avgDelayTicks >> 16;
			osDelay(nTicks);
			status = osMessageQueuePut(q_id[i], &message, 0, 0);
			if (status == osOK) {
				sent[i]++;
			}
			else if (status == osErrorResource){
				overflows[i]++;
			}
		}
	}
}

// Server Thread
void server (void *arg) {
	char *iChar = (char *) arg;
	int i = *iChar-'0';
	int delaySeconds = 0;
	int avgDelayTicks = 0;
	int nTicks = 0;
	int ticksPerSecond = osKernelGetTickFreq();	
	while (true) {
		delaySeconds = next_event();
		avgDelayTicks = delaySeconds*ticksPerSecond/10;
		nTicks = avgDelayTicks >> 16;
		osDelay(nTicks);
		osMessageQueueGet(q_id[i], &message, NULL, osWaitForever);
		received[i]++;
	}
}

// Monitor Thread
void monitor (void *arg) {
	int ticksPerSecond = osKernelGetTickFreq();
	int seconds = 1;
	while (true) {
		osDelay(ticksPerSecond);
		printf("Elapsed Time in Seconds: %d    ", seconds);
		for (int i = 0; i < numQueues; i++) {
			printf("Queue %d Sent, Received, Overflows: %d, %d, %d    ", i, sent[i], received[i], overflows[i]);
		}
		printf("\n");
		seconds++;
	}
}

// Helper function to initialize all queues, servers, and variables
void initQueuesServersVars (void) {
	for (int i = 0; i < numQueues; i++) {
		q_id[i] = osMessageQueueNew(10, sizeof(int), NULL);
		sent[i] = 0;
		received[i] = 0;
		overflows[i] = 0;
	}
	osThreadNew(server, "0", NULL);
	osThreadNew(server, "1", NULL);
}

int main () {
	osKernelInitialize();
	initQueuesServersVars();
	osThreadNew(client, NULL, NULL);
	osThreadNew(monitor, NULL, NULL);
	osKernelStart();
}
