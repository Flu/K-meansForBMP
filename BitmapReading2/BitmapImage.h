#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _HEADER_SIZE 54
#include <iostream>
#include "Pixels.h"
using namespace std;

class BitmapImage {
	FILE *inputFile, *outputFile;
	unsigned char *header;
	Pixels pixels;
public:
	BitmapImage();
	BitmapImage(const char*);
	int writeToFile(const char*);
	~BitmapImage();
	friend ostream& operator<<(ostream&, BitmapImage&);
};