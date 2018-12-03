#include "init.cpp"
#include "kmeans.hpp"

// Converts a Pixel to a Centroid implicitly if needed (downcast operator)
Pixel::operator Centroid() {
	return Centroid(r, g, b);
}

// Algorithm used for converging to the optimal solution
void converge(Pixel* pixels, const long &numberOfPixels, Centroid* centroids, const short& clusterNumber) {
	constexpr short maxIter = 200;
	for (short iteration = 0; iteration < maxIter; iteration++) {
		// Choose closest centroid to every pixel
		for (long pxIndex = 0l; pxIndex < numberOfPixels; pxIndex++)
			chooseClosestCentroid(pixels[pxIndex], centroids, clusterNumber);
		// For every centroid, find the pixels closest to it (check the pointer from every pixel)
		// and calculate their average
		// TODO: A look-up table for every centroid (Pixel**) might speed up stuff
		for (short centroidIndex = 0; centroidIndex < clusterNumber; centroidIndex++) {
			long pixelCount = 0l; // Number of pixels found for a single centroid
			long redSum = 0l, greenSum = 0l, blueSum = 0l; // Sum of all colors, to be averaged
			for (long pxIndex = 0; pxIndex < numberOfPixels; pxIndex++) {
				if (pixels[pxIndex].nearestCenter == &centroids[centroidIndex]) {
					pixelCount++;
					redSum += pixels[pxIndex].r;
					blueSum += pixels[pxIndex].b;
					greenSum += pixels[pxIndex].g;
				}
			} // End of summing loop
			if (pixelCount != 0) {
				centroids[centroidIndex].r = redSum/pixelCount;
				centroids[centroidIndex].g = greenSum/pixelCount;
				centroids[centroidIndex].b = blueSum/pixelCount;
			}
		} // End of recalculating the centroids, starting over
	} // End of all iterations and the end of k-means

	// Time to rewrite the pixel values with the centroid ones
	for (long pxIndex = 0l; pxIndex < numberOfPixels; pxIndex++) {
		chooseClosestCentroid(pixels[pxIndex], centroids, clusterNumber);
		pixels[pxIndex].r = pixels[pxIndex].nearestCenter->r;
		pixels[pxIndex].g = pixels[pxIndex].nearestCenter->g;
		pixels[pxIndex].b = pixels[pxIndex].nearestCenter->b;
	}
}