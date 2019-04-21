/*
 * Valve.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#include "Valve.h"
#include <Arduino.h>

Valve::Valve(uint8_t index, uint8_t pin) {
	this->index = index;
	this->pin = pin;
}

void Valve::init() {
	pinMode (this->pin, OUTPUT);
	off();
}

void Valve::on(unsigned long startingFrom, unsigned long durationMilliseconds) {
	if (durationMilliseconds>0) {
		digitalWrite(pin, HIGH);
		onStartingFromMillis = startingFrom;
		onDurationMillis = durationMilliseconds;
		printf("Valve [%d] is ON",index);
	}
}

void Valve::off() {
	digitalWrite(this->pin, LOW);
	onStartingFromMillis = 0;
	onDurationMillis = 0;
	printf("Valve [%d] is OFF",index);
}

void Valve::onTimer(unsigned long nowMilliseconds) {
	if (onStartingFromMillis>0) { // if we are in business
		if (nowMilliseconds<onStartingFromMillis) {
			// we have timer overflow here, need to adjust starting time, assuming it = 1, for simplicity
			onStartingFromMillis = 1; // NOT 0, otherwise we will never turn valve off
		}
		unsigned long delta = nowMilliseconds - onStartingFromMillis;
		if (delta>=onDurationMillis) {
			// need to turn valve off, interval exceeded
			off();
		}
	} // otherwise do nothing
}

// Static member functions
void Valve::initAll() {
	printf("Init all valves\n");
	for (int index=0;index<VALVES_COUNT;index++) {
		Valve v = Valve(VALVES_PINS[index]);
		v.init();
		Valve::ALL_VALVES[index]=v;
		printf("Init valve [%d] pin=%d\n",index,VALVES_PINS[index]);
	}
	printf("Init all valves completed\n");
}

void Valve::resetAll() {
	printf("reset all valves\n");
	for (int index=0;index<VALVES_COUNT;index++) {
		Valve::ALL_VALVES[index].off();
	}
	printf("reset all valves completed\n");
}

/*
 *
 * See for queue implementation https://www.freertos.org/a00118.html
 * add task with a loop that wait commands from the queue for ~100ms; if any command taken, execute it immediately.
 * otherwise do the timing logic; commands will be send into the queue from udp packets handler
 *
 *
 */


