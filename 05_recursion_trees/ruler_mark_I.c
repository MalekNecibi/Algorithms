#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void printRuler(short* tickmarks, size_t rulerSize) {
    for (size_t i = 0; i < rulerSize; i++) {
        printf("%3zu \n", i);
        printf("    ");
        for (short j = 0; j < tickmarks[i]; j++) {
            printf(" X");
        }
        printf("\n");
    }
    printf("%3zu \n", rulerSize);
    return;
}


void mark_ruler(short max_height) {
    size_t rulerSize = ((size_t)1 << max_height) - 1;
    short* tickmarks = malloc(rulerSize * sizeof(short));
    
    size_t index = 0;
    for (size_t n = 1; n <= max_height; n++) {
        // set the longest yet
        tickmarks[index] = n;
        index++;
        
        // copy everything from before
        memcpy(tickmarks+index, tickmarks, sizeof(short) * (index-1));
        index = 2*index - 1;
    }
    
    printRuler(tickmarks, rulerSize);

    free(tickmarks);
    return;
}

int main(int argc, char* argv[]) {
    short max_height;

    if (argc < 2) {
        printf("Usage: %s <tickmarks_max_height>\n", argv[0]);
        return 1;

    } else {
        if (1 != sscanf(argv[1], "%hu", &max_height)) {
            return 2;
        }
        if (max_height >= 32) {
            printf("ERROR: maximum height = 32\n");
            return 3;
        }
    }
    
    mark_ruler(max_height);
    
    return 0;
}
