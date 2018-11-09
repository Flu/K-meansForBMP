#include <iostream>
#include <string.h>
#include <stdio.h>

class Pixel {
	unsigned char red, green, blue;

public:
	Pixel();
	explicit Pixel(const unsigned char&, const unsigned char&, const unsigned char&);
	Pixel(const Pixel&);
	unsigned char& operator[](const int&);
	const unsigned char& operator[](const int&) const;
};

class Pixels {
	Pixel *arrayValues;
	long long length;

public:
	Pixels();
	Pixels(const char *values);
	Pixel& operator[](const int&);
	const Pixel& operator[](const int&) const;
	~Pixels();
};