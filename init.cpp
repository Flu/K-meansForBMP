#include "kmeans.hpp"
#include "bitmap.hpp"
#include "init.hpp"

// Calculates distance from pixel to every chosen centroid, returns the minimum
long chooseClosestCentroid(Pixel &pixel, Centroid* centers, const short &centersChosen) {
	long min = std::numeric_limits<long>::max();
	for (short centerIndex = 0; centerIndex < centersChosen; centerIndex++)
		if (long currDistance = computeDistance(pixel, centers[centerIndex]); currDistance < min) {
			min = currDistance;
			pixel.nearestCenter = &centers[centerIndex];
		}
	return min;
}

// Normalizes vector - divides all the distances by their sum. Alternatively, you could divide them all
// by their maximum distance
void normalizeVector(long double* distances, const long &numberOfPixels, const long double& sum) {
	for (long index = 0; index < numberOfPixels; index++)
		distances[index] /= sum;
}

// Sums up the distances from the distances vector
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