#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Pixels.h"
#include "BitmapImage.h"
using namespace std;

BitmapImage::BitmapImage() {
	inputFile = outputFile = NULL;
	header = NULL;
}
BitmapImage::BitmapImage(const char *pathToInput) {
	inputFile = fopen(pathToInput, "rb");
	if (!inputFile)
		exit(1); //Invalid path or error opening file
	header = new unsigned char[_HEADER_SIZE];
	fread(header, sizeof(unsigned char), _HEADER_SIZE, inputFile);

	pixels.width = *(int*)&header[18];
	cout << pixels.width << " ";
	pixels.height = *(int*)&header[22];
	cout << pixels.height << " ";
	pixels.colorDepth = *(unsigned short*)&header[28];
	if (pixels.colorDepth != 24)
		exit(2);
	pixels.values = new unsigned char[3 * pixels.width*pixels.height];
	if (fread(pixels.values, sizeof(unsigned char), 3 * pixels.width*pixels.height, inputFile) != 3 * pixels.width*pixels.height)
		exit(3); //Error reading file
	fclose(inputFile); //Closes the file and disassociates it
}
//Method for writing in a new file the pixel values and the header - if succesful, returns the number of bytes it had written, if not, returns
//0 if the arg is NULL, -1 if the path is invalid or the file couldn't be opened
int BitmapImage::writeToFile(const char* pathToOuput) {
	if (!pathToOuput)
		return 0;
	outputFile = fopen(pathToOuput, "wb");
	if (!outputFile) {
		cout << "Eroare deschidere fisier scriere" << endl;
		return -1;
	}
	fwrite(header, sizeof(unsigned char), _HEADER_SIZE, outputFile);
	unsigned long long index;
	bool succes = true;
	for (index = 0ul; index < 3*pixels.width*pixels.height; index++) {
		if (fwrite(&pixels[index], sizeof(unsigned char), 1, outputFile) != 1)
			succes = false;
	}
	cout << index << " " << succes << endl;
	fclose(outputFile);
	return pixels.width*pixels.height;
}
BitmapImage::~BitmapImage() {
	if (header) 
		delete[] header;
}