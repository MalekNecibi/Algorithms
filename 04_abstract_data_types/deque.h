#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#ifndef DEQUE_DTYPE
#define DEQUE_DTYPE int
#endif

#ifndef DEQUE_ERROR_VAL
#define DEQUE_ERROR_VAL INT_MIN
#endif

// Deque    : pointer to a DequeMeta
// DequeMeta: container with pointers to head and tail DequeNode's
// DequeNode: container that actually stores one value to store

typedef struct DoubleListNode DequeNode;
typedef struct DequeMeta* Deque;

struct DequeMeta {
    DequeNode* head;
    DequeNode* tail;
};

struct DoubleListNode {
    DEQUE_DTYPE value;
    struct DoubleListNode* next;
    struct DoubleListNode* prev;
};

// private
DequeNode* initDequeNode(DEQUE_DTYPE value) {
    DequeNode* node = malloc( sizeof(DequeNode) );
    if (!node) return NULL;

    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Deque initDeque() {
    Deque deque = calloc(1, sizeof(struct DequeMeta));
    deque->head = NULL;
    deque->tail = NULL;

    return deque;
}

bool isEmpty(Deque deque) {
    if (!deque) {
        printf("WARNING: isEmpty called with deleted/NULL Deque\n");
        return true;
    }
    if (!deque->head || !deque->tail) {
        // should both be NULL simultaneously
        if (deque->head || deque->tail) {
            printf("ERROR isEmpty() : only 1 of head/tail is NULL ? %p , %p\n", deque->head, deque->tail);
        }
    }
    return (!deque->head || !deque->tail);
}

// return DEQUE_ERROR_VAL if empty/deleted deque provided
DEQUE_DTYPE popRight(Deque deque) {
    if (!deque || isEmpty(deque)) {
        return DEQUE_ERROR_VAL;
    }
    
    DequeNode *old_tail = deque->tail;
    DEQUE_DTYPE value = old_tail->value;
    
    DequeNode *new_tail = old_tail->prev;
    deque->tail = new_tail;

    if (NULL == new_tail) {
        // was only 1 item in deque, now 0
        deque->head = NULL;
    } else {
        new_tail->next = NULL;
    }
    
    free(old_tail);
    return value;
}

// return DEQUE_ERROR_VAL if empty/deleted deque provided
DEQUE_DTYPE popLeft(Deque deque) {
    if (!deque || isEmpty(deque)) {
        return DEQUE_ERROR_VAL;
    }
    
    DequeNode *old_head = deque->head;
    DEQUE_DTYPE value = old_head->value;
    
    DequeNode *new_head = old_head->next;
    new_head->prev = NULL;
    deque->head = new_head;

    if (NULL == new_head) {
        // was only 1 item in deque, now 0
        deque->tail = NULL;
    } else {
        new_head->prev = NULL;
    }
    
    free(old_head);
    return value;
}

bool pushLeft(Deque deque, DEQUE_DTYPE value) {
    if (!deque) {
        return false;
    }

    DequeNode* node = initDequeNode(value);
    if (!node) {
        return false;
    }
    node->prev = NULL;  // redundant but safe

    if ( isEmpty(deque) ) {
        node->next = NULL;
        deque->tail = node;

    } else {
        node->next = deque->head;
        deque->head->prev = node;
    }
    // update DequeMeta with new head
    deque->head = node;

    return true;
}

bool pushRight(Deque deque, DEQUE_DTYPE value) {
    if (!deque) {
        return false;
    }
    
    DequeNode* node = initDequeNode(value);
    if (!node) {
        return false;
    }
    node->next = NULL;  // redundant but safe

    if ( isEmpty(deque) ) {
        // only 1 item now, head == tail
        node->prev = NULL;
        deque->head = node;
    
    } else {
        // extend the tail of linked list with new node
        node->prev = deque->tail;
        deque->tail->next = node;
    }
    // update DequeMeta with new tail
    deque->tail = node;

    return true;
}

void deleteDeque(Deque* _deque) {
    if (!_deque || !*_deque) {
        return;
    }

    Deque deque = *_deque;
    
    // remove all items from Deque
    while ( !isEmpty(deque) ) {
        popLeft(deque);
    }
    
    // delete the deque's metadata
    free(deque);
    
    *_deque = NULL;
}
