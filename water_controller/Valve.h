/*
 * Valve.h
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#ifndef VALVE_H_
#define VALVE_H_

#include <stdint.h>

class Valve {
public:
	Valve(uint8_t pin);
	void init();
	void on(uint64_t countdown);
	void off();
	void onTimer(uint64_t micros);
private:
	uint8_t pin = 0;
	unsigned long deadlineMicros = 0;
};

#endif /* VALVE_H_ */
