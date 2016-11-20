/*
 *  Copyright (c) 2016 Oliver Stefan <MAIL>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 */
#ifndef AIR_H
#define AIR_H

struct air_values{
	unsigned int sendIntervall;
	unsigned short airVOC;
	unsigned short airRH;
};

extern struct air_values air;


#endif
