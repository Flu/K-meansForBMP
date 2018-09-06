#include "Pixels.h"
#include "BitmapImage.h"
#include <iostream>
using namespace std;

int main() {
	BitmapImage image("marbles.bmp");
	//TODO Here will come the code for K-Means

	cout << image.writeToFile("output.BMP") << endl;
	system("pause");
	return 0;
}