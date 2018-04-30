#include "BitmapImage.h"
#include "Pixels.h"

enum {
	red, green, blue
};
ostream& operator<<(ostream &os, BitmapImage& im) {
	if (im.pixels) {
		for (unsigned index = 0u; index < im.pixels->width*im.pixels->height; index++) {
			os << index << ": ";
			for (unsigned char color = 0u; color < 3u; color++) {
				os << (unsigned int)im.pixelValues[index][color] << " ";
			}
			os << endl;
		}
	}
	return os;
}

int main() {
	BitmapImage image("VENUS.BMP");
	//cout << image;
	int s[] = { 2, 5, 8 };
	cout << s[red] << " " << s[green] << " " << s[blue];
	system("pause");
	return 0;
}