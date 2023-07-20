#include<stdio.h>
#include<stdlib.h>

#include<math.h>    // INFINITY
#include<stdint.h>  // 

// choose your data type at compile-time
#ifndef DTYPE
#define DTYPE int
#endif

// Get the default printf specifier for a given type
// custom : https://en.cppreference.com/w/c/io/fprintf
#define DEFAULT_FORMAT(x) _Generic((x), unsigned char: "%c",                       \
         char: "%c",                      signed char: "%hhd",                     \
    short int: "%hd",              unsigned short int: "%hu",                      \
          int: "%d",                     unsigned int: "%u",                       \
     long int: "%ld",               unsigned long int: "%lu",                      \
long long int: "%lld",         unsigned long long int: "%llu",                     \
        float: "%f",                           double: "%lf",                      \
  long double: "%Lf",                          char *: "%s",                       \
       void *: "%p",                                                            \
      default: "%x")

#define PRINT_DTYPE(x) printf(#x " = ");  \
    printf(DEFAULT_FORMAT(x), (x)); \
    printf("\n");


void printHex(DTYPE data);

int main(void) {
    DTYPE limit, prev;
    
    prev = 0;
    limit = prev + 1;
    
    // grow exponentially (growth) until overflow
    while (limit > prev && limit != INFINITY) {
        PRINT_DTYPE(prev);
        prev = limit;
        limit *= 2;
    }
    
    // the limit of growth we can achieve
    DTYPE max_remaining = prev;
    limit = prev + max_remaining;
    
    // shrink exponentially (decay) overflow
    while (max_remaining > 0 && limit != prev) {
        PRINT_DTYPE(prev);
        if (limit < prev || limit == INFINITY) {
            max_remaining /= 2;
        } else {
            prev = limit;
        }
        limit = prev + max_remaining;
    }
    
    printf("\nFinal value:\n");
    PRINT_DTYPE(limit);
    printf("as   signed : %zd\n", (ssize_t) limit);
    printf("as unsigned : %zu\n",  (size_t) limit);
    printHex(limit);
//    printf("hexadecimal : %lx\n",  (size_t) limit);

    return 0;
}


union asHex {
    DTYPE value;
    unsigned char bytes[sizeof(DTYPE)];
};
void printHex(DTYPE data) {
    union asHex data_hex;  //
    data_hex.value = data;
    printf("hexadecimal : ");
    // little endian
    for (ssize_t i = sizeof(DTYPE)-1; i >= 0; i--) {
        printf("%02x ", data_hex.bytes[i]);              // technically undefined behavior
    }
    printf("\n");
}
