#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#ifndef DTYPE
#define DTYPE int
#endif

#ifndef QUEUE_ERROR_VAL
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
    DTYPE value;
    struct ListNode* next;
};

// private
QueueNode* initQueueNode(DTYPE value) {
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

// return QUEUE_ERROR_VAL if empty/deleted queue provided
DTYPE dequeue(Queue queue) {
    if (!queue || isEmpty(queue)) {
        return QUEUE_ERROR_VAL;
    }
    
    QueueNode *old_head = queue->head;
    DTYPE value = old_head->value;
    
    QueueNode *new_head = old_head->next;
    queue->head = new_head;

    if (NULL == new_head) {
        // was only 1 item in queue, now 0
        queue->tail = NULL;
    }
    
    free(old_head);
    return value;
}

bool enqueue(Queue queue, DTYPE value) {
    if (!queue) {
        return false;
    }
    
    QueueNode* node = initQueueNode(value);
    if (!node) {
        return false;
    }
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

int main(void) {
    Queue q = initQueue();
    enqueue(q, 12);
    
    printf("%d\n", dequeue(q));
    
    enqueue(q, 17);
    printf("%d\n", dequeue(q));

    enqueue(q, 19);
    enqueue(q, 19282);
    printf("%d\n", dequeue(q));
    enqueue(q, -2189);

    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    
    // dequeue more than enqueue
    printf("%d (should be %d)\n", dequeue(q), QUEUE_ERROR_VAL);
    
    enqueue(q, 38);
    enqueue(q, 239792);
    printf("%d\n", dequeue(q));

    deleteQueue(&q);


    // should fail with QUEUE_ERROR_VAL
    enqueue(q, 18);
    enqueue(q, 1);
    enqueue(q, -9304792);
    printf("Dequeue after deletion returns QUEUE_ERROR_VAL? %s\n", (dequeue(q) == QUEUE_ERROR_VAL) ? "true" : "false");

    deleteQueue(&q);

    return 0;
}
