/*
 * interrupt.c
 *
 *  Created on: 20 Jan 2016
 *      Author: offic
 */
#include <msp430.h>

#include "interrupt.h"
#include "scheduler.h"

#define TIME_TO_CALL_SCHEDULER  5000 // timer triggers once a second i.e. change threads every 5 seconds

int callScheduler;
int iLEDonCount;

void setupTimer (void) {

	// This sets the MSP430's clock to a factory calibrated 1 MHz,
	// which means that any delays we specify will be more accurate
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	// Setup your timer
	TA0CCTL1 = CM_0 | OUTMOD_7;		// no capture (->ignore CCISx, SCS, SCCI), Compare mode, Reset/Set outmode, ignore "rest"
	CCTL0 = CCIE;					// CCRO Interrupt enable
	TA0CTL = 						// Timer TA0
			TASSEL_2 +				// TASSEL_2 selects SMCLK clock
			ID_0 + 					// ???
			MC_1 + 					// ???
			TACLR;					// Clear timer

	TACCR0 = 1000; 					// 1 ms @ 1MHz i.e. timer gets called every second

	// initialise your schedule timer
	callScheduler = 0;
	iLEDonCount = 0;
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer (void) {

	// up your timers
	callScheduler++;
	iLEDonCount++;	// ie. LED has been ON for another ms

	// do we need to call the scheduler
	if(callScheduler >= TIME_TO_CALL_SCHEDULER) {
		callScheduler = 0;
		scheduler_runNextThread ();
	}

}
