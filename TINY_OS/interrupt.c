/*
 * interrupt.c
 *
 *  Created on: 20 Jan 2016
 *      Author: offic
 */
#include <msp430.h>

#include "interrupt.h"
#include "scheduler.h"

#define ONE_SECOND 512


int changeThreadTimer = 0;

void setupTimer (void) {

	// this code is from the morse example

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
	TACCR0 = 1000000; 					// 1 ms @ 1MHz   1 sec

	// end of morse example

	// this code from here: http://forum.allaboutcircuits.com/blog/msp430-long-timer-count.552/

	  // Set up 32768Hz crystal
//	  BCSCTL1 |= DIVA_3;    // divide by 8
//	  BCSCTL3 |= XCAP_3;    // select 12pF caps

	  // initialize Timer0_A
//	  TA0CCR0 = 5 * ONE_SECOND;     // set up terminal count for 10s
//	  TA0CTL = TASSEL_1 + ID_3 + MC_1; // configure and start timer

//		CCTL0 = CCIE;					// CCRO Interrupt enable
	//  TA0CCTL0_bit.CCIE = 1;   // enable timer interrupts


}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer (void) {

	timeThread++; // increase timer
	changeThreadTimer++;

	if(changeThreadTimer >= CHANGETIMETHREAD){  // time to change a Thread
		changeThreadTimer = 0;
		scheduler_runNextThread ();
	}

}
