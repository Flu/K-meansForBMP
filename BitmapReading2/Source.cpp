#include "BitmapImage.h"

enum {
	red, green, blue
};

int main() {
	BitmapImage image("VENUS.BMP");
	//cout << image;
	int s[] = { 2, 5, 8 };
	cout << s[red] << " " << s[green] << " " << s[blue];
	system("pause");
	return 0;
}