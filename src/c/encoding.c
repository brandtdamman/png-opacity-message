#include "encoding.h"

void read_file(char_node_t* HEAD, const char* filename) {
    FILE* input;
    wchar_t curr[2];

    // CHANGE DEPENDING ON REGION.
    setlocale(LC_CTYPE, "en-US.UTF-8");

    if ((input = fopen(filename, "r")) == NULL)
        return; //? throw error ?
        
    char_node_t* node = HEAD;
    int count = 0;
    while (fgetws(curr, 2, input) != NULL) {
        // node = add_char_node(node, curr);
        count += 1;
        wprintf(L"%s\n", curr);
        // printf("%s\n", binary);
    }

    wprintf("count = %d\n", &count);
}

void convert_text(char* text, const char* locale) {
    //! Use OMP nested threads.
}

char* inttob(int val) {
    char* retVal = (char*)malloc(sizeof(char) * (BYTE_SIZE + 1));

    int curr = val;

    int i;
    for (i = 0; i < BYTE_SIZE; i++) {
        int power = pow(2, (BYTE_SIZE - i - 1));
        // printf("power: %d\n", power);
        if (curr - power > 0) {
            // printf("worked. adding '1' to string?\n");
            retVal[i] = '1';
            curr -= power;
        } else {
            retVal[i] = '0';
        }
    }

    retVal[BYTE_SIZE] = '\0';
    return retVal;
}