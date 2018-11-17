struct Centroid;
struct Pixel;

std::default_random_engine generator(rand());
std::uniform_int_distribution<int> distributionI(0,1419*1001 - 1);
std::uniform_real_distribution<long double> distributionR(0.l,1.l);

auto genI = std::bind(distributionI, generator);
auto genR = std::bind(distributionR, generator);

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