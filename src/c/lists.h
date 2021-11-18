#ifndef __LISTS_H__
#define __LISTS_H__

#include <locale.h>
#include <wchar.h>

// structures
typedef struct char_node {
    //* Struct used for text IO.
    wchar_t* chr;
    char_node_t* next;
} char_node_t;

typedef struct segment_node {
    //* Struct used for decomposition.
    int bits[8];
    segment_node_t* next;
} segment_node_t;

// prototypes for operations
char_node_t* create_head_char_node();
char_node_t* add_char_node(const char_node_t* TAIL, wchar_t* data);
char_node_t* iterate_char_node(const char_node_t* curr);

segment_node_t* create_head_segment_node();
segment_node_t* add_segment_node(const segment_node_t* TAIL, int* data);
segment_node_t* iterate_segment_node(const segment_node_t* curr);

#endif
