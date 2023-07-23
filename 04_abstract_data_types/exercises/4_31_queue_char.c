#define DTYPE char
#define QUEUE_ERROR_VAL '\0'

#include "../queue.h"
#include<string.h>


// A letter means put and an asterisk means get in the sequence
//      E A S * Y * Q U E * * * S T * * * I O * N * * *

int main(void) {
    char* queue_string = "E A S * Y * Q U E * * * S T * * * I O * N * * *";
    size_t queue_string_len = strlen(queue_string);

    Queue q = initQueue();

    for (size_t i = 0; i < queue_string_len; i++) {
        char c = queue_string[i];
        if (' ' == c) continue;
        
        if ('*' == c) {
            printf("%c ", dequeue(q));
        
        } else {
            enqueue(q, c);
        }
    }
    printf("\n");

    deleteQueue(&q);
    
    return 0;
}
