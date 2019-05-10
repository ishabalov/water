/*
 * Valve.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#include "Valve.h"
#include <Arduino.h>

Valve::Valve(){
	this->index=0;
	this->pin=0;
};

void Valve::setup(uint8_t index,uint8_t pin) {
	this->index=index;
	this->pin=pin;
	pinMode (this->pin, OUTPUT);
	off();
	printf("Valve [%d] initialized, pin=%d\n",index,pin);
}

void Valve::on(unsigned long startingFrom, unsigned long durationMilliseconds) {
	if (durationMilliseconds>0) {
		digitalWrite(pin, HIGH);
		turnedOnStartingFromMillis = startingFrom;
		tirnedOnDurationMillis = durationMilliseconds;
		printf("Valve [%d] is ON",index);
	}
}

void Valve::off() {
	digitalWrite(this->pin, LOW);
	turnedOnStartingFromMillis = 0;
	tirnedOnDurationMillis = 0;
	printf("Valve [%d] is OFF",index);
}

void Valve::onTimer(unsigned long nowMilliseconds) {
	if (turnedOnStartingFromMillis>0) { // if we are in business
		if (nowMilliseconds<turnedOnStartingFromMillis) {
			// we have timer overflow here, need to adjust starting time, assuming it = 1, for simplicity
			turnedOnStartingFromMillis = 1; // NOT 0, otherwise we will never turn valve off
		}
		unsigned long delta = nowMilliseconds - turnedOnStartingFromMillis;
		if (delta>=tirnedOnDurationMillis) {
			// need to turn valve off, interval exceeded
			off();
		}
	} // otherwise do nothing
}

Valves::Valves() {
	printf("Init all valves\n");
	for (int index=0;index<VALVES_COUNT;index++) {
		valves[index].setup(index,VALVES_PINS[index]);
		printf("Init valve [%d] pin=%d\n",index,VALVES_PINS[index]);
	}
	printf("Init all valves completed\n");
}

void Valves::resetAll() {
	printf("reset all valves\n");
	for (int index=0;index<VALVES_COUNT;index++) {
		valves[index].off();
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


