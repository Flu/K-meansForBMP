#include <iostream>
#include <unistd.h>

#include "bitmap.cpp"

void startKmeans(const char* filename) {
	BitmapImage image(filename);
	image.readHeader();

	std::cout << "Thr image has " << image.getWidth() << "x" << image.getHeight() << " pixels." << std::endl;
}

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cerr << "No arguments were given" << std::endl;
		return 1;
	}
	++argv;
	for (int iter = 0; iter < argc - 1; iter++) {
		startKmeans(argv[iter]);
	}
	return 0;
}