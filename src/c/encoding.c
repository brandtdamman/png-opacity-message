#include "encoding.h"

int read_file(int** retData, const char* filename) {
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
    fclose(input);

    input = open_file(filename);
    wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * count);
    int i = 0;
    while (fgetws(curr, 2, input) != NULL) {
        data[i++] = curr[0];
        //wprintf(L"%s", curr);
//         wprintf(L"%s", *retData);
    }
//
//    for (i = 0; i < 10; i++) {
//        fprintf(stdout, "%c\n", data[i]);
//    }
//
//    fprintf(stdout, "\n");
    *retData = data;
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
        char* tempStr = inttob(text_data[i]);
        
        for (j = 0; j < BYTE_SIZE; j++)
            (*bin_data)[i].data[j] = tempData[j];
        
//        wchar_t* charSeq[2];
//        charSeq[0] = (wchar_t)text_data[i];
//        charSeq[1] = '\0';
//        wprintf(L"%s\t", charSeq);
//        fprintf(stdout, tempStr);
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