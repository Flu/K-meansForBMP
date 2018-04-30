#include "BitmapImage.h"
#include "Pixels.h"

BitmapImage::BitmapImage() {
	inputFile = NULL;
	pixelValues = NULL;
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

	unsigned char* tmp = new unsigned char[3 * pixels->width*pixels->height];
	fread(tmp, sizeof(unsigned char), 3 * pixels->width*pixels->height, inputFile);

	pixelValues = new unsigned char*[pixels->width*pixels->height]; //matrix for pixel values of size width*height x 3
	if (!pixelValues)
		exit(2); //bad allocation or not enogh memory
	for (unsigned index = 0u; index < pixels->width*pixels->height; index++) {
		pixelValues[index] = new unsigned char[3];
		if (!pixelValues[index])
			exit(2); //bad allocation or not enough memory
	}
	//pixelValues takes the info from tmp - now every pixel's RGB value is stored in a matrix with width*height columns and 3 lines
	for (unsigned index = 0u, index2 = 0u; index < pixels->width*pixels->height; index++, index2 = 3u * index) {
		pixelValues[index][0] = tmp[index2];
		pixelValues[index][1] = tmp[index2 + 1];
		pixelValues[index][2] = tmp[index2 + 2];
	}
	pixels = new Pixels(pixelValues, pixels->width, pixels->height);
}
BitmapImage::~BitmapImage() {
	if (pixels) {
		for (unsigned index = 0u; index < pixels->width*pixels->height; index++)
			delete[] pixelValues[index];
		delete[] pixelValues;
	}
	if (header)
		delete[] header;
	if (inputFile)
		delete inputFile;
}