/*
 * CommandProcessor.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: ishabalov
 */

#include "CommandProcessor.h"

#include "config.h"

char Command::verb() {
	return verb_[0];
}
int Command::parameter_1() {
	char buffer[3];
	buffer[0] = parameter_1_[0];
	buffer[1] = parameter_1_[1];
	buffer[2] = 0;
	return atoi(buffer);
}
int Command::parameter_2() {
	char buffer[4];
	buffer[0] = parameter_1_[0];
	buffer[1] = parameter_1_[1];
	buffer[2] = parameter_1_[2];
	buffer[3] = 0;
	return atoi(buffer);
}


CommandProcessor::CommandProcessor():
		led(ACT_LED_PIN),
		valves(Valve::ALL_VALVES),
		queue(xQueueCreate(QUEUE_LENGTH, sizeof(Command))) {
}

