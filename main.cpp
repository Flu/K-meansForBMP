#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <unistd.h>

#include "bitmap.cpp"

template <class IntegralType>
class IntRandomEngine {
	IntegralType startRange, endRange;
	std::default_random_engine generator;
public:
	IntRandomEngine(const long long &startRange, const long long &endRange = std::numeric_limits<IntegralType>::max())
		: startRange(startRange), endRange(endRange) {}

	IntegralType getRandomNumber() {
		std::uniform_int_distribution<IntegralType> distribution(startRange, endRange); 
		IntegralType ret = distribution(this->generator);
		distribution.reset();
		return ret;
	}
};

struct Centroid;

struct Pixel {
	char r, g, b;
	Pixel() : r(0), g(0), b(0) {}
	Pixel(const char &r, const char &g, const char &n) : r(r), g(g), b(b) {}
	operator Centroid();
};

struct Centroid : public Pixel {
	Centroid() : Pixel() {}
	Centroid(const char &r, const char &g, const char &b) : Pixel(r, g, b) {}
};

Pixel::operator Centroid() {
	return Centroid(r, g, b);
}

long computeDistance(const Pixel &a, const Pixel &b) {
	return (a.r - b.r)*(a.r - b.r) + (a.g - b.g)*(a.g - b.g) + (a.b - b.b)*(a.b - b.b);
}

void chooseCentroids(Pixel* pixels, const long &numberOfPixels, const short &clusters) {
	IntRandomEngine<long> engine(0, numberOfPixels);

	Centroid *centroids = new Centroid[clusters];
	centroids[0] = pixels[engine.getRandomNumber()];

	long chosenCentroids = 1l;
	for (short clusterno = 0l; clusterno < clusters; clusterno++)
		for (long index = 0l; index < chosenCentroids; index++) {

	}
	
	delete[] centroids;
}

void printDetails(const BitmapImage& image) {
	std::cout << "The image has " << image.getWidth() << "x" << image.getHeight() << " pixels." << std::endl;
	std::cout << "The bit depth is " << image.getBitDepth() << " bits." << std::endl;
}

void startKmeans(const char* filename) {
	BitmapImage image(filename);
	image.readHeader();
	printDetails(image);
	image.readArray();

	long numberOfPixels = image.getWidth()*image.getHeight();
	Pixel *pixels = new Pixel[numberOfPixels];
	for (long index = 0; index < numberOfPixels*3; index += 3) {
		pixels[index/3].r = image[index];
		pixels[index/3].g = image[index + 1];
		pixels[index/3].b = image[index + 2];
	}
	
	chooseCentroids(pixels, numberOfPixels, 255);

	delete[] pixels;
	image.writeToFile("results/marbles.bmp");
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