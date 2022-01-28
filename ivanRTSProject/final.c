#include <cmsis_os2.h>
#include <stdlib.h>
#include "general.h"

typedef struct {
	uint8_t n;
	bool *loyal;
	uint8_t commander;
	char command;
	uint8_t reporter;
} test_t;

bool loyal0[] = { true, true, false };
bool loyal1[] = { true, false, true, true };
bool loyal2[] = { true, false, true, true };
bool loyal3[] = { true, false, true, true, false, true, true };

#define N_TEST 4

test_t tests[N_TEST] = {
	{ sizeof(loyal0)/sizeof(loyal0[0]), loyal0, 0, 'R', 1 },
	{ sizeof(loyal1)/sizeof(loyal1[0]), loyal1, 0, 'R', 2 },
	{ sizeof(loyal2)/sizeof(loyal2[0]), loyal2, 1, 'A', 2 },
	{ sizeof(loyal3)/sizeof(loyal3[0]), loyal3, 0, 'R', 6 }
};

#define MAX_GENERALS 7
uint8_t ids[MAX_GENERALS] = { 0, 1, 2, 3, 4, 5, 6 };
osThreadId_t generals[MAX_GENERALS];
uint8_t nGeneral;

void startGenerals(uint8_t n) {
	nGeneral = n;
	for(uint8_t i=0; i<nGeneral; i++) {
		generals[i] = osThreadNew(general, ids + i, NULL);
		if(generals[i] == NULL) {
			printf("failed to create general[%d]\n", i);
		}
	}
}

void stopGenerals(void) {
	for(uint8_t i=0; i<nGeneral; i++) {
		osThreadTerminate(generals[i]);
	}
}

void testCases(void *arguments) {
	for(int i=0; i<N_TEST; i++) {
		printf("\ntest case %d\n", i);
		if(setup(tests[i].n, tests[i].loyal, tests[i].reporter)) {
			startGenerals(tests[i].n);
			broadcast(tests[i].command, tests[i].commander);
			cleanup();
			stopGenerals();
		} else {
			printf(" setup failed\n");
		}
	}
	printf("\ndone\n");
}

/* main */
int main(void) {
	osKernelInitialize();
  osThreadNew(testCases, NULL, NULL);
	osKernelStart();
	
	for( ; ; ) ;
}
