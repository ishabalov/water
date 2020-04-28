/*
 * CommandProcessor.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: ishabalov
 */

#include <ctype.h>

#include "CommandProcessor.h"
#include "config.h"
#include "ActLed.h"
#include "Valve.h"
#include "BmeSensor.h"


//
//char Command::verb() {
//	return verb_[0];
//}
//int Command::parameter_1() {
//	char buffer[3];
//	buffer[0] = parameter_1_[0];
//	buffer[1] = parameter_1_[1];
//	buffer[2] = 0;
//	return atoi(buffer);
//}
//int Command::parameter_2() {
//	char buffer[4];
//	buffer[0] = parameter_1_[0];
//	buffer[1] = parameter_1_[1];
//	buffer[2] = parameter_1_[2];
//	buffer[3] = 0;
//	return atoi(buffer);
//}
//

extern ActLed LED;
extern Valves VALVES;
extern BmeSensor BME;


CommandProcessorCommand::CommandProcessorCommand(char *body, CommandProcessorCallback_t callback):
	body(strlwr(body)),
	callback(callback){
}

CommandProcessor::CommandProcessor():
	queue(xQueueCreate(QUEUE_LENGTH, sizeof(char*))),
	callbackBuffer(CALLBACK_BUFFER_SIZE)
	{
	printf("Init command processor\n");
	Serial.println("Command processor is initialized");
}

void CommandProcessor::task(CommandProcessor &instance) {
	CommandProcessorCommand message(NULL,NULL);
	while (true) {
		if(xQueueReceive(instance.queue, &message, DURATION)) {
			instance.processCommand(message);
		}
	}
}
/*
 * Implementations of specific command processor functions
 */
void version(CommandProcessorCommand &command,char *index[], PrintBuffer *buffer) {
	buffer->printf("%s\n",WATER_VERSION);
}
void status(CommandProcessorCommand &command,char *index[], PrintBuffer *buffer) {
	VALVES.status(buffer);
	BME.status(buffer);
}

/*
 * Toggle valve
 * t(oggle) number [interval]/ t 1
 */
const ulong DEFAULT_TOGGLE_INTERVAL = 60000; // 1 min
void toggleValve(CommandProcessorCommand &command,char *index[], PrintBuffer *buffer) {
	int valve;
	ulong interval;
	if (index[1]!=NULL) {
		valve = strtol(index[1],NULL,10);
	} else {
		buffer->printf("Need to specify valve index\n");
		return;
	}
	if (index[2]!=NULL) {
		interval = strtol(index[2],NULL,10);
	} else {
		interval = DEFAULT_TOGGLE_INTERVAL;
	}
	VALVES.toggle(valve,interval);
}

/**
 * Turn all valves off
 */
void reset(CommandProcessorCommand &command,char *index[], PrintBuffer *buffer) {
	VALVES.resetAll();
}


/*
 * Main command processor parser
 */

/*
 * Create class/struct to hold buffer and use it
 */
void CommandProcessor::processCommand(CommandProcessorCommand &command) {
	printf("processing command %s\n",command.body);
	char *index[PARSER_BUFFER_SIZE];
	loadIndex(command.body,index);
	bool commanError = false;
	switch (*index[0]) {
	case 'v': version(command,index,&callbackBuffer); break;
	case 's': status(command,index,&callbackBuffer); break;
	case 't': toggleValve(command,index,&callbackBuffer); break;
	case 'r': reset(command,index,&callbackBuffer); break;
	default: commanError=true; break;
	}
	if (commanError) {
		LED.blink(2);
	} else {
		LED.blink(1);
	}
}
bool  isSpace(char c) {
	switch (c) {
	case ' ' :
	case '\n':
	case '\r':
	case '\t':
	case 0   : return true;
	default  : return false;
	}
}
void  CommandProcessor::loadIndex(char *body, char *index[]){
	int currentIndex=0;
	boolean isInTerm=false;
	while (*body) {
		if (isSpace(*body)) {
			*body=0;
			isInTerm=false;
		} else {
			if (!isInTerm) {
				if (currentIndex<PARSER_BUFFER_SIZE) { // ignore the rest of the line
					index[currentIndex]=body;
					currentIndex++;
				}
				isInTerm=true;
			}
		}
		body++;
	}
	while(currentIndex<PARSER_BUFFER_SIZE) {
		index[currentIndex]=NULL;
		currentIndex++;
	}
}
/*
 * Singleton object & non-members methods
 */

void CommandProcessor::init(CommandProcessor &instance) {
	xTaskCreate((void(*)(void *))&CommandProcessor::task, "Activity LED", STACK_SIZE, &instance, PRIORITY, NULL);
	printf("Command processor task created\n");
}
