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

#include <sblib/core.h>
#include <sblib/ioports.h>
#include <sblib/spi.h>
#include <sblib/serial.h>
#include <sblib/eib/sblib_default_objects.h>
#include "timer32.h"

#define LEDS 18

#define _DEBUG__

#define TIMER32_0_STEP 10 //unit: ms Schrittweite der Dimmung (1..100)
#define SENSOR_TIMER_100MS 100/TIMER32_0_STEP //100ms/Timerschritte
#define LED_DIMM_TIME 500 //unit: ms Gesamtzeit der Dimmung
#define LED_DIMM_STEPS LED_DIMM_TIME/TIMER32_0_STEP //Anzahl Schritte der Dimmung
#define MAX_LED_ON_TIME 3500 //unit: ms Zeit, die die LED nach Dimmen an sein soll

void spi_send(uint8_t *);

SPI spi(SPI_PORT_0);

struct rgb_led{
	uint8_t blau;
	uint8_t rot;
	uint8_t gruen;
};

struct rgb_led rgb_leds[6];

int blinkPin = PIO0_7;

uint8_t rgb_buffer_ist[LEDS];
uint8_t rgb_buffer_soll[LEDS];
struct dimmrampe{
	int16_t steigung;
	uint8_t nullstelle;
};

struct dimmrampe dimmrampen[LEDS];

volatile uint8_t flag_sens_pos = 0;
volatile uint8_t flag_sens_neg = 0;
volatile uint8_t flag_dimmen = 0;
volatile uint8_t flag_led_on = 0;

volatile int differenz_median = 0;
volatile int timer32_0_cnt = 0;
volatile int led_on_time = 0;
volatile int wert_ohne_LED = 0;
volatile int dimm_steps_cnt = 0;

#ifdef _DEBUG__
Serial Serial(PIO2_7, PIO2_8);
#endif

void TIMER32_0_IRQHandler(void) {

	LPC_TMR32B0->IR = 1; /* clear interrupt flag */

	//Dimmung der RGB Leds
	if(flag_dimmen == 1){
		dimm_steps_cnt++;
		uint8_t flag_val_changed = 0;
		for(uint8_t i=0; i<LEDS; i++){
			if(rgb_buffer_ist[i] != rgb_buffer_soll[i]){
				rgb_buffer_ist[i] = ((dimmrampen[i].steigung * dimm_steps_cnt) / 100) + dimmrampen[i].nullstelle;
				flag_val_changed = 1;
			}
		}
		if(flag_val_changed == 0){
			flag_dimmen = 0;
			dimm_steps_cnt = 0;
		}
	}
	if(flag_led_on == 1){
		led_on_time += TIMER32_0_STEP;
	}
	if(led_on_time == MAX_LED_ON_TIME){
		flag_sens_neg = 1;
		led_on_time = 0;
	}
	spi_send(rgb_buffer_ist);


// 	Annäherungssensor auslesen und auswerten
// 	alle 100ms wird der ADC ausgelesen (5* -> Mittelwert)
//	jeweils 50ms versetzt wird die IR-LED ein- und ausgeschaltet
	if (timer32_0_cnt == SENSOR_TIMER_100MS/2) { //alle 100ms die Sensorabfrage durchführen

		wert_ohne_LED = 0;

		delayMicroseconds(100);
		for (int i = 0; i < 5; i++) {
			wert_ohne_LED += analogRead(AD3);
		}

		digitalWrite(PIO3_2, 0); //IR LED ein

		wert_ohne_LED /= 5;
	}
	if (timer32_0_cnt == SENSOR_TIMER_100MS) {

		timer32_0_cnt = 0; //100ms Sekungen Zähler rücksetzen

		int wert_mit_LED = 0;
		int differenz_temp = 0;

		delayMicroseconds(100);
		for (int i = 0; i < 5; i++) {
			wert_mit_LED += analogRead(AD3);
		}

		digitalWrite(PIO3_2, 1); //IR LED aus

		wert_mit_LED /= 5;

		differenz_temp = wert_mit_LED - wert_ohne_LED;

		differenz_median = differenz_median * 4 + differenz_temp;

		differenz_median /= 5;

#ifdef _DEBUG__
		serial.println(wert_ohne_LED);
		serial.println(wert_mit_LED);
		serial.println(differenz_temp);
		serial.println("");
#endif

		if (differenz_temp - differenz_median > 60) {
#ifdef _DEBUG__
			serial.println("positive Flanke erkannt!");
#endif
			flag_sens_pos = 1;
		} //else if (differenz_temp - differenz_median > 20) {
//			differenz_median = differenz_temp;
//			serial.println("negative Flanke erkannt!");
//			//flag_sens_neg = 1;
//		}
	}

	timer32_0_cnt++;

	return;
}

