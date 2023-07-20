// Find Limits [max/min] of builtin data types (without cheating)
// Malek Necibi

// To run, compile gcc with -DDTYPE="..." flag to set the data type
// e.g. gcc -DDTYPE="int" 3_1_dtype_limit.c


#include<stdio.h>
#include<stdlib.h>
#include<math.h>    // INFINITY
#include<stdint.h>  // not required, but allows for more test cases

// stdbool not supported
// choose your data type at compile-time
#ifndef DTYPE
#   define DTYPE int
#endif

// Sign : find minimum or maximum value
#ifdef MIN
#    define SIGN (-1)
#else
#    define SIGN (+1)
#endif


// Get the default printf specifier for a given type
// https://en.cppreference.com/w/c/io/fprintf
#define DEFAULT_FORMAT(x) _Generic((x), unsigned char: "%c",        \
         char: "%c",                      signed char: "%hhd",      \
    short int: "%hd",              unsigned short int: "%hu",       \
          int: "%d",                     unsigned int: "%u",        \
     long int: "%ld",               unsigned long int: "%lu",       \
long long int: "%lld",         unsigned long long int: "%llu",      \
        float: "%f",                           double: "%lf",       \
  long double: "%Lf",                          char *: "%s",        \
       void *: "%p",                                                \
      default: "%x")

#ifndef quiet
#   define PRINT_DTYPE(x) printf(#x " = ");  \
        printf(DEFAULT_FORMAT(x), (x)); \
        printf("\n");
#else
#   define PRINT_DTYPE(x)
#endif


void printHex(DTYPE data);

int main(void) {
    
    DTYPE previous = 0;
    DTYPE limit = previous + SIGN*1;
    
    // grow exponentially (growth) until overflow
    while (SIGN*limit > SIGN*previous && limit != SIGN*INFINITY) {
        PRINT_DTYPE(previous);
        previous = limit;
        limit *= 2;
    }
    
    // the limit of growth we can achieve
    DTYPE max_remaining = previous;
    limit = previous + max_remaining;
    
    // shrink exponentially (decay) overflow
    while (SIGN*max_remaining > 0 && limit != previous) {
        PRINT_DTYPE(previous);
        if (SIGN*limit < SIGN*previous || limit == SIGN*INFINITY) {
            max_remaining /= 2;
        } else {
            previous = limit;
        }
        limit = previous + max_remaining;
    }
    
    printf("\nFinal value:\n");
    PRINT_DTYPE(limit);
    printf("as   signed : %zd\n", (ssize_t) limit);
    printf("as unsigned : %zu\n",  (size_t) limit);
    printHex(limit);
    // plain printf "%x" insufficient for negative values

    return 0;
}


union asBytes {
    DTYPE value;
    unsigned char bytes[sizeof(DTYPE)];
};
void printHex(DTYPE data) {
    union asBytes data_hex;
    data_hex.value = data;
    printf("hexadecimal : ");
                                                        // little endian
    for (ssize_t i = sizeof(DTYPE)-1; i >= 0; i--) {
        printf("%02x ", data_hex.bytes[i]);             // technically undefined behavior
    }
    printf("\n");
}
