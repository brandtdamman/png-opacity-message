#ifndef __LISTS_H__
#define __LISTS_H__

#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

#define BYTE_SIZE 8
#define DATA_SIZE 2

// structures
typedef struct char_node_t char_node_t;

struct char_node_t {
    //* Struct used for text IO.
    wchar_t* chr;
    char_node_t* next;
};

typedef struct segment_node_t segment_node_t;

struct segment_node_t {
    //* Struct used for decomposition.
    int bits[BYTE_SIZE];
    segment_node_t* next;
};

// prototypes for operations
//? Char Nodes
char_node_t* create_head_char_node();
char_node_t* add_char_node(char_node_t* TAIL, wchar_t* data);
void print_char_nodes(char_node_t* HEAD);

//? Segment Nodes
segment_node_t* create_head_segment_node();
segment_node_t* add_segment_node(segment_node_t* TAIL, int data[BYTE_SIZE]);

#endif
