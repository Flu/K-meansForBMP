#include "pixel.cpp"

#define HEADER_SIZE 40
#define DIB_SIZE 14

class BitmapImage {
	Pixels values;
	long width, height;
	short bitDepth;
	char header[HEADER_SIZE+DIB_SIZE];
	FILE* stream;

public:
	explicit BitmapImage(const char* filename);
	int readHeader();
	long readArray();
	int writeToFile(const char *filename) const;
	char& operator[](const int &index);
	~BitmapImage();

	const long& getHeight() const;
	const long& getWidth() const;
	const short& getBitDepth() const;
};