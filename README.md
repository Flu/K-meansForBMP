# K-means algorithm for bitmap files
Algorithm that reads a bitmap file and applies k-means to it to reduce the number of colors. It doesn't do any actual compression, just demonstrates k-means (at least for now).

## Choosing an image
When executing from the command line, you must put two arguments, one with the absolute or relative paths to the image you want to input and the number of clusters the data should be divided in. For example, after ```cd```-ing in the project's root directory, run:
```bash
$ ./a.out images/nature.bmp 50
```
Which has the effect of segmenting the color data of the nature.bmp image found in the results folder into 50 clusters of data, and writing a new file with the new color values.

## Please be warned

* Any attempt to use a non-standard bitmap format (that doesn't have the BITMAPINFOHEADER) or that already has a color pallette, will probably result in weird results and/or errors.
* The resulting image will be saved to disk in the results/ directory in the root project directory.

## Example images

![Before](images/nature.bmp)
![After, 50 colors](results/nature.bmp)
