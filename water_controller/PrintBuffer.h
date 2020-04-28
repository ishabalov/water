/*
 * PrintBuffer.h
 *
 *  Created on: May 23, 2019
 *      Author: ishabalov
 */

#ifndef PRINTBUFFER_H_
#define PRINTBUFFER_H_

#include <Arduino.h>


class PrintBuffer {
public:
	PrintBuffer(size_t size);
	void reset();
	char *get();
	void printf(const char *format, ...);
private:
	char *buf;
	size_t size;
	char *current;
	size_t capacity;
};

#endif /* PRINTBUFFER_H_ */
