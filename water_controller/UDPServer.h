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
	UDPServer(char* ssid, char* password, uint16_t p, ActLed& led);
private:
	const char* ssid;
	const char* password;
	const uint16_t port;

	AsyncUDP udp;

	// Internal links
	const ActLed& activityLed;

	void setup();
};

#endif /* UDPSERVER_H_ */
