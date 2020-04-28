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
#include "PrintBuffer.h"

struct ValveCommand {
	char verb;
	uint8_t valveIndex;
	uint16_t duration;
};

class Valve {
public:
	Valve();
	void on(unsigned long startingFrom, unsigned long durationMilliseconds);
	void off();
	bool isOn();
	void onTimer(unsigned long nowMilliseconds);
	static void resetAll();
	static void initAll();
	void status(PrintBuffer *buffer);
	void toggle(ulong interval);

private:
	void setup(uint8_t index,uint8_t pin);
	uint8_t index;
	uint8_t pin;
	unsigned long turnedOnStartingFromMillis = 0;
	unsigned long tirnedOnDurationMillis = 0;
	friend class Valves;
};

class Valves {
public:
	Valves();
	void resetAll();
	void status(PrintBuffer *buffer);
	void toggle(uint8_t valveIndex, ulong interval);
	static void task(Valves &instance); // called from os Task Handler
	static void init(Valves &instance);
private:
	Valve valves[VALVES_COUNT];
};


#endif /* VALVE_H_ */
