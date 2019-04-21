/*
 * AckLed.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#include "ActLed.h"
#include "config.h"

ActLed::ActLed(uint8_t pin):
	pin(pin),
	queue(xQueueCreate(QUEUE_LENGTH, sizeof(uint8_t))) { // act led commands queue, each command is just a number of "blinks"
	pinMode (this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);
	printf("Setup activity LED, pin=%d\n", pin);
}

void ActLed::blink(uint8_t nTimes) {
	xQueueSend(queue,&nTimes,0); // send command to queue, no wait and ignore overflows
}

void ActLed::task(ActLed &inst) {
	uint8_t countdown = 0;
	uint8_t message = 0;
	while (true) {
		if(xQueueReceive(inst.queue, &message, DURATION)) {
			// got new command
			countdown = message;
			digitalWrite(inst.pin, HIGH);
		} else {
			// no new command
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
 * Static objects & methods
 */
ActLed LED = ActLed(ACT_PIN);
void actLedInit() {
	xTaskCreate((void(*)(void *))&ActLed::task, "Activity LED", STACK_SIZE, &LED, PRIORITY, NULL);
	printf("Activity LED task created\n");
}
