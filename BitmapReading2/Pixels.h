#pragma once
#include <iostream>
using namespace std;

class Pixels {
	unsigned int width, height;
	unsigned char **values;
public:
	Pixels();
	Pixels(unsigned char**, unsigned int, unsigned int);
	Pixels(const unsigned char*);
	Pixels(const Pixels&);
	unsigned char& operator()(const unsigned, const unsigned);
	unsigned char* operator[](const unsigned);
	~Pixels();
	friend class BitmapImage;
	friend ostream& operator<<(ostream&, BitmapImage&);
};

