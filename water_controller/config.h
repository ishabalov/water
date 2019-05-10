/*
 * config.h
 *
 *  Created on: Apr 11, 2019
 *      Author: ishabalov
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

/* Console */
const unsigned int SERIAL_BD = 115200;

/*
 * Valves, assigned pin numbers
 */
const int VALVES_COUNT = 10;
const uint8_t VALVES_PINS[VALVES_COUNT] = {25,26,19,23,18,5,10,9,35,34};

/*
 * Activity led pin
 */
const uint8_t ACT_LED_PIN = 2;

/*
 * BME sensor I2C address
 */
const uint8_t BME280_ADDRESS = 0x76; // Use alternative address, default is 0x77, but this mean connection of SDO pin to the ground;

/*
 * WIFI & UDP Server parameters
 */

//const char* SSID = "shabalov5";
//const char* PASSWORD = "zero07grow=";
//const unsigned int UDP_PORT = 18342;

/*
 * Internal configuration, do not change it unless needed
 */

const uint32_t STACK_SIZE = 8192;
const UBaseType_t PRIORITY = 1;

extern char* WATER_VERSION;

#endif /* CONFIG_H_ */
