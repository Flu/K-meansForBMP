#include "pixel.hpp"

class BitmapImage {
	Pixels values;
	long width, heigth;
	unsigned char header[40];
};