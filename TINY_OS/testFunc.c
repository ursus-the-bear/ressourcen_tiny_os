/*
 * testFunc.c
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */
#include <msp430.h>
#include "testFunc.h"

void setupTestFuncs () {

	// preabmle
	WDTCTL = WDTPW + WDTHOLD; 		// stop using the watchdog

	// LED initial setup
	P1DIR |= RED_LED + GREEN_LED;	// ENABLE GREEN AND RED LED
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}

// delay a couple of secs
void delay (int secsToWait) {
	int i, j, k;
	for (i = 1; i <= secsToWait; i++) {
		// 16 000 000 cycles is a second
		for (j = 1; j <= 16; j++)
			for (k = 1; k <= 50; k++)
				__delay_cycles (1000); // delay program execution for 1000 cycles
	}

	// MCU clock MCLK = 16MHz --> instruction cycle time = 62.5ns (= 1/MCLK)
	// Required delay = 5s
    //
	// --> 5s/62.5ns = 80.000.000
	// --> 1s 		 = 16.000.000

}
// red for 2 secs
void functionRed () {

	// switch red on
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT |= RED_LED;		// Red on

	// wait
	delay (2);

	// everything off
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}
// green for 2 secs
void functionGreen () {

	// switch red on
	P1OUT |= GREEN_LED;		// Green on
	P1OUT &= ~RED_LED;		// Red off

	// wait
	delay (2);

	// everything off
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}
