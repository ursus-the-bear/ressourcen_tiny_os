/*
 * scheduler.c
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */
#include <msp430.h>
#include "scheduler.h"
#include "setjmp.h"

thread_t threadList [MAX_THREADS];
int currThread;

// where is your next free spot
int scheduler_getFreeThread () {

	// didn't your parents tell you not to speak until you are spoken to?
	_disable_interrupts();

	// find the spot you want to place the thread
	int RC;
	int i;
	RC = ERROR_THREAD;
	for (i = 0; i < MAX_THREADS; i++) {
		if (threadList [i].state == FREE) {
			RC = i;
			break;
		}
	}

	// ok, what is it that you wanted
	_enable_interrupts ();

	// and return the first space you found
	return RC;
}

// start a thread
int scheduler_startThread (void (*funcPtr)()) {

	// do not process interrupts when I am busy
	_disable_interrupts();

	// get the next thread
	int threadID = scheduler_getFreeThread ();
	if (threadID == NO_THREAD) return threadID;

	// setup your thread array
	threadList[threadID].funcPtr = funcPtr;
	threadList[threadID].state = WAITING;

	// save the current state of the
	if (setjmp (threadList [threadID].context) == 0) {
		// now that everything is setup nothing left to do but go back to the caller
		_enable_interrupts ();
		return threadID;
	} else {
		// ok, the longjmp has been called
		_enable_interrupts ();
		threadList [threadID].funcPtr();		// basically run the function you are passing to it
		scheduler_killThread(threadID);			// once you get here you are finished so stop
		return ERROR_THREAD;
	}
}
// where is your next free spot
int scheduler_getNextThreadToRun () {

	// didn't your parents tell you not to speak until you are spoken to?
	_disable_interrupts();

	// find the next thread AFTER the current one (looping the array if need be)
	int RC;
	RC = ERROR_THREAD;
	int i;
	int arrayPos;
	// which count are you at
	for (i = 1; i < MAX_THREADS; i++) {
		// find the position you need to check in the loop
		arrayPos = currThread + i; // this is where you are now
		if (arrayPos > MAX_THREADS) // you are over your array so go to the beginning of the loop -> saves you 2 loops :o)
			arrayPos = MAX_THREADS - (i + currThread);

		// now check that position
		if (threadList [arrayPos].state == WAITING) {
			RC = arrayPos;
			i = MAX_THREADS;
		}
	}

	// ok, what is it that you wanted
	_enable_interrupts ();

	// and return the first space you found
	return RC;
}
// select the next thread to run and run it
void scheduler_runNextThread() {

	// do not process interrupts when I am busy
	_disable_interrupts();

	// which thread do we need to run now
	int threadID = scheduler_getNextThreadToRun();
	if (threadID == ERROR_THREAD) return;

	// now switch according to the state of the thread
	switch (threadList[threadID].state) {
	case RUNNING: break ; // not sure I need this as I only return WAITING threads
	case WAITING:
		if (setjmp(threadList[threadID].context) == 0) {
			if (threadList[currThread].state == RUNNING)
				threadList[currThread].state = WAITING;
			currThread = threadID;
			threadList[currThread].state = RUNNING;
			longjmp(threadList[currThread].context, 1);
		}
	}

	// ok, now we can process interrupts again
	_enable_interrupts ();
}
void scheduler_killThread (int threadNo) {

	// children should be seen and not heard
	_disable_interrupts();

	// just say this position is empty
	threadList [threadNo].state = FREE;

	// ok, what is it that you wanted
	_enable_interrupts ();

}
