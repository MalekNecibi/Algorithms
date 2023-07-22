#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define BUFFER_SIZE 31
int main(int argc, char* argv[]) {
    
    printf("Prime tester, how many values should we test? ");

    char* buffer;
    char input_buffer[BUFFER_SIZE + 1] = {0};
    
    if (argc > 1) {
        buffer = argv[1];
    } else {
        if ( !fgets(input_buffer, BUFFER_SIZE, stdin) )
            return -1;
        
        buffer = (char*)input_buffer;
    }
        
    char* end;
    long max_val = strtol(buffer, &end, 10);
    if (buffer == end)
        return -1;
    
    // 0 : prime
    // 1 : non-prime
    bool* primes_array = calloc(1 + max_val, sizeof(bool));
    if (!primes_array)
        return -2;
    
    primes_array[0] = true;
    primes_array[1] = true;
    
    for (long i = 2; i <= max_val; i++) {
        for (long j = i*2; j <= max_val; j += i) {
            primes_array[j] = true;
        }
    }
    
    printf("\nPrimes:\n");
    long prime_count = 0;
    for (long i = 1; i <= max_val; i++) {
        if (!primes_array[i]) {
            // printf("%ld, ", i);
            prime_count++;
        }
    }
    printf("\n\n%ld primes of\n%ld total\n", prime_count, max_val);
    
    
    free(primes_array);
}
