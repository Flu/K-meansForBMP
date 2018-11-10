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
	short bytesToRead = HEADER_SIZE;
	unsigned char* tempPtr = header;
	while (bytesToRead -= fread(tempPtr, sizeof(char), bytesToRead, this->stream))
		tempPtr += HEADER_SIZE - bytesToRead;
	
	this->width = *(int*)&header[18];
	this->height = *(int*)&header[22];
	this->bitDepth = *(short*)&header[28];
	return 0;
}

long BitmapImage::readArray() {
	if (!this->stream)
		throw "Stream is empty";
	if (fseek(this->stream, 40, SEEK_SET) == -1)
		throw strerror(errno);
	
	long bytesToRead = this->width*this->height*(this->bitDepth/8);

	values.readArray(stream, bytesToRead);
	return bytesToRead;
}

inline char& BitmapImage::operator[](const int& index) {
	return values[index];
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

const short& BitmapImage::getBitDepth() const {
	return this->bitDepth;
}