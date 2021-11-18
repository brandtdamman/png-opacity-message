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
    omp_set_nested(1);
    omp_set_dynamic(0);

    // 1. Load text from file, character by character.
    char* text;
    read_file()

    return 0;
}

/*
    Details required and optional CLI arguments.

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
