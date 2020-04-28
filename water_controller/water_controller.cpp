#include <Arduino.h>

#include <BluetoothSerial.h>

#include "config.h"
#include "ActLed.h"
#include "BmeSensor.h"
#include "Valve.h"
#include "CommandProcessor.h"


void setup_console() {
	Serial.begin(SERIAL_BD);
}

BluetoothSerial ESP_BT; //Object for Bluetooth


ActLed LED = ActLed(ACT_LED_PIN);
BmeSensor BME = BmeSensor(BME280_ADDRESS);
Valves VALVES = Valves();
CommandProcessor CP = CommandProcessor();



/* General arduino core */
void setup() {
	setup_console();
	ActLed::init(LED);
	CommandProcessor::init(CP);
	Valves::init(VALVES);
	LED.blink(3);
	ESP_BT.begin("water_2.0"); //Name of your Bluetooth Server

//	setup_bmp();
//	setup_timer();
//	setup_GPIO();
//	setup_wifi();
//	setup_udp_server();
}

void loop() {
	delay(2000);
	// read_timer();
	//  read_bmp();
}
