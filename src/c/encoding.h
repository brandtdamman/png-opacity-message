#ifndef __ENCODING_H__
#define __ENCODING_H__

#include "lists.h"

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <wchar.h>

int read_file(wchar_t** retData, const char* filename);
void convert_text(char* text, const char* locale);
FILE* open_file(const char* filename);

#endif