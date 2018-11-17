#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <unistd.h>

#include "bitmap.cpp"
#include "kmeans.hpp"

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



// Normalizes vector - divides all the distances by their sum. Alternatively, you could divide them all
// by their maximum distance
void normalizeVector(long double* distances, const long &numberOfPixels, const long double& sum) {
	for (long index = 0; index < numberOfPixels; index++)
		distances[index] /= sum;
}

long double sumDistances(Pixel* pixels, const long &numberOfPixels, double long* dist, Centroid* centroids, short &chosenCentroids) {
	long double returnSum = 0.l;
	for (long px = 0l; px < numberOfPixels; px++) {
			// Now the coordinates for the closest centroid are stored in pixels[px]
			dist[px] = chooseClosestCentroid(pixels[px], centroids, chosenCentroids);
			returnSum += dist[px];
	}
	return returnSum;
}

// Chooses centroids with the k-means++ initialization method
Centroid* chooseCentroids(Pixel* pixels, const long &numberOfPixels, const short &clusters) {
	if (clusters < 2)
		throw "Should be a minimum of 2 clusters for this to work";

	// Choose random initial centroid
	Centroid *centroids = new Centroid[clusters];
	centroids[0] = pixels[genI()];

	short chosenCentroids = 1;
	for (short clusterno = 1; clusterno < clusters; clusterno++) {
		// Distances from every pixel to its nearest centroid and sum the distances
		long double *distances = new long double[numberOfPixels];
		long double sum = sumDistances(pixels, numberOfPixels, distances, centroids, chosenCentroids);

		normalizeVector(distances, numberOfPixels, sum);

		// Choose a real number between [0, 1] and iterate all the distances from every data point to
		// the closest cluster already chosen. Then, choose the first element in the list such that the sum
		// of the values in the normalized vector (here, distances) up to that element is greaten than or equal
		// to randNumber. That data point will be the next centroid
		long double randNumber = genR();

		long double normSum = 0.l;
		for (long pxIndex = 0l; pxIndex < numberOfPixels; pxIndex++) {
			normSum += distances[pxIndex];
			if (normSum >= randNumber) {
				centroids[clusterno] = pixels[pxIndex];
				chosenCentroids++;
				break;
			}
		} // End choosing centroid with probability D^2(x)

		delete[] distances;
	} // End choosing the next centroid loop
	
	return centroids;
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

// Reads the file, calls the main k-means methods and writes the file back to disk
void startKmeans(const char* filename) {
	BitmapImage image(filename);
	image.readHeader();
	printDetails(image);
	image.readArray();
	
	Pixel* pixels = loadPixels(image);
	long numberOfPixels = image.getWidth()*image.getHeight();
	Centroid* centroids = chooseCentroids(pixels, numberOfPixels, 10);
	for (short index = 0; index < 10; index++) {
		std::cout << "Centroid " << index << " is at ";
		std::cout << (int)centroids[index].r << " " << (int)centroids[index].g << " " << (int)centroids[index].b;
		std::cout << std::endl;
	}
	// Clean up useless buffers and write to disk
	delete[] pixels;
	delete[] centroids;
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