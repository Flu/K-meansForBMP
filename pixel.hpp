/* This header presents the classes and methods for opening, reading and writing to
the bitmap file that kmeans++ will be used on.
Fluturel Adrian, (c) 2018
*/

#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>

class Pixels {
	char *arrayValues;
	long long length;

public:
	Pixels();
	Pixels(const char *values);
	char& operator[](const int&);
	const char& operator[](const int&) const;
	char* getArray() const;
	int readArray(FILE *stream, const long &bytesToRead);
	int writeArray(FILE *stream) const;
	~Pixels();
};