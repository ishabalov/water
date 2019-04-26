#include <Arduino.h>

#include "config.h"
#include "ActLed.h"

/* Console */

void setup_console() {
	Serial.begin(SERIAL_BD);
}

ActLed LED = ActLed(ACT_LED_PIN);

/* General arduino core */
void setup() {
	setup_console();
	ActLed::actLedInit(LED);
	LED.blink(3);
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
