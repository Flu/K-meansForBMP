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

	pixelValues = new unsigned char*[imageWidth*imageHeight]; //matrix for pixel values of size width*height x 3
	if (!pixelValues)
		exit(2); //bad allocation or not enogh memory
	for (unsigned index = 0u; index < imageWidth*imageHeight; index++) {
		pixelValues[index] = new unsigned char[3];
		if (!pixelValues[index])
			exit(2); //bad allocation or not enough memory
	}
	//pixelValues takes the info from tmp - now every pixel's RGB value is stored in a matrix with width*height columns and 3 lines
	for (unsigned index = 0u, index2 = 0u; index < imageWidth*imageHeight; index++, index2 = 3 * index) {
		pixelValues[index][0] = tmp[index2];
		pixelValues[index][1] = tmp[index2 + 1];
		pixelValues[index][2] = tmp[index2 + 2];
	}
		
}
ostream& operator<<(ostream &os, BitmapImage& im) {
	if (im.pixelValues) {
		for (unsigned index = 0u; index < im.imageWidth*im.imageHeight; index++) {
			os << index << ": ";
			for (unsigned char color = 0u; color < 3u; color++) {
				os << (unsigned int)im.pixelValues[index][color] << " ";
			}
			os << endl;
		}
	}
	return os;
}
BitmapImage::~BitmapImage() {
	if (pixelValues) {
		for (unsigned index = 0u; index < imageWidth*imageHeight; index++)
			delete[] pixelValues[index];
		delete[] pixelValues;
	}
	if (header)
		delete[] header;
	if (inputFile)
		delete inputFile;
}