/* Here are all the declarations of the functions and structs/classes necesarry 
for the k-means++ algorithm.
Fluturel Adrian, (c) 2018
*/

#pragma once
struct Centroid;
struct Pixel;

struct Pixel {
	char r, g, b;
	char rc, gc, bc;
	Pixel() : r(0), g(0), b(0) {}
	Pixel(const char &r, const char &g, const char &n) : r(r), g(g), b(b) {}
	operator Centroid();
};

struct Centroid : public Pixel {
	Centroid() : Pixel() {}
	Centroid(const char &r, const char &g, const char &b) : Pixel(r, g, b) {}
};

void startKmeans(const char*, const short&);
void converge(Pixel*, const Centroid*, const long&);