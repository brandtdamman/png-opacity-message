/*
 *   ____                _ __         ______                                             __       
 *  / __ \___  ___ _____(_) /___ __  / __/ /____ ___ ____ ____  ___  ___ ________ ____  / /  __ __
 * / /_/ / _ \/ _ `/ __/ / __/ // / _\ \/ __/ -_) _ `/ _ `/ _ \/ _ \/ _ `/ __/ _ `/ _ \/ _ \/ // /
 * \____/ .__/\_,_/\__/_/\__/\_, / /___/\__/\__/\_, /\_,_/_//_/\___/\_, /_/  \_,_/ .__/_//_/\_, / 
 *     /_/                  /___/              /___/               /___/        /_/        /___/  
 *
 * Developed by https://github.com/brandtdamman.
 * See header file and/or https://github.com/brandtdamman/png-opacity-message for license and other details.
 * 
 * Originally designed for IASTATE MATH424 - Introduction to High Performance Computing
 */
#include "main.h"

#include <time.h>

int main(int argc, char *argv[])
{
    // Validation CLI args.
    if (argc != 4)
        usage(argv[0]);

    // Obtain filenames from the args.
    const char* text_file = argv[1];
    const char* image_file = argv[2];
    const char* output_file = argv[3];

    // Inform OMP it isn't allowed to make _more_ threads.
    // omp_set_nested(1);
    // omp_set_dynamic(0);

    // 1. Load text from file, character by character.
    clock_t begin = clock();

    int* text_data;
    int char_count = read_file(&text_data, text_file);
    clock_t end = clock();
    double reading = (double)(end - begin) / CLOCKS_PER_SEC;

    // 2. (Parallel) Decompose text into binary data.
    begin = clock();

    bin_data_t* decomposed_data;
    convert_text(text_data, char_count, &decomposed_data);
    end = clock();
    double converting = (double)(end - begin) / CLOCKS_PER_SEC;

    // 3. Load image data.  Painfully.
    begin = clock();

    image_t* im_data;
    read_image(&im_data, image_file);
    end = clock();
    double image_load = (double)(end - begin) / CLOCKS_PER_SEC;

    wprintf(L"\nEstimated times (in seconds)\n================================\n");
    wprintf(L"I/O Read\t=\t%lf\n", reading);
    wprintf(L"Converting\t=\t%lf\n", converting);
    wprintf(L"Image I/O\t=\t%lf\n", image_load);
    wprintf(L"================================\n\n");
    return 0;
}

/*
    Details the required and optional CLI arguments.

    :param prog_name: name of the program
    :type prog_name: char*
 */
void usage(const char *prog_name)
{
    fprintf(stderr, "usage: %s <text_file> <image_file> <output_file>\n", prog_name);
    fprintf(stderr, "\tBoth text_file and image_file should exist.\n");
    fprintf(stderr, "\tEnsure write permissions are available for output_file.\n");
    exit(1);
}
