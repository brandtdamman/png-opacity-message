#include "encoding.h"

int read_file(wchar_t** retData, const char* filename) {
    FILE* input;
    wchar_t curr[2];

    // CHANGE DEPENDING ON REGION.
    setlocale(LC_CTYPE, "en-US.UTF-8");

    input = open_file(filename);

    // char_node_t* node = HEAD;
    int count = 0;
    //* once to get number of characters.
    while (fgetws(curr, 2, input) != NULL) {
        // node = add_char_node(node, curr);
        count += 1;
        // wprintf(L"%s\n", curr);
        // printf("%s\n", binary);
    }

    printf("count = %d\n", count);

    input = open_file(filename);
    *retData = (wchar_t*)malloc(sizeof(wchar_t) * count);
    while (fgetws(*retData, count, input) != NULL) {
        wprintf(L"%s", *retData);
    }

    fprintf(stdout, "\n");
    return count;
}

FILE* open_file(const char* filename) {
    FILE* input;
    
    if ((input = fopen(filename, "r")) == NULL)
        return NULL; //? throw error ?

    return input;
}

void convert_text(char* text, const char* locale) {
    //! Use OMP nested threads.
}

int* wchartobin(wchar_t val) {
    int* retVal = (int*)malloc(sizeof(int) * (BYTE_SIZE));

    int curr = val;

    int i;
    for (i = 0; i < BYTE_SIZE; i++) {
        int power = pow(2, (BYTE_SIZE - i - 1));
        if (curr - power > 0) {
            retVal[i] = 1;
            curr -= power;
        } else {
            retVal[i] = 0;
        }
    }

    return retVal;
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