#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void _mark_ruler(short* tickmarks, size_t left, size_t right, short height) {
//    printf("[%d,%d] : %zu\n", left, right, height);
    
    size_t mid = left + (right-left) / 2;
    tickmarks[mid] = height;
    
    if (height <= 1) {
        return;
    }
    
    _mark_ruler(tickmarks, left,  mid-1, height-1);
    _mark_ruler(tickmarks, mid+1, right, height-1);
}

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
    // number of tickmarks = 2 ^ tallest tickmark - 1
    size_t num_tickmarks = ( (size_t)1 << max_height ) - 1;
    
    short* tickmarks = malloc(num_tickmarks * sizeof(short));
    
    _mark_ruler(tickmarks, 0, num_tickmarks-1, max_height);
    printRuler(tickmarks, num_tickmarks);
    
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
