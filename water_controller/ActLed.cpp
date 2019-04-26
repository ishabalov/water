/*
 * AckLed.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#include "ActLed.h"
#include "config.h"

ActLedQueueCommand::ActLedQueueCommand(uint8_t blinks) :
	blinks(blinks) {
}

ActLed::ActLed(uint8_t pin):
	pin(pin),
	queue(xQueueCreate(QUEUE_LENGTH, sizeof(ActLedQueueCommand))) { // act led commands queue, each command is just a number of "blinks"
	pinMode (this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);
	printf("Setup activity LED, pin=%d\n", pin);
}

void ActLed::blink(uint8_t blinks) {
	ActLedQueueCommand command(blinks);
	xQueueSend(queue,&command,0); // send command to queue, no wait and ignore overflows
}

void ActLed::task(ActLed &inst) {
	uint8_t countdown = 0;
	ActLedQueueCommand message(0);
	while (true) {
		if(xQueueReceive(inst.queue, &message, DURATION)) {
			// got new command
			countdown = message.blinks;
			digitalWrite(inst.pin, HIGH);
		} else {
			// no new command, just blinking
			if (digitalRead(inst.pin)) { // ON
				digitalWrite(inst.pin, LOW);
				countdown--;
			} else { // OFF
				if (countdown>0) {
					digitalWrite(inst.pin, HIGH);
				}
			}
		}
	}
}

/*
 * Singleton object & non-members methods
 */
ActLed LED = ActLed(ACT_LED_PIN);
void actLedInit() {
	xTaskCreate((void(*)(void *))&ActLed::task, "Activity LED", STACK_SIZE, &LED, PRIORITY, NULL);
	printf("Activity LED task created\n");
}
