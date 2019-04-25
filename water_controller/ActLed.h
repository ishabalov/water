/*
 * AckLed.h
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#ifndef ACTLED_H_
#define ACTLED_H_

#include <Arduino.h>

class ActLed {
public:
	ActLed(uint8_t pin);
	void blink(uint8_t nTimes);
	static void task(ActLed &inst); // called from os Task Handler
	static void actLedInit(ActLed &instance);
private:
	const uint8_t pin;
	const QueueHandle_t queue;
	static const TickType_t DURATION = 100 / portTICK_RATE_MS; // milliseconds
	static const int QUEUE_LENGTH = 2;
};


#endif /* ACTLED_H_ */
