#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _HEADER_SIZE 54
#include <iostream>
#include <functional>
#include <math.h>
#include <fstream>

class BitmapImage {
protected:
	FILE *inputFile;
	unsigned int imageHeight, imageWidth, numberOfPixels;
	unsigned char *header, **pixelValues;
public:
	BitmapImage();
	BitmapImage(const char*);
	~BitmapImage();
};

