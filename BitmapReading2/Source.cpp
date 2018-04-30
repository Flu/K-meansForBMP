#include "Pixels.h"
#include "BitmapImage.h"
#include <iostream>
using namespace std;

int main() {
	BitmapImage image("VENUS.BMP");
	std::cout << image;

	system("pause");
	return 0;
}