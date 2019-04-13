/*
 * Timer.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: ishabalov
 */

#include "Timer.h"

Timer::Timer() {
	timerSemaphore = xSemaphoreCreateBinary();
	// Use 1st timer of 4 (counted from zero).
	// Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
	// info).
	timer = timerBegin(0, 80, true);
	// Attach onTimer function to our timer.
	timerAttachInterrupt(timer, &Timer::interruptionHandler, true);
	// Set alarm to call onTimer function every second (value in microseconds).
	// Repeat the alarm (third parameter)
	timerAlarmWrite(timer, ALARM_INTERVAL , true);
	// Start an alarm
	timerAlarmEnable(timer);
}

bool Timer::alarmFired() {
	return xSemaphoreTake(timerSemaphore, 0) == pdTRUE;
}

uint32_t Timer::readLastAlarmMicros() {
	uint32_t ret;
	portENTER_CRITICAL_ISR(&timerMux);
	ret = lastAlarmMicros;
	portEXIT_CRITICAL_ISR(&timerMux);
	return ret;
}

void Timer::onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	this->lastAlarmMicros = micros();
	this->counter++;
	portEXIT_CRITICAL_ISR(&timerMux);
	xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

Timer instance = Timer();

//static IRAM_ATTR void interruptionHandler() { // @suppress("Unused static function")
//	instance.onTimer();
//}

