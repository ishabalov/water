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
	Valve(uint8_t index, uint8_t pin);
	void on(unsigned long startingFrom, unsigned long durationMilliseconds);
	void off();
	void onTimer(unsigned long nowMilliseconds);
	static void resetAll();
	static void initAll();

private:
	const uint8_t index;
	const uint8_t pin;
	unsigned long onStartingFromMillis = 0;
	unsigned long onDurationMillis = 0;

	// Static structure for array of existing valves
	static Valve ALL_VALVES[VALVES_COUNT];
};


#endif /* VALVE_H_ */
