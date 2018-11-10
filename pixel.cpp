#include <iostream>
#include <string.h>
#include <stdio.h>

#include "pixel.hpp"

Pixels::Pixels() {
	arrayValues = nullptr;
	length = 0;
}

Pixels::Pixels(const char* values) {
	this->arrayValues = nullptr;
	length = 0;

	if (values) {
		this->length = strlen(values);
		if (!(this->arrayValues = new char[length]))
			throw std::bad_alloc();
		memcpy(this->arrayValues, values, length*sizeof(char));
	}
}

int Pixels::readArray(FILE *stream, const long &bytesToRead) {
	if (!stream)
		throw "Invalid stream";
	this->length = bytesToRead;
	this->arrayValues = new char[this->length];
	long ret;
	ret = fread(this->arrayValues, sizeof(char), bytesToRead, stream);
	if (ret == 0)
		throw strerror(errno);
	if (ret < bytesToRead)
		throw std::out_of_range("Didn't read all bytes");
}

char& Pixels::operator[](const int &index) {
	if (index < length && index >= 0)
		return this->arrayValues[index];
}

const char& Pixels::operator[](const int &index) const {
	if (index < length && index >= 0)
		return this->arrayValues[index];
}

char* Pixels::getArray() const {
	return this->arrayValues;
}

Pixels::~Pixels() {
	if (this->arrayValues)
		delete[] arrayValues;
}