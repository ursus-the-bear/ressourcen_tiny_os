/*
 * testFunc.h
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */

#ifndef TESTFUNC_H_
#define TESTFUNC_H_

#define BUTTON  	BIT3 // Port 1.3
#define RED_LED   	BIT0 // Port 1.0
#define GREEN_LED  	BIT6 // Port 1.6
#define REPEATTIMEFUNC 2000

void setupTestFuncs ();
void delay (int secsToWait);
void functionRed ();
void functionGreen ();

#endif /* TESTFUNC_H_ */
