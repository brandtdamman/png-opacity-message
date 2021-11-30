#include "image.h"

void read_image(image_t** im_data, const char* file_name) {
    *im_data = (image_t*)malloc(sizeof(image_t));
    (*im_data)->filename = file_name;

    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stdout, " File %s could not be opened for reading", file_name);
        exit(1);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fprintf(stdout, " File %s is not recognized as a PNG file", file_name);
        exit(1);
    }

    (*im_data)->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!(*im_data)->png_ptr) {
        fprintf(stdout, " png_create_read_struct failed");
        exit(1);
    }

    (*im_data)->info_ptr = png_create_info_struct((*im_data)->png_ptr);
    if (!(*im_data)->info_ptr) {
        fprintf(stdout, " png_create_info_struct failed");
        exit(1);
    }

    if (setjmp(png_jmpbuf((*im_data)->png_ptr))) {
        fprintf(stdout, " Error during init_io");
        exit(1);
    }

    png_init_io((*im_data)->png_ptr, fp);
    png_set_sig_bytes((*im_data)->png_ptr, 8);

    png_read_info((*im_data)->png_ptr, (*im_data)->info_ptr);

    (*im_data)->width = png_get_image_width((*im_data)->png_ptr, (*im_data)->info_ptr);
    (*im_data)->height = png_get_image_height((*im_data)->png_ptr, (*im_data)->info_ptr);
    (*im_data)->color_type = png_get_color_type((*im_data)->png_ptr, (*im_data)->info_ptr);
    (*im_data)->bit_depth = png_get_bit_depth((*im_data)->png_ptr, (*im_data)->info_ptr);

    (*im_data)->number_of_passes = png_set_interlace_handling((*im_data)->png_ptr);
    png_read_update_info((*im_data)->png_ptr, (*im_data)->info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf((*im_data)->png_ptr))) {
        fprintf(stdout, " Error during read_image");
    }

    (*im_data)->row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*im_data)->height);
    int y;
    for (y = 0; y < (*im_data)->height; y++)
        (*im_data)->row_pointers[y] = (png_byte*) malloc(png_get_rowbytes((*im_data)->png_ptr, (*im_data)->info_ptr));

    png_read_image((*im_data)->png_ptr, (*im_data)->row_pointers);

    fclose(fp);
}

void encode_data(bin_data_t* bin_data, double im_data) {
    //
}

