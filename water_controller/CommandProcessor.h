/*
 * CommandProcessor.h
 *
 *  Created on: Apr 22, 2019
 *      Author: ishabalov
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include <Arduino.h>
#include "config.h"

#include "ActLed.h"
#include "Valve.h"

class Command {
public:
	char verb();
	int parameter_1();
	int parameter_2();
private:
	char verb_[1];
	char parameter_1_[2];
	char parameter_2_[3];
};

class CommandProcessor {
public:
	CommandProcessor();
private:
	const ActLed led;
	const Valve valves[VALVES_COUNT];
	const QueueHandle_t queue;
	static const TickType_t DURATION = 1000 / portTICK_RATE_MS; // milliseconds
	static const int QUEUE_LENGTH = 2;
};

#endif /* COMMANDPROCESSOR_H_ */
