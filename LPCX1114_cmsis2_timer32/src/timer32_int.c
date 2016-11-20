//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2009 Code Red Technologies Ltd.
//
// timer32_int.c - Interrupt handler code for timer32 peripherals of LPC11xx
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.
//
//*****************************************************************************

// Code based on content of NXP timer32.c, to be found in LPC11xx_Lib project.
// Interrupts handlers have been extracted to this file so that the library
// project is then application independent.

#include "LPC11xx.h"
#include "timer32.h"

volatile uint32_t timer32_0_counter = 0;
volatile uint32_t timer32_1_counter = 0;



/******************************************************************************
** Function name:		TIMER32_0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER32_0_IRQHandler(void)
{
  LPC_TMR32B0->IR = 1;			/* clear interrupt flag */
  timer32_0_counter++;
  return;
}

/******************************************************************************
** Function name:		TIMER32_1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER32_1_IRQHandler(void)
{
  LPC_TMR32B1->IR = 1;			/* clear interrupt flag */
  timer32_1_counter++;
  return;
}
