#include <msp430.h> 
#include "testFunc.h"
#include "scheduler.h"
#include "interrupt.h"

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
		threadList [i].state = FREE;
	currThread = -1;

	// add your threads
	int threadID;
	threadID = scheduler_startThread (&functionGreen);
	threadID = scheduler_startThread (&functionRed);
	threadID = scheduler_startThread (&functionGreen);
	threadID = scheduler_startThread (&functionRed);
	threadID = scheduler_startThread (&functionGreen);
	//threadID = scheduler_startThread (&functionRed);
//	threadID = scheduler_startThread (&functionGreen);
//	threadID = scheduler_startThread (&functionRed);

	// thread 9 und 10 sind leer - damit kann ich mein thread array prüfen


	// ok, now enable the interrupts for everything to just magically start
	__enable_interrupt();
	setupTimer (); // after all initials


	while (1==1) {

		// currently do nothing
		// just loafing aroung
	}
}
