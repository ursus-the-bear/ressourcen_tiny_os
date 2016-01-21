/*
 * testFunc.c
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */
#include <msp430.h>
#include "testFunc.h"
#include "interrupt.h"


void setupTestFuncs () {

	// preabmle
	WDTCTL = WDTPW + WDTHOLD; 		// stop using the watchdog

	// LED initial setup
	P1DIR |= RED_LED + GREEN_LED;	// ENABLE GREEN AND RED LED
	P1OUT &= ~GREEN_LED;			// Green off
	P1OUT &= ~RED_LED;				// Red off

}
// red for 2 secs
void functionRed () {

	iLEDonCount = 0;

	// switch red on
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT |= RED_LED;		// Red on

	int i;
	while (iLEDonCount <= REPEATTIMEFUNC){
		i = iLEDonCount;  // just do something so the while does not get removed
	}

	// everything off
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}
// green for 2 secs
void functionGreen () {

	iLEDonCount = 0;

		// switch red on
	P1OUT |= GREEN_LED;		// Green on
	P1OUT &= ~RED_LED;		// Red off

	//wait
	int i;

	while (iLEDonCount <= REPEATTIMEFUNC){
		i = iLEDonCount;
	}

	// everything off
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}
