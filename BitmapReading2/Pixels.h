#pragma once
#include <iostream>
using namespace std;

class Pixels {
private:
	unsigned int width, height;
	unsigned char **values;
public:
	Pixels();
	Pixels(const unsigned char**, const unsigned int, const unsigned int);
	Pixels(const Pixels&);
	unsigned char& operator()(const unsigned, const unsigned);
	unsigned char* operator[](const unsigned);
	~Pixels();
	friend class BitmapImage;
	friend ostream& operator<<(ostream&, BitmapImage&);
};