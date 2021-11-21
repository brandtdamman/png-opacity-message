#ifndef __ENCODING_H__
#define __ENCODING_H__

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BYTE_SIZE 8

typedef struct bin_data_t bin_data_t;

struct bin_data_t {
    int data[BYTE_SIZE];
};

int read_file(int** retData, const char* filename);
void convert_text(wchar_t* text_data, const int char_count, bin_data_t** bin_data);

FILE* open_file(const char* filename);
int* inttobin(int val);
char* inttob(int val);

#endif