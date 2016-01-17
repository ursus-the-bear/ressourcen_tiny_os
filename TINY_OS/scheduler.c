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

	// find the spot you want to place the thread at
	int RC;
	RC = ERROR_THREAD;
	for (int i = 0; i < MAX_THREADS; i++) {
		if (threadList [i].state == NO_THREAD) {
			RC = i;
			i = MAX_THREADS;
		}
	}

	// ok, what is it that you wanted
	_enable_interrupts ();

	// and return the first space you found
	return RC;
}

// start a thread
int scheduler_startThread(int threadNo) {

	// do not process interrupts when I am busy
	_disable_interrupts();

	// check if there is even a thread there
	if (threadList [threadNo].state == NO_THREAD) {
		_enable_interrupts ();
		return ERROR_THREAD;
	}

	// is this thread already running
	if (threadList [threadNo].state == RUNNING) {
		_enable_interrupts ();
		return threadNo;
	}

	// ok, you need to start the thread
	currThread = threadNo;
	if (setjmp (threadList [threadNo].context) == 0) {
		// now that everything is setup nothing left to do
		_enable_interrupts ();
		return threadNo;
	} else {
		// when do you get here?
		_enable_interrupts ();
		threadList [threadNo]->funcPtr ();		// basically run the function you are passing to it
		scheduler_killThread(threadNo);			// once you get here you are finished so stop
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
	switch (threadList [threadID].state) {
	case WAITING:
		if (setjmp(threadList[threadID].context) == 0) {
			if (gThreads[gRunningThread].state == THREAD_RUNNING)
				gThreads[gRunningThread].state = THREAD_READY;
			gRunningThread = nextThread;
			gThreads[gRunningThread].state = THREAD_RUNNING;
			longjmp(gThreads[gRunningThread].context, 1);
		}
	}

	//
//	threadID nextThread ;//determine next Thread (round robin)
//	switch(gThreads[nextThread].state) {
//	case THREAD_RUNNING: break; // already running
//	case THREAD_READY:
//		break;
//		default: break; // no thread to run -> sleep no atomic
//	}

	// ok, now we can process interrupts again
	_enable_interrupts ();
}
void scheduler_killThread (int threadNo) {

	// children should be seen and not heard
	_disable_interrupts();

	// just say this position is empty
	threadList [threadNo].state = NO_THREAD;

	// ok, what is it that you wanted
	_enable_interrupts ();

}
