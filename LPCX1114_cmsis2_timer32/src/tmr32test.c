/*****************************************************************************
 *   tmr32test.c:  32-bit timer C file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Preliminary version, first Release
 *   2009,2010       1.01	 Minor tweaks by Code Red
 *
******************************************************************************/

// CodeRed - Minor modifications to original NXP code, plus ported to LPC11xx

// Jan 2011 - CRP additions for Red Suite / LPCXpresso 3.6.2

#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "timer32.h"
#include "gpio.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// LPCXpresso eval board LED
#define LED_PORT 0		// Port for led
#define LED_BIT 7		// Bit on port for led
#define LED_ON 1		// Level to set port to turn on led
#define LED_OFF 0		// Level to set port to turn off led


extern volatile uint32_t timer32_0_counter;


/* Main Program */

int main (void) {
  /* Basic chip initialization is taken care of in SystemInit() called
   * from the startup code. SystemInit() and chip settings are defined
   * in the CMSIS system_<part family>.c file.
   */

  /* Initialize GPIO (sets up clock) */
  GPIOInit();

  // Initialise Timer32_0 to tick at rate of 1/100th of second.
	// Default clock speed set up by CMSIS SystemInit function
	// (SystemCoreClock) - is 48MHz or 48000000 Hz. Dividing this
    // by 100 is 480000.
	// Note by default LPC_SYSCON->SYSAHBCLKDIV is 1.
  init_timer32(0, ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/100 ));

  /* Initialise counter that is incremented by timer32 interrupts */
  timer32_0_counter = 0;

  /* Turn timer on */
  enable_timer32(0);
  
  /* Set port for LED to output */
  GPIOSetDir( LED_PORT, LED_BIT, 1 );

  while (1)                                /* Loop forever */
  {
	// Toggle state of LED every second
	if ( (timer32_0_counter > 0) && (timer32_0_counter <= 100) )
	{
		  GPIOSetValue( LED_PORT, LED_BIT, LED_OFF );
	}
	if ( (timer32_0_counter > 100) && (timer32_0_counter <= 200) )
	{
		  GPIOSetValue( LED_PORT, LED_BIT, LED_ON );
	}
	else if ( timer32_0_counter > 200 )
	{
	  timer32_0_counter = 0;
	}
  }
}
