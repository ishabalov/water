/*
 * Valve.h
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#ifndef VALVE_H_
#define VALVE_H_

#include <stdint.h>
#include "config.h"

class Valve {
public:
	Valve(uint8_t pin);
	void init();
	void on(unsigned long startingFrom, unsigned long durationMilliseconds);
	void off();
	void onTimer(unsigned long nowMilliseconds);
	static void resetAllValves();

private:
	uint8_t pin = 0;
	unsigned long onStartingFromMillis = 0;
	unsigned long onDurationMillis = 0;
};

const int VALVES_COUNT = 10;
Valve allValves[];

#endif /* VALVE_H_ */
