#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>


// #define NUM 123456789
#ifndef NUM
#define NUM 10000
#endif

size_t binary_search(ssize_t *array, ssize_t needle) {
    size_t l = 0;
    size_t r = NUM-1;
    size_t mid;

    while (l < r) {
        // mid = (l + r) / 2;
        mid =  l + (r-l) / 2;
        if (array[mid] > needle) {
            r = mid - 1;
        
        } else if (array[mid] < needle) {
            l = mid + 1;

        } else {
            return mid;
        }
    }
    return l;
}

int main(void) {
    time_t t;
    srand((unsigned) time(&t));

    ssize_t* haystack = malloc(NUM * sizeof(ssize_t));
    ssize_t val = -NUM; //-rand() % NUM;
    for (size_t i = 0; i < NUM; i++) {
        haystack[i] = val; 
        val += rand() % 5;
    }
    printf("allocation complete\n");


    ssize_t needle = haystack[rand() % NUM];
//    ssize_t needle = haystack[NUM-1]-1;
    printf("searching for %zd...\n", needle);
    size_t index = binary_search(haystack, needle);
    printf("[%zu] = %zd\n", index, haystack[index]);

    free(haystack);

    return 0;
}
