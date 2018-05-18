#pragma once
#include <iostream>
using namespace std;

class Pixels {
private:
	unsigned int width, height; //The width and height of the image in pixels - stored as a 4-byte integer
	unsigned short colorDepth; //Color depth of the image: typical values are 1, 2, 4, 16, 24, 32 - stored as a two-bit integer
	unsigned char *values; //Values array
public:
	Pixels();
	Pixels(const unsigned char*, const unsigned int, const unsigned int);
	Pixels(const Pixels&);
	unsigned char& operator()(const unsigned, const unsigned);
	unsigned char& operator[](const unsigned);
	unsigned int getWidth();
	unsigned int getHeight();
	bool isFull();
	~Pixels();
	friend class BitmapImage;
};
ostream& operator<<(ostream &os, BitmapImage& im) {
	if (im.pixels.isFull()) {
		for (unsigned index = 0u; index < im.pixels.getWidth()* im.pixels.getHeight(); index++) {
			os << index << ": ";
			for (unsigned char color = 0u; color < 3u; color++) {
				os << im.pixels(index, color) << " ";
			}
			os << endl;
		}
	}
	return os;
}