/*
 *  Copyright (c) 2016 Oliver Stefan <os252@gmx.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 */

#include <sblib/core.h>
#include <sblib/eib/user_memory.h>
#include <sblib/timeout.h>
#include <sblib/eib/com_objects.h>
#include "app_temp_control.h"
#include "params.h"
#include "temperature.h"
#include "air.h"



const byte* functionsParams = userEepromData + (EE_FUNCTIONS_PARAMS_BASE - USER_EEPROM_START);
const byte* TimingParams = userEepromData + (EE_TIMING_PARAMS_BASE - USER_EEPROM_START);

struct temp temp_values;
struct air air_values;

bool external_temp_sensor_active = false;

unsigned int factortime_to_ms(unsigned int startaddress) {
	uint8_t time_factor, time_unit;
	unsigned int result = 1000; //start at 1s = 1000ms
	time_factor = userEeprom[startaddress] & 0x3F; // Bits 0..5 are the factor
	time_unit   = userEeprom[startaddress] & 0xC0; // Bits 6..7 are the unit of time (0=sec, 1=min, 2=hours)

	for(uint8_t i = 0; i<time_unit; i++){
		result *= 60; //calculate the factor (0*60 = sec, 1*60=min, 2*60=hours)
	}
	return (result *= time_factor);

}

void initApplication(void) {
	if (userEeprom[EE_FUNCTIONS_PARAMS_BASE] & TEMPERATURE_FUNCTION_ACTIVE) {
		temp_values.sendInterval = factortime_to_ms(EE_TIMING_PARAMS_BASE);
		temp_values.autoResetTime = factortime_to_ms(EE_TIMING_PARAMS_BASE + 1);
	}

	if (userEeprom[EE_FUNCTIONS_PARAMS_BASE] & AIR_VALUES_ACTIVE) {
		air_values.sendIntervall = factortime_to_ms(EE_TIMING_PARAMS_BASE + 2);
	}

	if (userEeprom[EE_FUNCTIONS_PARAMS_BASE] & EXTERN_TEMP_SENSOR) {
		external_temp_sensor_active = true;
		//TODO set input for external sensor
	}
}

// handle external-set-temperature, window state, ventilation state
void objectUpdated(int objno) {
	if(objno == REC_WINDOW_STATE){
		int value = objectRead(objno);
	}

}

// send values periodic (temperature internal, temperature external, temperature set value, air quality, air humidity)
void handlePeriodic(void) {

	if (timeout[TEMPERATURES].expired()) {
		// send temperature internal, temperature external, temperature set value
		objectWriteFloat(SEND_INTERN_TEMP, temp_values.tempIntern);
		objectWriteFloat(SEND_SET_TEMP, temp_values.set_temp);
		if(external_temp_sensor_active){
			objectWriteFloat(SEND_EXT_TEMP, temp_values.tempExtern);
		}
		timeout[TEMPERATURES].start(temp_values.sendInterval);
	}

	if (timeout[AIR_VALUES].expired()) {
		// send air quality, air humidity
		objectWriteFloat(SEND_AIR_QUALITY, air_values.airVOC);
		objectWriteFloat(SEND_AIR_HUMIDITY, air_values.airRH);
		timeout[AIR_VALUES].start(air_values.sendIntervall);
	}
}

// initiate changes on Display
void inputChanged(int channel, int val) {

}
