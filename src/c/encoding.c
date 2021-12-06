#include "encoding.h"

#define MAXC 100
#define CURRSIZE 2

int read_file(int** retData, const char* filename) {
    FILE* input;
    wchar_t curr[CURRSIZE];

    // CHANGE DEPENDING ON REGION.
    setlocale(LC_CTYPE, "en-US.UTF-8");
    // setlocale(LC_ALL, "French_Canada.1252");

    // input = open_file(filename);
    wprintf(L"%s\n", filename);
    if ((input = fopen(filename, "r")) == NULL)
        return 0;

    // char_node_t* node = HEAD;
    int count = 0;
    //* once to get number of characters.
    while (fgets(curr, CURRSIZE, input) != NULL) {
        // node = add_char_node(node, curr);
        count += 1;
        // wprintf(L"Blah\n");
        // wprintf(L"%s", curr);
        // printf("%s\n", binary);
    }

    // printf("count = %d\n", count);
    fclose(input);

    // input = open_file(filename);
    if ((input = fopen(filename, "r")) == NULL)
        return 0;
    // wprintf(L"Blah\n");
    wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * count);
    int i = 0;
    while (fgets(curr, 2, input) != NULL) {
        data[i++] = curr[0];
        // wprintf(L"%s\n", curr);
//         wprintf(L"%s", *retData);
    }
//
    // for (i = 0; i < 10; i++) {
    //     fprintf(stdout, "%c\n", data[i]);
    // }
//
//    fprintf(stdout, "\n");
    *retData = data;
    wprintf(L"%d\n", count);
    return count;
}

FILE* open_file(const char* filename) {
    FILE* input;
    
    if ((input = fopen(filename, "r")) == NULL)
        return NULL; //? throw error ?

    return input;
}

void convert_text(wchar_t* text_data, const int char_count, bin_data_t** bin_data) {
    //! Use OMP nested threads.

    // do it serial first.

    //? determine ranges to utilize.

    // allocate.  Definitely memory intensive at the moment...
    *bin_data = (bin_data_t*)malloc(sizeof(bin_data_t) * char_count);

    //* Decompose!
    int i, j;
    for (i = 0; i < char_count; i++) {
        int* tempData = inttobin(text_data[i]);
        // char* tempStr = inttob(text_data[i]);
        
        for (j = 0; j < BYTE_SIZE; j++)
            (*bin_data)[i].data[j] = tempData[j];

        // wprintf(L"%c --> %s", text_data[i], tempStr);
    }

    // Don't need this anymore.
    free(text_data);
}

int* inttobin(int val) {
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

/* FOR DEBUGGING PURPOSES. */
char* inttob(int val) {
    char* retVal = (char*)malloc(sizeof(char) * (BYTE_SIZE + 2));

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

    retVal[BYTE_SIZE] = '\n';
    retVal[BYTE_SIZE + 1] = '\0';
    return retVal;
}