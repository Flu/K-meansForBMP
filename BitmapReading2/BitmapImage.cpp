#include <iostream>
#include "BitmapImage.h"
#include "Pixels.h"
using namespace std;

BitmapImage::BitmapImage() {
	inputFile = NULL;
	header = NULL;
	pixels = NULL;
}
BitmapImage::BitmapImage(const char *path) {
	inputFile = fopen(path, "rb");
	if (!inputFile)
		exit(1); //invalid path or error opening file
	header = new unsigned char[_HEADER_SIZE];
	fread(header, sizeof(unsigned char), _HEADER_SIZE, inputFile);
	pixels = new Pixels;
	pixels->width = *(unsigned int*)&header[18];
	pixels->height = *(unsigned int*)&header[22];

	unsigned char **temp = new unsigned char*[pixels->width*pixels->height]; //Temporary matrix for pixel values
	if (!temp)
		exit(2); //bad allocation or not enogh memory
	for (unsigned index = 0u; index < pixels->width*pixels->height; index++) {
		temp[index] = new unsigned char[3];
		if (!temp[index])
			exit(2); //bad allocation or not enough memory
		fread(temp[index], sizeof(unsigned char), 3, inputFile);
	}
	fclose(inputFile); //Closes the file and disassociates it
	pixels = new Pixels((const unsigned char **)temp, pixels->width, pixels->height); //Creating anonymous object and assigning it to pixels, so now the image's pixel values are in pixels
	for (unsigned index = 0u; index < pixels->width*pixels->height; index++)
		delete[] temp[index];
	delete[] temp;
}
BitmapImage::~BitmapImage() {
	if (pixels) {
		for (unsigned index = 0u; index < pixels->width*pixels->height; index++)
			delete[] pixels->values[index];
		delete[] pixels->values;
	}
	if (header)
		delete[] header;
	if (inputFile)
		delete inputFile;
}