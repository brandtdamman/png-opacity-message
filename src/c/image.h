#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <omp.h>
#include <png.h>

#include "encoding.h"

#define PNG_DEBUG

typedef struct image_t image_t;
struct image_t {
    const char* filename;
    int width;
    int height;
    int number_of_passes;

    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep* row_pointers;
};

// Credit to http://zarb.org/~gc/html/libpng.html for the beautiful example of PNG loading, processing, and writing.
void read_image(image_t** im_data, const char* file_name);
void encode_data(bin_data_t* bin_data, image_t* im_data, const int opacity,
                    const int thread_count);
void save(image_t* im_data, const char* file_name);

#endif