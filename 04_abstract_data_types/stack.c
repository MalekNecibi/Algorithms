#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define DTYPE int
#define ERROR_VAL INT_MIN

// push to head
// pop from head

// Stack    : pointer to a StackMeta
// StackMeta: container with pointers to head and tail StackNode's
// StackNode: container that actually stores one value to store

typedef struct ListNode StackNode;
typedef struct StackMeta* Stack;

struct StackMeta {
    StackNode* head;

};

struct ListNode {
    DTYPE value;
    struct ListNode* next;
};

// private
StackNode* initStackNode(DTYPE value) {
    StackNode* node = malloc( sizeof(StackNode) );
    if (!node) return NULL;

    node->value = value;
    node->next = NULL;
    return node;
}

Stack initStack() {
    Stack stack = calloc(1, sizeof(struct StackMeta));
    stack->head = NULL;

    return stack;
}


bool isEmpty(Stack stack) {
    if (!stack) {
        printf("WARNING: isEmpty called with deleted/NULL Stack\n");
        return true;
    }
    return (!stack->head);
}







// return ERROR_VAL if empty/deleted stack provided
DTYPE pop(Stack stack) {
    if (!stack || isEmpty(stack)) {
        return ERROR_VAL;
    }
    
    StackNode *old_head = stack->head;
    DTYPE value = old_head->value;
    
    StackNode *new_head = old_head->next;
    stack->head = new_head;
    
    free(old_head);
    return value;
}







bool push(Stack stack, DTYPE value) {
    if (!stack) {
        return false;
    }
    
    StackNode* node = initStackNode(value);
    if (!node) {
        return false;
    }
    node->next = stack->head;

    stack->head = node;
    return true;
}










void deleteStack(Stack* _stack) {
    if (!_stack || !*_stack) {
        return;
    }
    
    Stack stack = *_stack;
    // remove all items from stack
    while ( !isEmpty(stack) ) {
        pop(stack);
    }
    
    free(stack);
    *_stack = NULL;
}



int main(void) {
    Stack s = initStack();
    push(s, 12);
    printf("%d\n", pop(s));
    
    push(s, 17);
    printf("%d\n", pop(s));
    
    push(s, 19);
    push(s, 19282);
    push(s, -2189);
    
    pop(s);

    deleteStack(&s);
    
    

    // must all fail with ERROR_VAL, and without memory leaks
    push(s, 18);
    push(s, 1);
    push(s, -9304792);
    pop(s);

    deleteStack(&s);

    
    Stack s2 = initStack();
    push(s2, 12);
    
    printf("%d\n", pop(s2));
    
    push(s2, 17);
    printf("%d\n", pop(s2));

    push(s2, 19);
    push(s2, 19282);
    printf("%d\n", pop(s2));
    push(s2, -2189);

    printf("%d\n", pop(s2));
    printf("%d\n", pop(s2));
    
    // pop more than push
    printf("%d (should be %d)\n", pop(s2), ERROR_VAL);
    
    push(s2, 38);
    push(s2, 239792);
    printf("%d\n", pop(s2));

    deleteStack(&s2);


    // should fail with ERROR_VAL
    push(s2, 18);
    push(s2, 1);
    push(s2, -9304792);
    printf("pop after deletion returns ERROR_VAL? %s\n", (pop(s2) == ERROR_VAL) ? "true" : "false");

    deleteStack(&s2);

    return 0;
}
