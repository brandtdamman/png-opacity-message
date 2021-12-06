#include "image.h"

void read_image(image_t **im_data, const char *file_name)
{
    *im_data = (image_t *)malloc(sizeof(image_t));
    (*im_data)->filename = file_name;

    unsigned char header[8]; // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
    {
        fprintf(stdout, " File %s could not be opened for reading", file_name);
        exit(1);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stdout, " File %s is not recognized as a PNG file", file_name);
        exit(1);
    }

    (*im_data)->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!(*im_data)->png_ptr)
    {
        fprintf(stdout, " png_create_read_struct failed");
        exit(1);
    }

    (*im_data)->info_ptr = png_create_info_struct((*im_data)->png_ptr);
    if (!(*im_data)->info_ptr)
    {
        fprintf(stdout, " png_create_info_struct failed");
        exit(1);
    }

    if (setjmp(png_jmpbuf((*im_data)->png_ptr)))
    {
        fprintf(stdout, " Error during init_io");
        exit(1);
    }

    png_init_io((*im_data)->png_ptr, fp);
    png_set_sig_bytes((*im_data)->png_ptr, 8);

    png_read_info((*im_data)->png_ptr, (*im_data)->info_ptr);

    (*im_data)->width = png_get_image_width((*im_data)->png_ptr, (*im_data)->info_ptr);
    wprintf(L"%d", (*im_data)->width);
    (*im_data)->height = png_get_image_height((*im_data)->png_ptr, (*im_data)->info_ptr);
    (*im_data)->color_type = png_get_color_type((*im_data)->png_ptr, (*im_data)->info_ptr);
    (*im_data)->bit_depth = png_get_bit_depth((*im_data)->png_ptr, (*im_data)->info_ptr);

    (*im_data)->number_of_passes = png_set_interlace_handling((*im_data)->png_ptr);
    png_read_update_info((*im_data)->png_ptr, (*im_data)->info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf((*im_data)->png_ptr)))
    {
        fprintf(stdout, " Error during read_image");
    }

    (*im_data)->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (*im_data)->height);
    int y;
    for (y = 0; y < (*im_data)->height; y++)
        (*im_data)->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes((*im_data)->png_ptr, (*im_data)->info_ptr));

    png_read_image((*im_data)->png_ptr, (*im_data)->row_pointers);

    fclose(fp);
}

void encode_data(bin_data_t *bin_data, image_t *im_data, const int opacity)
{
    if (png_get_color_type(im_data->png_ptr, im_data->info_ptr) == PNG_COLOR_TYPE_RGB)
        wprintf(L"[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
                        "(lacks the alpha channel)");

    if (png_get_color_type(im_data->png_ptr, im_data->info_ptr) != PNG_COLOR_TYPE_RGBA)
        wprintf(L"[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
                PNG_COLOR_TYPE_RGBA, png_get_color_type(im_data->png_ptr, im_data->info_ptr));

    //! Presentation purposes only, change ASAP
    int i = 0;
    int subI = 0;

    for (int y = 0; y < im_data->height; y++)
    {
        png_byte *row = im_data->row_pointers[y];
        for (int x = 0; x < im_data->width/* * 2*/; x++)
        {
            png_byte *ptr = &(row[x * 4]);
            // wprintf(L"Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
            //         x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

            /* set red value to 0 and green value to the blue one */
            // ptr[0] = 0;
            // ptr[1] = ptr[2];
            
            //* Change the opacity!
            if (bin_data[i].data[subI] == 1) {
                ptr[3] = 255;
            } else {
                ptr[3] = opacity;
            }

            subI = (subI + 1) % 8;
            if (subI == 0)
                i++;
        }
    }
}

void save(image_t* im_data, const char* file_name)
{
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
        fprintf(stdout, "[write_png_file] File %s could not be opened for writing", file_name);

    /* initialize stuff */
    im_data->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!im_data->png_ptr)
        fprintf(stdout, "[write_png_file] png_create_write_struct failed");

    im_data->info_ptr = png_create_info_struct(im_data->png_ptr);
    if (!im_data->info_ptr)
        fprintf(stdout, "[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(im_data->png_ptr)))
        fprintf(stdout, "[write_png_file] Error during init_io");

    png_init_io(im_data->png_ptr, fp);

    /* write header */
    if (setjmp(png_jmpbuf(im_data->png_ptr)))
        fprintf(stdout, "[write_png_file] Error during writing header");

    png_set_IHDR(im_data->png_ptr, im_data->info_ptr, im_data->width, im_data->height,
                    im_data->bit_depth, im_data->color_type, PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(im_data->png_ptr, im_data->info_ptr);

    /* write bytes */
    if (setjmp(png_jmpbuf(im_data->png_ptr)))
        fprintf(stdout, "[write_png_file] Error during writing bytes");

    png_write_image(im_data->png_ptr, im_data->row_pointers);

    /* end write */
    if (setjmp(png_jmpbuf(im_data->png_ptr)))
        fprintf(stdout, "[write_png_file] Error during end of write");

    png_write_end(im_data->png_ptr, NULL);

    /* cleanup heap allocation */
    for (int y = 0; y < im_data->height; y++)
        free(im_data->row_pointers[y]);
    free(im_data->row_pointers);

    fclose(fp);
}
