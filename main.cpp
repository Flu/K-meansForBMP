/*
Proof of concept program used to show the capabilities of k-means++ clustering algorithm,
with applications in image processing, for compressing bitmap image files, by reducing the
number of colors in the image and constructin a pallette of primary colors.

The number of clusters set in the command line are the number of colors ultimately shown
in the final image.
Fluturel Adrian, (c) 2018
*/

#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <unistd.h>

#include "pixel.cpp"
#include "bitmap.cpp"
#include "kmeans.cpp"

void parseArgs(const int& argc, const char** argv) {
	// Parse and try to open any file given in the argument
	for (int iter = 0; iter < argc - 1; iter += 2) {
		try {
			startKmeans(argv[iter], std::stoi(argv[iter + 1], nullptr, 10));
		} catch(const char* err) {
			std::cerr << "Error happened with file " << argv[iter] << std::endl;
			std::cerr << err << std::endl;
		}
	}
}

// Computes squared Euclidean distance between two points
long computeDistance(const Pixel &a, const Pixel &b) {
	return (a.r - b.r)*(a.r - b.r) + (a.g - b.g)*(a.g - b.g) + (a.b - b.b)*(a.b - b.b);
}

// Image metadata gets printed to stdout
void printDetails(const BitmapImage& image) {
	std::cout << "The image has " << image.getWidth() << "x" << image.getHeight() << " pixels." << std::endl;
	std::cout << "The bit depth is " << image.getBitDepth() << " bits." << std::endl;
}

Pixel* loadPixels(const BitmapImage &image) {
	long numberOfPixels = image.getWidth()*image.getHeight();
	Pixel *pixels = new Pixel[numberOfPixels]; // Helper class for working with pixels
	for (long index = 0; index < numberOfPixels*3; index += 3) {
		pixels[index/3].r = image[index];
		pixels[index/3].g = image[index + 1];
		pixels[index/3].b = image[index + 2];
	}
	return pixels;
}

void unloadPixels(BitmapImage &image, const Pixel* pixels, const long& numberOfPixels) {
	for (long index = 0; index < numberOfPixels*3; index += 3) {
		image[index] = pixels[index/3].r;
		image[index + 1] = pixels[index/3].g;
		image[index + 2] = pixels[index/3].b;
	}
}

// Reads the file, calls the main k-means methods and writes the file back to disk
void startKmeans(const char* filename, const short& numberOfClusters) {
	BitmapImage image(filename);
	image.readHeader();
	printDetails(image);
	image.readArray();
	
	Pixel* pixels = loadPixels(image);
	long numberOfPixels = image.getWidth()*image.getHeight();
	Centroid* centroids = chooseCentroids(pixels, numberOfPixels, numberOfClusters);

	converge(pixels, numberOfPixels, centroids, numberOfClusters);
	unloadPixels(image, pixels, numberOfPixels);
	// Clean up useless buffers and write to disk
	delete[] pixels;
	delete[] centroids;
	image.writeToFile("results/marbles.bmp");
}

int main(int argc, const char** argv) {
	if (argc < 2) {
		std::cerr << "No arguments were given" << std::endl;
		return 1;
	}
	++argv;
	parseArgs(argc, argv);
	return 0;
}