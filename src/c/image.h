#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <omp.h>
#include <png.h>

#define PNG_DEBUG

// Credit to http://zarb.org/~gc/html/libpng.html for the beautiful example of PNG loading, processing, and writing.
void read_image();

#endif