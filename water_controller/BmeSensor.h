/*
 * BmeSensor.h
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#ifndef BMESENSOR_H_
#define BMESENSOR_H_

#include <Adafruit_BME280.h>
#include <Arduino.h>

#include "PrintBuffer.h"

class BmeSensor {
public:
	BmeSensor(uint8_t bmeAddress);
	float readTemperrature();
	float readPressure();
	float readHumidity();
	void status(PrintBuffer *buffer);
private:
	Adafruit_BME280 bme; // Use default I2C GPIO: 21(SDA) 22(SCL)
	void setup_bme(uint8_t bmeAddress);
};

#endif /* BMESENSOR_H_ */
