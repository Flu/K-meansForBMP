#pragma once
#include "bitmap.hpp"

BitmapImage::BitmapImage(const char* filename) {
	this->stream = nullptr;
	width = height = 0;
	memset(header, 0, (HEADER_SIZE+DIB_SIZE)*sizeof(char));

	if (!(this->stream = fopen(filename, "r")))
		throw "Invalid file";
}

int BitmapImage::readHeader() {
	if (!stream) {
		throw "Invalid file";
		return -1;
	}
	short bytesToRead = HEADER_SIZE + DIB_SIZE;
	char* tempPtr = header;
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
	if (fseek(this->stream, HEADER_SIZE + DIB_SIZE, SEEK_SET) == -1)
		throw strerror(errno);
	
	long bytesToRead = this->width*this->height*(this->bitDepth/8);

	values.readArray(stream, bytesToRead);
	fclose(this->stream);
	return bytesToRead;
}

inline char& BitmapImage::operator[](const int& index) {
	return values[index];
}

inline const char& BitmapImage::operator[](const int& index) const {
	return values[index];
}

int BitmapImage::writeToFile(const char* filename) const {
	if (!filename)
		throw "Invalid filename";
	FILE* outputStream = fopen(filename, "w");
	if (!outputStream)
		throw strerror(errno);

	if (!header)
		throw "Header wasn't read";
	if (fwrite(header, sizeof(char), HEADER_SIZE + DIB_SIZE, outputStream) != HEADER_SIZE + DIB_SIZE)
		throw "Error writing header";

	int ret = values.writeArray(outputStream);
	if (ret == -2)
		throw "Byte array was empty";
	if (ret == 0)
		throw strerror(errno);
	
	fclose(outputStream);
}

BitmapImage::~BitmapImage() {
	if (stream)
		fclose(this->stream);
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