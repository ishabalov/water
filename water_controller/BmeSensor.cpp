/*
 * BmeSensor.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#include "BmeSensor.h"

BmeSensor::BmeSensor(uint8_t bmeAddress) {
	this->setup_bme(bmeAddress);
}

float BmeSensor::readTemperrature() {
	return this->bme.readTemperature();
}
float BmeSensor::readPressure() {
	return this->bme.readPressure();
}
float BmeSensor::readHumidity() {
	return this->bme.readHumidity();
}

void BmeSensor::status(PrintBuffer *buffer) {
	buffer->printf("Temp.:%3.0f C, press.: %,5.0F P, hum.: %3.0f%\n",readTemperrature(),readPressure(),readHumidity());
}

void BmeSensor::setup_bme(uint8_t bmeAddress) {
	Serial.printf("Setup bme sensor begin, using address %x\n",bmeAddress);
	if (!bme.begin(bmeAddress)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
	} else {
		Serial.println("Successfully configured BME280 sensor");
	}
	Serial.println("Setup bme done");
}

