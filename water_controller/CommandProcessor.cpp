/*
 * CommandProcessor.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: ishabalov
 */

#include "CommandProcessor.h"
#include "config.h"

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

CommandProcessorCommand::CommandProcessorCommand(char *body, CommandProcessorCallback_t callback):
	body(body),
	callback(callback){
}

CommandProcessor::CommandProcessor():
	queue(xQueueCreate(QUEUE_LENGTH, sizeof(char*))) {
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
void version(CommandProcessorCommand &command,char *index[]) {
	char callbackBuffer[CALLBACK_BUFFER_SIZE];
	sprintf(callbackBuffer,"%s\n",WATER_VERSION);
}
void status(CommandProcessorCommand &command,char *index[]) {
	char callbackBuffer[CALLBACK_BUFFER_SIZE];
	sprintf(callbackBuffer,"Status:\n",WATER_VERSION);

}
void CommandProcessor::processCommand(CommandProcessorCommand &command) {
	printf("processing command %s\n",command.body);
	char *index[PARSER_BUFFER_SIZE];
	loadIndex(command.body,index);
	bool commandProcessed = false;
	switch (*index[0]) {
	case 'v':
	case 'V': version(command,index); commandProcessed = true; break;
	case 's':
	case 'S': status(command,index); commandProcessed = true; break;
	}
	if (commandProcessed) {
		LED.blink(1);
	} else {
		LED.blink(2);
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
}
/*
 * Singleton object & non-members methods
 */

void CommandProcessor::init(CommandProcessor &instance) {
	xTaskCreate((void(*)(void *))&CommandProcessor::task, "Activity LED", STACK_SIZE, &instance, PRIORITY, NULL);
	printf("Command processor task created\n");
}
