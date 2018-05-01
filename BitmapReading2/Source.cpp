#include "Pixels.h"
#include "BitmapImage.h"
#include <iostream>
using namespace std;

int main() {
	BitmapImage image("VENUS.BMP");
	image.writeToFile("output.BMP");
	system("pause");
	return 0;
}