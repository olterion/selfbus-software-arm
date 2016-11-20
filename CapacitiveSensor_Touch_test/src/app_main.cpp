#include <LPC11xx.h>                               // LPC11xx definitions
#include "CapacitiveSensor.h"
#include <sblib/serial.h>
#include <sblib/timer.h>
#include <sblib/eib/sblib_default_objects.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(); // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
Serial Serial(PIO2_7, PIO2_8);

void setup() {
	bcu.setProgPin(PIN_PROG);
	//SystemInit();
	//SysTick_Config(SystemCoreClock / 100);           // generate interrupt each 10 ms
	serial.begin(19200);
	serial.println("WS2803 Taster TEST");
}

void loop() {
	long start = millis();
	long total1 = cs_4_2.capacitiveSensor(30);
	//		long total2 = cs_4_6.capacitiveSensor(30);
	//		long total3 = cs_4_8.capacitiveSensor(30);

	serial.println((unsigned int) (millis() - start));        // check on performance in milliseconds
	serial.print("\r");                    // tab character for debug windown spacing

	serial.print((unsigned int) total1);                  // print sensor output 1
	serial.print("\r");
	//		serial.print(total2);                  // print sensor output 2
	//		serial.print("\r");
	//		serial.println(total3);                // print sensor output 3

	delay(100);                             // arbitrary delay to limit data to serial port

}
