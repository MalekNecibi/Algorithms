#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#ifndef STACK_DTYPE
#define STACK_DTYPE int
#endif

#ifndef STACK_ERROR_VAL
#define STACK_ERROR_VAL INT_MIN
#endif

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
    STACK_DTYPE value;
    struct ListNode* next;
};

// private
StackNode* initStackNode(STACK_DTYPE value) {
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







// return STACK_ERROR_VAL if empty/deleted stack provided
STACK_DTYPE pop(Stack stack) {
    if (!stack || isEmpty(stack)) {
        return STACK_ERROR_VAL;
    }
    
    StackNode *old_head = stack->head;
    STACK_DTYPE value = old_head->value;
    
    StackNode *new_head = old_head->next;
    stack->head = new_head;
    
    free(old_head);
    return value;
}







bool push(Stack stack, STACK_DTYPE value) {
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



