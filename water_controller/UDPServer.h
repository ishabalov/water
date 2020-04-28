/*
 * UDPServer.h
 *
 *  Created on: Apr 20, 2019
 *      Author: ishabalov
 */

#ifndef UDPSERVER_H_
#define UDPSERVER_H_

#include "ActLed.h"

class UDPServer {
public:
	UDPServer(char* ssid, char* password, uint16_t port);
	int status(char *callbackBuffer, size_t bufferSize);

private:
	static const TickType_t DELAY = 1000 / portTICK_RATE_MS;

	const char* ssid;
	const char* password;
	const uint16_t port;
	// infrastructure members
	AsyncUDP udp;
	void setup();
	static void udpPacketHandler(AsyncUDPPacket& packet);
};

#endif /* UDPSERVER_H_ */
