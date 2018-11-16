struct Centroid;
struct Pixel;

template <class IntegralType>
class IntRandomEngine {
	IntegralType startRange, endRange;
	std::default_random_engine generator;
public:
	IntRandomEngine(const IntegralType &startRange, const IntegralType &endRange = std::numeric_limits<IntegralType>::max())
		: startRange(startRange), endRange(endRange) {}
		IntegralType getRandomNumber();
};

template<class RealType>
class RealRandomEngine {
	RealType startRange, endRange;
	std::default_random_engine generator;
public:
	RealRandomEngine(const RealType &startRange, const RealType &endRange = std::numeric_limits<RealType>::max())
		: startRange(startRange), endRange(endRange) {}
	RealType getRandomNumber();
};

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