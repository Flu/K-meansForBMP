#include <iostream>
#include <string.h>
#include <stdio.h>

#include "pixel.hpp"

Pixel::Pixel() {
	red = green = blue = 0u;
}

Pixel::Pixel(const unsigned char& red, const unsigned char& green, const unsigned char& blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Pixel::Pixel(const Pixel& rvalue) {
	this->red = rvalue.red;
	this->green = rvalue.green;
	this->blue = rvalue.blue;
}

unsigned char& Pixel::operator[](const int &index) {
		if (index == 0)
			return red;
		if (index == 1)
			return green;
		if (index == 2)
			return blue;
		throw std::out_of_range("Wrong index - not defined");
	}

const unsigned char& Pixel::operator[](const int &index) const {
	if (index == 0)
		return red;
	if (index == 1)
		return green;
	if (index == 2)
		return blue;
	throw std::out_of_range("Wrong index - not defined");
}

Pixels::Pixels() {
	arrayValues = nullptr;
	length = 0;
}

Pixels::Pixels(const char* values) {
	this->arrayValues = nullptr;
	length = 0;

	if (values) {
		length = strlen(values)/3;
		this->arrayValues = new Pixel[length];
		if (!this->arrayValues)
			throw std::bad_alloc();
		for (unsigned int index = 0u; index < strlen(values); index += 3) {
			this->arrayValues[index][0] = values[index];
			this->arrayValues[index][1] = values[index + 1];
			this->arrayValues[index][2] = values[index + 2];
		}
	}
}

Pixel& Pixels::operator[](const int &index) {
	if (index < length && index >= 0)
		return this->arrayValues[index];
}

const Pixel& Pixels::operator[](const int &index) const {
	if (index < length && index >= 0)
		return this->arrayValues[index];
}

Pixels::~Pixels() {
	if (this->arrayValues)
		delete[] arrayValues;
}