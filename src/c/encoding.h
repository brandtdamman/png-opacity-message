#ifndef __ENCODING_H__
#define __ENCODING_H__

#include <wchar.h>
#include <locale.h>

void read_file(char* text, const char* filename);
void convert_text(char* text, const char* locale);

#endif