/*
 * Timer.h
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>

void IRAM_ATTR staticTimer();


class Timer {
public:
	Timer();
	boolean alarmFired();
	uint32_t readLastAlarmMicros();

	static IRAM_ATTR void interruptionHandler();

private:
	hw_timer_t* timer = NULL;
	volatile uint64_t counter = 0;
	volatile uint64_t lastAlarmMicros = 0;
	volatile SemaphoreHandle_t timerSemaphore;
	portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
	const unsigned long ALARM_INTERVAL = 100000;
	void IRAM_ATTR onTimer();

};



#endif /* TIMER_H_ */
