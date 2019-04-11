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

void Valve::resetAllValves() {
	for (int index=0;index<VALVES_COUNT;index++) {
		allValves[index].off();
	}
}

Valve allValves[VALVES_COUNT] = {
		Valve(VALLVE_0_PIN),
		Valve(VALLVE_1_PIN),
		Valve(VALLVE_2_PIN),
		Valve(VALLVE_3_PIN),
		Valve(VALLVE_4_PIN),
		Valve(VALLVE_5_PIN),
		Valve(VALLVE_6_PIN),
		Valve(VALLVE_7_PIN),
		Valve(VALLVE_8_PIN),
		Valve(VALLVE_9_PIN)
};

