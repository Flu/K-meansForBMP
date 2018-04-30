#pragma once
#include <iostream>
#include "BitmapImage.h"
using namespace std;

class Pixels : protected BitmapImage {
protected:
	unsigned int width, height;
	unsigned char **values;
public:
	Pixels();
	Pixels(const unsigned char**);
	Pixels(const unsigned char*);
	Pixels(const Pixels&);
	unsigned char& operator()(const unsigned, const unsigned);
	unsigned char* operator[](const unsigned);
	~Pixels();
};

