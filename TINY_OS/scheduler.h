/*
 * scheduler.h
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <inttypes.h>
#include <limits.h>   // length of variables

// check if your types are long enough
#if (MAX_INT < 1000000)
	#error int_too_small
// this produces a compiler error
//	#warning "xxx" // same same but different
#endif

// what info am I keeping per thread
typedef struct _thread {
	char state;
	void * funcptr;
	jmp_buf context;
	uint 16.t sleepTime;
} thread_t;

#define MAX_THREADS 10
#define ERROR_THREAD -1

#define RUNNING 'R'
#define WAITING 'W'
#define BLOCKED 'B'
#define ADDED 'A'
#define NO_PROCESS 'N'

typedef enum {
STATE_RUNNING,
STATE_READY,

} state_t;



int scheduler_getFreeThread ();
int scheduler_addThread (void * function);
int scheduler_startThread (int threadNo);
void scheduler_runNextThread ();
int scheduler_getNextThreadToRun ();
void scheduler_killThread (int threadNo);

extern int currThread;
extern thread_t threadList [MAX_THREADS];

#endif /* SCHEDULER_H_ */
