/*
 * Valve.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#include "Valve.h"
#include <Arduino.h>

Valve::Valve(uint8_t pin) {
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
	}
}

void Valve::off() {
	digitalWrite(this->pin, LOW);
	onStartingFromMillis = 0;
	onDurationMillis = 0;
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
void Valve::initAllValves() {
	ALL_VALVES[0]=Valve(VALLVE_0_PIN);
	ALL_VALVES[1]=Valve(VALLVE_1_PIN);
	ALL_VALVES[2]=Valve(VALLVE_2_PIN);
	ALL_VALVES[3]=Valve(VALLVE_3_PIN);
	ALL_VALVES[4]=Valve(VALLVE_4_PIN);
	ALL_VALVES[5]=Valve(VALLVE_5_PIN);
	ALL_VALVES[6]=Valve(VALLVE_6_PIN);
	ALL_VALVES[7]=Valve(VALLVE_7_PIN);
	ALL_VALVES[8]=Valve(VALLVE_8_PIN);
	ALL_VALVES[9]=Valve(VALLVE_9_PIN);
}

void Valve::resetAllValves() {
	for (int index=0;index<VALVES_COUNT;index++) {
		Valve::ALL_VALVES[index].off();
	}
}

/*
 *
 * See for queue implementation https://www.freertos.org/a00118.html
 * add task with a loop that wait commands from the queue for ~100ms; if any command taken, execute it immediately.
 * otherwise do the timing logic; commands will be send into the queue from udp packets handler
 *
 *
 */


