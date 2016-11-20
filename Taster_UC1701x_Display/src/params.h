/*
 *  Copyright (c) 2016 Oliver Stefan <os252@gmx.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 */
#ifndef params_h
#define params_h

// Eeprom base address
#define EE_BASE_ADDRESS 0x4400

// Eeprom address: Send  actual temperature cyclically (not send = 0 or value: 1,2,3,4,5,10,15,20,30,40,50,60 min)
// size: 8 bit
#define EE_ACTUAL_TEMP_SEND_CYCLIC 361

// Eeprom address: Send actual temperature value after change of (not send = 0, steps 0,1K, range: 0,1K - 2.0K)
#define EE_ACTUAL_TEMP_SEND_CHANGE 363

// Eeprom address: Send setpoint at change (no = 0, yes = 1)
#define EE_SETPOINT_TEMP_SEND 407

#endif
