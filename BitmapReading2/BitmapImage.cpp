#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Pixels.h"
#include "BitmapImage.h"
using namespace std;

BitmapImage::BitmapImage() {
	inputFile = outputFile = NULL;
	header = NULL;
	pixels = NULL;
}
BitmapImage::BitmapImage(const char *pathToInput) {
	inputFile = fopen(pathToInput, "rb");
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
//Method for writing in a new file the pixel values and the header - if succesful, returns the number of bytes it had written, if not, returns
//0 if the arg is NULL, -1 if the path is invalid or the file couldn't be opened
int BitmapImage::writeToFile(const char* pathToOuput) {
	if (!pathToOuput)
		return 0;
	outputFile = fopen(pathToOuput, "wb");
	if (!outputFile)
		return -1;
	fwrite(header, sizeof(unsigned char), _HEADER_SIZE, outputFile);
	for (unsigned index = 0u; index < pixels->width*pixels->height; index++)
		fwrite((*pixels)[index], sizeof(unsigned char), 3, outputFile);
	fclose(outputFile);
	return pixels->width*pixels->height;
}
BitmapImage::~BitmapImage() {
	if (pixels) {
		for (unsigned index = 0u; index < pixels->width*pixels->height; index++)
			delete[] (*pixels)[index];
		delete[] pixels->values;
	}
	if (header)
		delete[] header;
	if (inputFile)
		delete inputFile;
}