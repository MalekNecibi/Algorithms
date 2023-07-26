#include<stdio.h>
#include<stdlib.h>

void _mark_ruler(int* ruler, int left, int right) {
    int height = right - left + 1;
//    printf("[%d,%d] : %d\n", left, right, height);
    
    int width = (height + 1) / 2;

    int mid = left + (right-left) / 2;
    if (0 != ruler[mid]) {
        printf("Warning: [%d] previously set with %d (h=%d)\n",mid, ruler[mid], height);
    } else {
        ruler[mid] = width;
    }

    if (left >= right) {
        return;
    }

    if (height <= 1) {
        return;
    }
    
    _mark_ruler(ruler, left,   mid-1);
    _mark_ruler(ruler, mid+1,  right);
    
//    _mark_ruler(ruler, left, mid-1,   height/2);
//    _mark_ruler(ruler, mid+1,  right, height/2);
}

void printRuler(int* ruler, size_t rulerSize) {
    for (size_t i = 0; i < rulerSize; i++) {
        printf("%3zu : \n", i);
        printf("       ");
        for (size_t j = 0; j < ruler[i]; j++) {
            printf(" X");
        }
        printf("\n");
    }
    
    printf("%3zu : \n", rulerSize);
    return;
}

// max_height must be power of 2
void mark_ruler(size_t num_tickmarks) {
    
    // num_tickmarks must be 1 less than a power-of-2
    size_t input_validator = num_tickmarks + 1;
    while (!(input_validator & 0b1)) {
        input_validator >>= 1;
    }
    if (1 != input_validator) {
        printf("ERROR: %zu is not a valid number of tickmarks!\n", num_tickmarks);
        printf("\tValue must be 1 less than a power-of-2 (e.g. 15)\n");
        return;
    }
    
    //int* ruler = malloc(max_height * sizeof(int));
    int* ruler = calloc(num_tickmarks, sizeof(int));
    
    _mark_ruler(ruler, 0, num_tickmarks-1);
    
    printRuler(ruler, num_tickmarks);
    
    free(ruler);
    return;
}


int main(int argc, char* argv[]) {
    
    size_t num_tickmarks;

    if (argc < 2) {
        printf("Usage: %s <num_tickmarks>\n", argv[0]);
        return 1;

    } else {
        if (1 != sscanf(argv[1], "%zu", &num_tickmarks)) {
            return 2;
        }
    }

    mark_ruler(num_tickmarks);
    
    // initial call (left, right, num_subdivisions
    // know outer boundary values
    // start in center (midpoint outers)
    // draw midpoint with height=num_subdivisions
    // recurse left
        // left=left, right=left + (right-left)/2, height=height/2
    
    return 0;
}
