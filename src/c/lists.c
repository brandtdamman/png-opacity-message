#include "lists.h"

//? Char Nodes
char_node_t* create_head_char_node() {
    char_node_t* HEAD = (char_node_t*)malloc(sizeof(char_node_t));
    return HEAD;
}

char_node_t* add_char_node(char_node_t* TAIL, wchar_t* data) {
    char_node_t* newTail = create_head_char_node();
    newTail->chr = data;
    TAIL->next = newTail;
    return newTail;
}

//? Segment Nodes
segment_node_t* create_head_segment_node() {
    segment_node_t* HEAD = (segment_node_t*)malloc(sizeof(segment_node_t));
    return HEAD;
}

segment_node_t* add_segment_node(segment_node_t* TAIL, int data[BYTE_SIZE]) {
    segment_node_t* newTail = create_head_segment_node();

    int i;
    for (i = 0; i < BYTE_SIZE; i++)
        newTail->bits[i] = data[i];

    TAIL->next = newTail;
    return newTail;
}
