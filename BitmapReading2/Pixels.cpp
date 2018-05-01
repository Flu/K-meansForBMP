using namespace std;
#include <iostream>
#include "BitmapImage.h"
#include "Pixels.h"
using namespace std;

//Default constructor
Pixels::Pixels() {
	values = NULL;
	width = height = 0u;
}
//Initialization constructor
Pixels::Pixels(const unsigned char **initValues, const unsigned int width, const unsigned int height) {
	if (!initValues)
		exit(1); //The arg pointer is null
	values = new unsigned char*[width*height];
	this->width = width;
	this->height = height;
	if (!values)
		exit(2); //Allocation error
	for (unsigned index = 0u; index < width*height; index++) {
		values[index] = new unsigned char[3];
		if (!values[index])
			exit(2); //Allocation error
		for (unsigned color = 0u; color < 3u; color++)
			values[index][color] = initValues[index][color];
	}
}
//Copy constructor
Pixels::Pixels(const Pixels& obj) {
	if (values) { //check if this->values is allocated. If it is, delete it
		for (unsigned index = 0u; index < width*height; index++)
			delete[] values[index];
		delete[] values;
	}
	this->width = obj.width;
	this->height = obj.height;
	if (!obj.values) //check if obj has values
		this->values = NULL;
	values = new unsigned char*[width*height];
	if (!values)
		exit(1); //Bad allocation
	for (unsigned index = 0u; index < width*height; index++) { //transfer info from obj to *this
		values[index] = new unsigned char[3];
		if (!values[index])
			exit(1); //Bad allocation
		for (unsigned char color = 0u; color < 3u; color++)
			values[index][color] = obj.values[index][color];
	}	
}
//Return a color value from pixel number pos
unsigned char& Pixels::operator()(const unsigned pos, const unsigned color) {
	if (pos < width*height && color < 3 && values)
		return values[pos][color];
	exit(1); //Position doesn't exist or pointer is NULL
}
//Returns a 3-element array with the RGB values of pixel pos
unsigned char* Pixels::operator[](const unsigned pos) {
	if (pos < width*height && values)
		return values[pos];
		exit(1); //Position doesn't exist or pointer is NULL
}
//ostream& operator<<(ostream &os, BitmapImage& im) {
//	if (im.pixels) {
//		for (unsigned index = 0u; index < im.pixels->width* im.pixels->height; index++) {
//			os << index << ": ";
//			for (unsigned char color = 0u; color < 3u; color++) {
//				os << (unsigned int)im.pixels->values[index][color] << " ";
//			}
//			os << endl;
//		}
//	}
//	return os;
//}
//Destructor
Pixels::~Pixels() {
	if (values) {
		for (unsigned index = 0u; index < width*height; index++)
			delete[] values[index];
		delete[] values;
	}
}
