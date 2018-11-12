#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <unistd.h>

#include "bitmap.cpp"
#include "kmeans.hpp"

// Returns random number in range [startRange, endRange] of integral type
template<typename IntegralType>
IntegralType IntRandomEngine<IntegralType>::getRandomNumber() {
		std::uniform_int_distribution<IntegralType> distribution(startRange, endRange); 
		IntegralType ret = distribution(this->generator);
		distribution.reset();
		return ret;
	}

// Converts a Pixel to a Centroid implicitly if needed (downcast operator)
Pixel::operator Centroid() {
	return Centroid(r, g, b);
}

// Computes squared Euclidean distance between two points
long computeDistance(const Pixel &a, const Pixel &b) {
	return (a.r - b.r)*(a.r - b.r) + (a.g - b.g)*(a.g - b.g) + (a.b - b.b)*(a.b - b.b);
}

// Calculates distance from pixel to every chosen centroid, returns the minimum
long chooseClosestCentroid(Pixel &pixel, const Centroid* centers, const short &centersChosen) {
	long min = std::numeric_limits<long>::max();
	for (short centerIndex = 0; centerIndex < centersChosen; centerIndex++)
		if (long currDistance = computeDistance(pixel, centers[centerIndex]); currDistance < min) {
			min = currDistance;
			pixel.rc = centers[centerIndex].r;
			pixel.gc = centers[centerIndex].g;
			pixel.bc = centers[centerIndex].b;
		}
	return min;
}

// Chooses centroids with the k-means++ initialization method
void chooseCentroids(Pixel* pixels, const long &numberOfPixels, const short &clusters) {
	IntRandomEngine<long> engine(0, numberOfPixels);

	Centroid *centroids = new Centroid[clusters];
	centroids[0] = pixels[engine.getRandomNumber()];

	short chosenCentroids = 1l;
	for (short clusterno = 1; clusterno < clusters; clusterno++) {
		double *distances = new double[numberOfPixels]; // Distances from every pixel to its nearest centroid
		for (long px = 0l; px < numberOfPixels; px++) {
			// Now the coordinates for the closest centroid are stored in pixels[px]
			distances[px] = chooseClosestCentroid(pixels[px], centroids, chosenCentroids);
		}

		delete[] distances;
	}
	
	delete[] centroids;
}

// Image metadata gets printed to stdout
void printDetails(const BitmapImage& image) {
	std::cout << "The image has " << image.getWidth() << "x" << image.getHeight() << " pixels." << std::endl;
	std::cout << "The bit depth is " << image.getBitDepth() << " bits." << std::endl;
}

// Reads the file, calls the main k-means methods and writes the file back to disk
void startKmeans(const char* filename) {
	BitmapImage image(filename);
	image.readHeader();
	printDetails(image);
	image.readArray();

	long numberOfPixels = image.getWidth()*image.getHeight();
	Pixel *pixels = new Pixel[numberOfPixels]; // Helper class for working with pixels
	for (long index = 0; index < numberOfPixels*3; index += 3) {
		pixels[index/3].r = image[index];
		pixels[index/3].g = image[index + 1];
		pixels[index/3].b = image[index + 2];
	}
	
	chooseCentroids(pixels, numberOfPixels, 50);

	// Clean up useless buffers and write to disk
	delete[] pixels;
	image.writeToFile("results/marbles.bmp");
}

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cerr << "No arguments were given" << std::endl;
		return 1;
	}

	++argv;

	// Parse and try to open any file given in the argument
	for (int iter = 0; iter < argc - 1; iter++) {
		try {
		startKmeans(argv[iter]);
		} catch (const char* err) {
			std::cerr << err << std::endl;
		}
	}
	return 0;
}