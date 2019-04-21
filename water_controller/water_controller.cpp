#include <Arduino.h>

#include "water_controller.h"

/* Console */

void setup_console() {
	Serial.begin(SERIAL_BD);
}

/* General arduino core */
void setup() {
	setup_console();
	setup_bmp();
	setup_timer();
	setup_GPIO();
	setup_wifi();
	setup_udp_server();
}

void loop() {
	delay(2000);
	// read_timer();
	//  read_bmp();
}
