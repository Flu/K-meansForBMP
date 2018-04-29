#include "BitmapImage.h"

BitmapImage::BitmapImage() {
	inputFile = NULL;
	pixelValues = NULL;
	header = NULL;
	imageHeight = imageWidth = numberOfPixels = 0u;
}
BitmapImage::BitmapImage(const char *path) {
	inputFile = fopen(path, "rb");
	if (!inputFile)
		exit(1); //invalid path or error opening file
	header = new unsigned char[_HEADER_SIZE];
	fread(header, sizeof(unsigned char), _HEADER_SIZE, inputFile);
	imageWidth = *(unsigned int*)&header[18];
	imageHeight = *(unsigned int*)&header[22];

	unsigned char* tmp = new unsigned char[3 * imageWidth*imageHeight];
	fread(tmp, sizeof(unsigned char), 3 * imageWidth*imageHeight, inputFile);

	pixelValues = new unsigned char*[imageWidth]; //matrix for pixel values of size width x height
	if (!pixelValues)
		exit(2); //bad allocation or not enogh memory
	for (unsigned index = 0u; index < imageWidth; index++) {
		pixelValues[index] = new unsigned char[imageHeight];
		if (!pixelValues[index])
			exit(2); //bad allocation or not enough memory
	}
	for (unsigned indexI = 0u; indexI < imageWidth; indexI++)
		for (unsigned indexJ = 0u; indexJ < imageHeight; indexJ++) {
			
		}
}