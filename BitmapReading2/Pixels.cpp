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
Pixels::Pixels(const unsigned char *initValues, const unsigned int width, const unsigned int height) {
	if (!initValues)
		exit(1); //The arg pointer is null
	values = new unsigned char[3*width*height];
	if (!values)
		exit(2); //Allocation error
	for (unsigned int index = 0u; index < 3 * width*height; index++)
		values[index] = *(unsigned char*)&initValues[index];
	this->width = width;
	this->height = height;
}
//Copy constructor
Pixels::Pixels(const Pixels& obj) {
	if (values) { //check if this->values is allocated. If it is, delete it
		delete[] values;
	}
	this->width = obj.width;
	this->height = obj.height;
	if (!obj.values) //check if obj has values
		this->values = NULL;
	values = new unsigned char[3*width*height];
	if (!values)
		exit(1); //Bad allocation
	for (unsigned index = 0u; index < width*height; index++) //transfer info from obj to *this
		values[index] = obj.values[index];
}
//Return a color value from pixel number pos
unsigned char& Pixels::operator()(const unsigned pos, const unsigned color) {
	if (pos < width*height && color < 3 && values) //If all is within bounds, then the value requested is returned
		return values[pos/3 + color];
	exit(1); //Position doesn't exist or pointer is NULL
}
//Returns a 3-element array with the RGB values of pixel pos
unsigned char& Pixels::operator[](const unsigned pos) {
	if (pos < 3*width*height && values)
		return values[pos];
		exit(1); //Position doesn't exist or pointer is NULL
}
//Getter for image width in pixels
unsigned int Pixels::getWidth() {
	return this->width;
}
//Getter for image height in pixels;
unsigned int Pixels::getHeight() {
	return this->height;
}
bool Pixels::isFull() {
	return (values == NULL ? false : true);
}
//Destructor
Pixels::~Pixels() {
	if (values) {
		delete[] values;
	}
}
