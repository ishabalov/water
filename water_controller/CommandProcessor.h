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
//
//class Command {
//public:
//	char verb();
//	int parameter_1();
//	int parameter_2();
//private:
//	char verb_[1];
//	char parameter_1_[2];
//	char parameter_2_[3];
//};


typedef void (*CommandProcessorCallback_t)(char *);
const int PARSER_BUFFER_SIZE = 32;
const int CALLBACK_BUFFER_SIZE = 4096;

class CommandProcessorCommand {
public:
	CommandProcessorCommand(char *body, CommandProcessorCallback_t callback);
private:
	char *body;
	const CommandProcessorCallback_t callback;
	friend class CommandProcessorCommandSplit;
	friend class CommandProcessor;
};

class CommandProcessor {
public:
	CommandProcessor();
	static void task(CommandProcessor &instance); // called from os Task Handler
	static void init(CommandProcessor &instance);
private:
	void loadIndex(char *body, char *index[]);

	const QueueHandle_t queue;
	void processCommand(CommandProcessorCommand &command);
	static const TickType_t DURATION = 1000 / portTICK_RATE_MS; // milliseconds
	static const int QUEUE_LENGTH = 2;
};

#endif /* COMMANDPROCESSOR_H_ */
