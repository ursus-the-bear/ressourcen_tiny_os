#include <msp430.h> 
#include "testFunc.h"
#include "scheduler.h"
#include "interrupt.h"
/*
 * main.c
 */
int main (void) {

	// preamble
	setupTestFuncs ();
	setupTimer ();

	// setup your processList
	int i;
	for (i = 0; i < MAX_THREADS; i++)
		threadList [i].state = FREE;
	currThread = -1;

	// add your threads
	int threadID;
	threadID = scheduler_startThread (&functionGreen);
	threadID = scheduler_startThread (&functionRed);
	threadID = scheduler_startThread (&functionGreen);
	threadID = scheduler_startThread (&functionRed);
	threadID = scheduler_startThread (&functionGreen);
	threadID = scheduler_startThread (&functionRed);
	threadID = scheduler_startThread (&functionGreen);
    threadID = scheduler_startThread (&functionRed);

	// ok, now enable the interrupts for everything to just magically start
	__enable_interrupt();

	// now just do nothing so the program can run for ever...
	while (1==1) {

		// currently do nothing
		// just loafing aroung
	}
}
