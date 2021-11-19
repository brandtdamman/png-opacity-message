#include "lists.h"

#include <math.h>
#include <stdio.h>

char* inttob(int val);

int main() {
    FILE* input;
    wchar_t curr[2];

    setlocale(LC_CTYPE, "en-US.UTF-8");

    if ((input = fopen("input.txt", "r")) == NULL)
        return 1;
        
    printf("%x\n\n", input);

    while (fgetws(curr, 2, input) != NULL) {
        int val = curr[0];
        char* binary = inttob(val);

        wprintf(L"%s\t%-3d\t", curr, val);
        printf("%s\n", binary);
    }

    return 0;
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