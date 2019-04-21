/*
 * UDPServer.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Wire.h>

#include "config.h"
#include "UDPServer.h"

UDPServer::UDPServer(char* ssid, char* password, uint16_t port, ActLed& led) :
	ssid(ssid),
	password(password),
	port(port),
	activityLed(led) {
	setup();
}


/* UDP Communications */

void UDPServer::setup() {
	printf("WiFi setup");
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		printf("Waiting for WiFi\n");
		delay(1000);
	}
	printf("WiFi setup success");
	while (!udp.listen(port)) {
		printf("Waiting for UDP bind\n");
		delay(1000);
	}
	printf("UDP Listening on IP: %s\n",WiFi.localIP());
//		blink(4);

	udp.onPacket((void)(AsyncUDPPacket&){});
//	udp.onPacket([](AsyncUDPPacket packet) {
//			handleUDPPacket(packet);
//	});
	}
}

void handleUDPPacket(AsyncUDPPacket& packet) {
	Serial.print("UDP Packet Type: ");
	Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
	Serial.print(", From: ");
	Serial.print(packet.remoteIP());
	Serial.print(":");
	Serial.print(packet.remotePort());
	Serial.print(", To: ");
	Serial.print(packet.localIP());
	Serial.print(":");
	Serial.print(packet.localPort());
	Serial.print(", Length: ");
	Serial.print(packet.length());
	Serial.print(", Data: ");
	Serial.write(packet.data(), packet.length());
	Serial.println();
	//reply to the client
	float temperrature = bmp.readTemperature();
	float pressure = bmp.readPressure();
	uint32_t last_timer = read_timer_last_millis();
	packet.printf("%s|%.2f|%.2f|%d", packet.data(),temperrature,pressure,last_timer);
	toggle();
	blink(1);
}
