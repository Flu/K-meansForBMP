#include "Pixels.h"

//Default constructor
Pixels::Pixels() {
	values = NULL;
	width = height = 0u;
}
//Initialization constructor
Pixels::Pixels(const unsigned char **initValues) {
	if (!initValues)
		exit(1); //The arg pointer is null
	values = new unsigned char*[width*height];
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
//Constructor for pixel values array
Pixels::Pixels(const unsigned char*) {

}
//Copy constructor
Pixels::Pixels(const Pixels& obj) {

}
unsigned char& Pixels::operator()(const unsigned pos, const unsigned color) {
	if (pos < width*height && color < 3 && values)
		return values[pos][color];
	exit(1); //Position doesn't exist or pointer is NULL
}
unsigned char* Pixels::operator[](const unsigned pos) {
	if (pos < width*height && values)
		return values[pos];
		exit(1); //Position doesn't exist or pointer is NULL
}
//Destructor
Pixels::~Pixels() {
	if (values) {
		for (unsigned index = 0u; index < width*height; index++)
			delete[] values[index];
		delete[] values;
	}
}
