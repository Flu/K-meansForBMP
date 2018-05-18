#include "Pixels.h"
#include "BitmapImage.h"
#include <iostream>
using namespace std;

int main() {
	BitmapImage image("lonely3.BMP");
	//TODO Here will come the code for K-Means

	image.writeToFile("output.BMP");
	system("pause");
	return 0;
}