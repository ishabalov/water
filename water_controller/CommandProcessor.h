/*
 * CommandProcessor.h
 *
 *  Created on: Apr 21, 2019
 *      Author: ishabalov
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include "config.h"
#include "ActLed.h"


class CommandProcessor {
public:
	CommandProcessor();
private:
	const ActLed led;
	const Valve[VALVES_COUNT] valves;
};

#endif /* COMMANDPROCESSOR_H_ */
