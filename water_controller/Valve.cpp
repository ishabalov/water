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
}

void Valve::on(uint64_t deadlineMicros) {
	digitalWrite(this->pin, HIGH);
	this->deadlineMicros = deadlineMicros;
}

void Valve::off() {
	digitalWrite(this->pin, LOW);
	this->deadlineMicros = 0;
}

void Valve::onTimer(uint64_t micros) {
	if (deadlineMicros>0 && micros>deadlineMicros) {
		// turn it off
		off();
	}
}



