#include <msp430.h> 
#include "testFunc.h"
#include "scheduler.h"

// list of my processes

/*
 * main.c
 */
int main (void) {

	// preamble
	setupTestFuncs ();

	// setup your processList
	int i;
	for (i = 0; i < MAX_THREADS; i++)
		threadList [i].state = NO_PROCESS;
	currThread = 0;

	// add your threads
	int threadID;
	threadID = scheduler_addThread (&functionGreen);
	threadID = scheduler_addThread (&functionRed);

	while (1==1) {

		// currently do nothing

	}
}
