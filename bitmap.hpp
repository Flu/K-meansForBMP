#include "pixel.cpp"

#define HEADER_SIZE 40

class BitmapImage {
	Pixels values;
	long width, height;
	short bitDepth;
	unsigned char header[HEADER_SIZE + 1];
	FILE* stream;
public:
	explicit BitmapImage(const char* filename);
	int readHeader();
	long readArray();
	char& operator[](const int &index);
	~BitmapImage();

	const long& getHeight() const;
	const long& getWidth() const;
	const short& getBitDepth() const;
};