#include "kmeans.hpp"

// Converts a Pixel to a Centroid implicitly if needed (downcast operator)
Pixel::operator Centroid() {
	return Centroid(r, g, b);
}

// Algorithm used for converging to the optimal solution
void converge(Pixel* pixels, const Centroid* centroids, const long &numberOfPixels) {

}