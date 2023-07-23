#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define DTYPE int
#define ERROR_VAL INT_MIN

// push to head
// pop from head

typedef struct ListNode StackNode;
typedef struct ListNode* Stack;
struct ListNode {
    DTYPE value;
    struct ListNode* next;
};

Stack initStack(DTYPE value) {
    StackNode* node = calloc(1, sizeof(StackNode));
    node->value = value;
    node->next = NULL;
    return node;
}

// return ERROR_VAL if empty stack provided
DTYPE pop(Stack *stack) {
    if (!stack || !*stack)
        return ERROR_VAL;
    
    StackNode *old_head = *stack;
    DTYPE value = old_head->value;
    
    StackNode *new_head = old_head->next;
    *stack = new_head;
    free(old_head);

    return value;
}

void push(Stack *stack, DTYPE value) {
    if (NULL == stack)
        return;
    if (NULL == *stack) {
        *stack = initStack(value);
        return;
    }

    StackNode* node = initStack(value);
    node->next = *stack;
    *stack = node;
}

void deleteStack(Stack* stack) {
    StackNode* head = *stack;
    while (head) {
        StackNode* node = head;
        head = node->next;

        free(node);
    }
    *stack = NULL;
}

int main(void) {
    
    Stack s = initStack(12);
    printf("%d\n", pop(&s));
    
    push(&s, 17);
    printf("%d\n", pop(&s));
    
    push(&s, 19);
    push(&s, 19282);
    push(&s, -2189);
    
    pop(&s);

    deleteStack(&s);
    
    // should still work, and safely
    push(&s, 18);
    push(&s, 1);
    push(&s, -9304792);
    pop(&s);

    deleteStack(&s);
    return 0;
}
