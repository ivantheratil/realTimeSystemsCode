#include <cmsis_os2.h>
#include "general.h"

// add any #includes here
#include <LPC17xx.h>
#include <stdbool.h>
#include <stdio.h>

#include <assert.h>
#include <string.h>

void OM(int m, char command,int *idPtr);


// add any #defines here

// add global variables here


bool Gloyal[7];
osMessageQueueId_t genQueue[7];
osSemaphoreId_t semaphore;

int n;
int m;
int Gcommander;
char Gcommand;
int report;
int n;

/** Record parameters and set up any OS and other resources
  * needed by your general() and broadcast() functions.
  * nGeneral: number of generals
  * loyal: array representing loyalty of corresponding generals
  * reporter: general that will generate output
  * return true if setup successful and n > 3*m, false otherwise
  */
	

bool setup(uint8_t nGeneral, bool loyal[], uint8_t reporter) {
	
	n = nGeneral;
	report = reporter;
	
	for (int i = 0; i < n; i++){
		Gloyal[i] = loyal[i];
		
		if (loyal[i] == false){
			m++;
		}
	}
	assert(n > 3*m);
	if (n <= 3*m){
		m = 0;
		return false;
	}
	
	for (int i = 0;i < n; i++){	
		genQueue[i]=osMessageQueueNew(20,sizeof(char[7]),NULL);
	}
	semaphore = osSemaphoreNew(n,0,NULL);

	
	return true;
}


/** Delete any OS resources created by setup() and free any memory
  * dynamically allocated by setup().
  */
void cleanup(void) {
	for (int i = 0;i < 7; i++){	
		osMessageQueueDelete (genQueue[i]);
	}
	osSemaphoreDelete (semaphore);

}


/** This function performs the initial broadcast to n-1 generals.
  * It should wait for the generals to finish before returning.
  * Note that the general sending the command does not participate
  * in the OM algorithm.
  * command: either 'A' or 'R'
  * sender: general sending the command to other n-1 generals
  */
void broadcast(char command, uint8_t commander) {
	Gcommand = command;
	Gcommander = commander;
	char msg[8];
	
	bool isTrue = Gloyal[Gcommander];
	
	if(Gcommander != isTrue){
		if(Gcommander%2 ==0){
			sprintf(msg,"%d:R",Gcommander);
		}
		else{		
			sprintf(msg,"%d:A",Gcommander);					
		}
	}
		
	else{
			
			sprintf(msg,"%d:%s",Gcommander,&Gcommand);					
	}



for (int i = 0; i < n; i++){
	if(i != Gcommander){
		osMessageQueuePut(genQueue[i], &msg, 0, 0);
	}
}
for (int i = 0; i < n; i++){
	osSemaphoreAcquire(semaphore,osWaitForever);
}
}

void OM(int m, char command,int *idPtr){
	if(m>0){
	
	
	}
	
}

/** Generals are created before each test and deleted after each
  * test.  The function should wait for a value from broadcast()
  * and then use the OM algorithm to solve the Byzantine General's
  * Problem.  The general designated as reporter in setup()
  * should output the messages received in OM(0).
  * idPtr: pointer to general's id number which is in [0,n-1]
  */
void general(void *idPtr) {
	uint8_t id = *(uint8_t *)idPtr;
	
	for(i in
	osSemaphoreRelease(semaphore);
	
}
