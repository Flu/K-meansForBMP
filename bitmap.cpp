#include "bitmap.hpp"

BitmapImage::BitmapImage(const char* filename) {
	this->stream = nullptr;
	width = height = 0;
	memset(header, 0, HEADER_SIZE*sizeof(char));

	if (!(this->stream = fopen(filename, "r")))
		throw "Invalid file";
}

int BitmapImage::readHeader() {
	if (!stream) {
		throw "Invalid file";
		return -1;
	}
	int bytesToRead = HEADER_SIZE;
	unsigned char* tempPtr = header;
	while (bytesToRead -= fread(tempPtr, sizeof(char), bytesToRead, this->stream))
		tempPtr += HEADER_SIZE - bytesToRead;
	
	this->width = *(int*)&header[18];
	this->height = *(int*)&header[22];
	return 0;
}

BitmapImage::~BitmapImage() {
	if (stream)
		if (fclose(stream) == EOF)
			throw strerror(errno);
}

const long& BitmapImage::getHeight() const {
	return this->height;
}

const long& BitmapImage::getWidth() const {
	return this->width;
}