/*
 * Initialize the application.
 */
void setup() {
	bcu.setProgPin(PIN_PROG);

	pinMode(blinkPin, OUTPUT);

	pinMode(PIO0_2, OUTPUT | SPI_SSEL);
	pinMode(PIO0_9, OUTPUT | SPI_MOSI);
	pinMode(PIO0_6, OUTPUT | SPI_CLOCK);

	spi.setClockDivider(128);
	spi.begin();

	analogBegin();
	pinMode(PIO1_2, INPUT_ANALOG);

	pinMode(PIO3_2, OUTPUT); //IR LED
	digitalWrite(PIO3_2, 0);

	// Enable the serial port with 19200 baud, no parity, 1 stop bit
#ifdef _DEBUG__
	serial.begin(19200);
	serial.println("WS2803 Taster TEST");
#endif
	for (int i = 0; i < LEDS; i++) {
		rgb_buffer_ist[i] = 0;
	}

	for(uint8_t i=0; i<LEDS; i+=3){
		rgb_leds[i/3].blau  = i;
		rgb_leds[i/3].rot   = i+1;
		rgb_leds[i/3].gruen = i+2;
	}

	// Initialise Timer32_0 to tick at rate of 1/100th of second.
	// Default clock speed set up by CMSIS SystemInit function
	// (SystemCoreClock) - is 48MHz or 48000000 Hz. Dividing this
	// by 100 is 480000.
	// Note by default LPC_SYSCON->SYSAHBCLKDIV is 1.
	init_timer32(0, ((SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV) / (1000 / TIMER32_0_STEP)));

	/* Turn timer on */
	enable_timer32(0);
}

void spi_send(uint8_t *value) {
	for (int Out = 0; Out < LEDS; Out++) {
		spi.transfer(value[Out]);
	}
	delayMicroseconds(600);
}

/*
 * The main processing loop.
 */
void loop() {

	if(flag_sens_pos && !flag_dimmen){
		for(uint8_t i=0; i<LEDS/3; i++){
			rgb_buffer_soll[rgb_leds[i].blau] = 255;
			rgb_buffer_soll[rgb_leds[i].rot] = 20;
			rgb_buffer_soll[rgb_leds[i].gruen] = 150;
		}

		for(uint8_t i=0; i<LEDS; i++){
			dimmrampen[i].steigung = ((rgb_buffer_soll[i] - rgb_buffer_ist[i]) * 100)/(LED_DIMM_TIME/TIMER32_0_STEP);
			dimmrampen[i].nullstelle = rgb_buffer_ist[i];
		}
		flag_sens_pos = 0;
		flag_dimmen = 1;
		flag_led_on = 1;
	}

	if(flag_sens_neg && !flag_dimmen){
		for(uint8_t i=0; i<LEDS; i++){
			rgb_buffer_soll[i] = 0x00;
		}

		for(uint8_t i=0; i<LEDS; i++){
			dimmrampen[i].steigung = ((rgb_buffer_soll[i] - rgb_buffer_ist[i]) * 100)/(LED_DIMM_TIME/TIMER32_0_STEP);
			dimmrampen[i].nullstelle = rgb_buffer_ist[i];
		}
		flag_sens_neg = 0;
		flag_dimmen = 1;
		flag_led_on = 0;
	}
}

