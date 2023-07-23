#define DTYPE char
#define DEQUE_ERROR_VAL '\0'

#include "../deque.h"
#include<string.h>


// An uppercase letter means put at the beginning, a lowercase letter means
// put at the end, a plus sign means get from the beginning, and an asterisk means
// get from the end in the sequence
//      E A s + Y + Q U E * * + s t + * + I O * n + + *

int main(void) {
    char* deque_string = "E A s + Y + Q U E * * + s t + * + I O * n + + *";
    //char* deque_string = "A B c + D + e F G * * + h i + * + J K * l + + *";
    size_t deque_string_len = strlen(deque_string);

    Deque dq = initDeque();

    for (size_t i = 0; i < deque_string_len; i++) {
        char c = deque_string[i];
        if (' ' == c) continue;
        
        switch(c) {
            case ' ':
                break;
            case '+':
                printf("%c ", popLeft(dq));
                break;
            case '*':
                printf("%c ", popRight(dq));
                break;
            default:
                if ('A' <= c && c <= 'Z') {
                    pushLeft(dq, c);

                } else if ('a' <= c && c <= 'z') {
                    pushRight(dq, c);
                }
                break;
        }
        fflush(stdout);
    }
    printf("\n");

    deleteDeque(&dq);
    
    return 0;
}
