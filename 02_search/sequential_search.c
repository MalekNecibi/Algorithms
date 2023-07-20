#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>


// #define NUM 123456789
#ifndef NUM
#define NUM 10000
#endif

int main(void) {
    time_t t;
    srand((unsigned) time(&t));

    ssize_t* haystack = malloc(NUM * sizeof(ssize_t));
    ssize_t val = -NUM; //-rand() % NUM;
    for (size_t i = 0; i < NUM; i++) {
        haystack[i] = val; 
//        printf("%zd  \n", val);
        val += rand() % 5;
    }
    printf("allocation complete\n");


//    ssize_t needle = haystack[irand() % NUM];
    ssize_t needle = haystack[NUM-1];
    printf("searching...\n");
    for (size_t i = 0; i < NUM; i++) {
        if (haystack[i] == needle) {
            printf("found %zd at index %zu\n", needle, i);
            break;
        }
    }


    free(haystack);

    return 0;
}
