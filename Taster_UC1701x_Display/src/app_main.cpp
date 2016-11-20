/*
 *  A simple example for SPI.

 *
 *  This example configures SPI for output and sends a byte every second.
 *
 *  Copyright (c) 2014 Stefan Taferner <stefan.taferner@gmx.at>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 */

#include <sblib/eib/sblib_default_objects.h>
#include <sblib/core.h>
#include <sblib/ioports.h>
#include <sblib/spi.h>
#include <sblib/serial.h>


#include <u8g_arm.h>
#include <M2tk.h>
#include <m2ghu8g.h>
#include "lcd.h"
#include "params.h"
#include <sblib/i2c/ds3231.h>

#define _DEBUG__

#ifdef _DEBUG__
Serial Serial(PIO2_7, PIO2_8);
#endif

//SPI spi(SPI_PORT_0);

int blinkPin = PIO0_7;

//SHT2xClass SHT21;
Ds3231 rtc;

static const char APP_VERSION[] __attribute__((used)) = "Binary Input 1.1.21";

// Hardware version. Must match the product_serial_number in the VD's table hw_product
// find it in the knxprod XML file in parameter "LdCtrlCompareProp"
const unsigned char hardwareVersion[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x48};

M2_LABEL(hello_world_label, NULL, "Hello World");
M2tk m2(&hello_world_label, NULL, NULL, m2_gh_u8g_bfs);

void draw_menu(void) {
    m2.draw();
}


/*
 * Initialize the application.
 */
void setup() {

	bcu.setProgPin(PIN_PROG);

	bcu.begin(76, 0x474, 2);  // we are a MDT temperatur controller, version 1.2

	pinMode(blinkPin, OUTPUT);

	memcpy(userEeprom.order, hardwareVersion, sizeof(hardwareVersion));

	// Enable the serial port with 19200 baud, no parity, 1 stop bit
#ifdef _DEBUG__
	serial.begin(19200);
	serial.println("UC1701x Display Taster TEST");
#endif

	u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_hw_spi, u8g_com_hw_spi_fn);

	u8g_SetDefaultForegroundColor(&u8g);


	  /* connect u8glib with m2tklib */
	  m2_SetU8g(&u8g, m2_u8g_box_icon);

	  /* assign u8g font to index 0 */
	  m2.setFont(0, u8g_font_7x13);


}

/*
 * The main processing loop.
 */
void loop() {
	uint8_t temp_cycle=0;

	//uint8_t pos = 0;

//	temp_cycle = userEeprom.getUInt8(EE_BASE_ADDRESS + EE_ACTUAL_TEMP_SEND_CYCLIC);
//
//	/* picture loop */
//	u8g_FirstPage(&u8g);
//	do {
//		temperature_screen();
//	} while (u8g_NextPage(&u8g));


	  u8g_FirstPage(&u8g);
	  do {
	    draw_menu();
	  } while( u8g_NextPage(&u8g) );



//    draw_state++;
//    if ( draw_state >= 5*8 )
//      draw_state = 0;

	/* refresh screen after some delay */
//	u8g_Delay(100);

}

