#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _HEADER_SIZE 54
#include "Pixels.h"
#include <iostream>
#include <functional>
using namespace std;

class BitmapImage {
protected:
	FILE *inputFile;
	unsigned char *header, **pixelValues;
	Pixels *pixels;
public:
	BitmapImage();
	BitmapImage(const char*);
	~BitmapImage();
	friend ostream& operator<<(ostream&, BitmapImage&);
};

