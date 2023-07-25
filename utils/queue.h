#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

// caller must overwrite both
#if !defined(QUEUE_DTYPE) && !defined(QUEUE_ERROR_VAL)
#define QUEUE_DTYPE int
#define QUEUE_ERROR_VAL INT_MIN
#endif

// enqueue to tail
// dequeue from head

// Queue    : pointer to a QueueMeta
// QueueMeta: container with pointers to head and tail QueueNode's
// QueueNode: container that actually stores one value to store

typedef struct ListNode QueueNode;
typedef struct QueueMeta* Queue;

struct QueueMeta {
    QueueNode* head;
    QueueNode* tail;
};

struct ListNode {
    QUEUE_DTYPE value;
    struct ListNode* next;
};

// private
QueueNode* initQueueNode(QUEUE_DTYPE value) {
    QueueNode* node = malloc( sizeof(QueueNode) );
    if (!node) return NULL;

    node->value = value;
    node->next = NULL;
    return node;
}

Queue initQueue() {
    Queue queue = calloc(1, sizeof(struct QueueMeta));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

bool isEmpty(Queue queue) {
    if (!queue) {
        printf("WARNING: isEmpty called with deleted/NULL Queue\n");
        return true;
    }
    if (!queue->head || !queue->tail) {
        // should both be NULL simultaneously
        if (queue->head || queue->tail) {
            printf("ERROR isEmpty() : only 1 of head/tail is NULL ? %p , %p\n", queue->head, queue->tail);
        }
    }
    return (!queue->head || !queue->tail);
}

QUEUE_DTYPE peek(Queue queue) {
    if (!queue || isEmpty(queue)) {
        return QUEUE_ERROR_VAL;
    }
    return queue->head->value;
}

// return QUEUE_ERROR_VAL if empty/deleted queue provided
QUEUE_DTYPE dequeue(Queue queue) {
    if (!queue || isEmpty(queue)) {
        return QUEUE_ERROR_VAL;
    }
    
    QueueNode *old_head = queue->head;
    QUEUE_DTYPE value = old_head->value;
    
    QueueNode *new_head = old_head->next;
    queue->head = new_head;

    if (NULL == new_head) {
        // was only 1 item in queue, now 0
        queue->tail = NULL;
    }
    
    free(old_head);
    return value;
}

bool enqueue(Queue queue, QUEUE_DTYPE value) {
    if (!queue) { return false; }
    
    // create the new node
    QueueNode* node = initQueueNode(value);
    if (!node) { return false; }
    node->next = NULL;  // redundant but safe

    if ( isEmpty(queue) ) {
        // only 1 item now, head == tail
        queue->head = node;
    
    } else {
        // extend the tail of linked list with new node
        queue->tail->next = node;
    }
    // update QueueMeta with new tail
    queue->tail = node;

    return true;
}

void deleteQueue(Queue* _queue) {
    if (!_queue || !*_queue) {
        return;
    }

    Queue queue = *_queue;
    // remove all items from Queue
    while ( !isEmpty(queue) ) {
        dequeue(queue);
    }
    
    // delete the queue's metadata
    free(queue);
    
    *_queue = NULL;
}

