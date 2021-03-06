/* This header presents the classes and methods for opening, reading and writing to
the bitmap file that kmeans++ will be used on.
Fluturel Adrian, (c) 2018
*/

#pragma once

#include <stdio.h>

#include "pixel.hpp"

#define HEADER_SIZE 40
#define DIB_SIZE 14

class BitmapImage {
	Pixels values;
	long width, height;
	short bitDepth;
	char header[HEADER_SIZE+DIB_SIZE];
	FILE* stream;

public:
	explicit BitmapImage(const char* filename);
	int readHeader();
	long readArray();
	int writeToFile(const char *filename) const;
	char& operator[](const int &index);
	const char& operator[](const int &index) const;
	~BitmapImage();

	const long& getHeight() const;
	const long& getWidth() const;
	const short& getBitDepth() const;
};