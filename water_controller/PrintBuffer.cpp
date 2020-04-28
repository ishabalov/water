/*
 * PrintBuffer.cpp
 *
 *  Created on: May 23, 2019
 *      Author: ishabalov
 */

#include "PrintBuffer.h"

PrintBuffer::PrintBuffer(size_t size) {
	this->size=size;
	this->buf = new char[size];
	reset();
}

void PrintBuffer::reset() {
	current=buf;
	*current=0;
	capacity=size;
}

char *PrintBuffer::get() {
	return buf;
}

void PrintBuffer::printf(const char *format, ...) {
	if (capacity>0) {
		va_list arg;
		va_start(arg, format);
		int offset  = vsnprintf(current,capacity,format,arg);
		va_end(arg);
		capacity-=offset;
		current+=offset;
	}
}

