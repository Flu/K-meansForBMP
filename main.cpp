#include <iostream>
#include <unistd.h>

#include "bitmap.cpp"

void printDetails(const BitmapImage& image) {
	std::cout << "The image has " << image.getWidth() << "x" << image.getHeight() << " pixels." << std::endl;
	std::cout << "The bit depth is " << image.getBitDepth() << " bits." << std::endl;
}

void startKmeans(const char* filename) {
	BitmapImage image(filename);
	image.readHeader();
	printDetails(image);
	image.readArray();

	for (int index = 0; index < image.getHeight(); index++) {
		image[index*image.getWidth()] = 255;
		image[index*image.getWidth()+ 1] = 255;
		image[index*image.getWidth()+ 2] = 210;
	}
	image.writeToFile("results/marbles_TEST.bmp");
}

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cerr << "No arguments were given" << std::endl;
		return 1;
	}

	++argv;

	for (int iter = 0; iter < argc - 1; iter++) {
		try {
		startKmeans(argv[iter]);
		} catch (const char* err) {
			std::cerr << err << std::endl;
		}
	}
	return 0;
}