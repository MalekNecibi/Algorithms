// divide and conquer

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>



int* generateArray(size_t, int*);
int findMax(int*, size_t);


int main(void) {
    srand((unsigned int) time(NULL));
    rand();

    printf("Generating array of %d random numbers\n", LENGTH);
    int real_max = 0;
    int* array = generateArray(LENGTH, &real_max);
    printf("The largest value in the array is now %d\n\n", real_max);

    printf("Searching recursively...\n\n");
    int found_max = findMax(array, LENGTH);

    printf(" real_max : %d\n", real_max);
    printf("found_max : %d\n", found_max);
    
    return 0;
}

int _max(int a, int b) {
    return (a > b) ? a : b ;
}

int findMax(int* array, size_t arrayLen) {
    if (0 == arrayLen){
        return INT_MIN;
    }

    if (1 == arrayLen) {
        return array[0];
    }

    size_t leftLen  = arrayLen / 2;
    size_t rightLen = arrayLen - leftLen;

    int* left_array  = array;
    int* right_array = array + leftLen;

    int leftMax  = findMax(left_array,  leftLen);
    int rightMax = findMax(right_array, rightLen);
    
    return _max(leftMax, rightMax);
}

// caller expected to free
int* generateArray(size_t length, int* real_max) {

    int* array = malloc(length * sizeof(int));


    for (size_t i = 0; i < length; i++) {
        array[i] = rand() % (int)MAX;
        *real_max = _max(*real_max, array[i]);
    }

    return array;

    
}

