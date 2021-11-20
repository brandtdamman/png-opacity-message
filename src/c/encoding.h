#ifndef __ENCODING_H__
#define __ENCODING_H__

#include "lists.h"

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <wchar.h>

void read_file(char_node_t* HEAD, const char* filename);
void convert_text(char* text, const char* locale);


#endif