#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// exclusive : [0-MAX_VALUE)
#define MAX_VALUE 25


// 3.39 Write a function that takes two arguments -a link to a list, and a function 
//      that takes a link as argument- and removes all items on the given list for
//      which the function returns a nonzero value

// 3.40 Solve Exercise 3.39, but make "copies" of the nodes that pass the test and return
//      a link to a list containing those nodes, in the order that they appear in 
//      the original list

struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* generateList(int num_nodes);
void printList(struct ListNode* head);

// split Linked List into 2 lists based on nonzero, maintaining initial order
int main(int argc, char* argv[]) {
    // how many elements in Linked List ? (default: 30)
    int num_nodes;
    if (argc >= 2) {
        num_nodes = atoi(argv[1]);
    } else {
        num_nodes = 30;
    }
    
    srand((unsigned int) time(NULL));
    rand();

    struct ListNode* head = generateList(num_nodes);

    printf("Initial ");
    printList(head);

    struct ListNode dummy_nonzeros;
    struct ListNode* nonzeros_tail = &dummy_nonzeros;
    nonzeros_tail->next = NULL;
    
    struct ListNode dummy_zeros;
    struct ListNode* zeros_head = &dummy_zeros;
    zeros_head->next = head;
    
    struct ListNode* node = head;
    struct ListNode* prev = zeros_head;
    while (node) {
        if (0 != node->val) {
            prev->next = node->next;
            nonzeros_tail->next = node;
            nonzeros_tail = node;
            node->next = NULL;
            node = prev->next;
            
        } else {
            prev = node;
            node = node->next;
        }
    }
    
    printf("\n");
    printf("Zeros ");
    printList(dummy_zeros.next);
    
    printf("Non-Zeros ");
    printList(dummy_nonzeros.next);
    
    // Not implementing free intentionally, different exercise
    // free(*Lists);
    //return dummy->next;
}


struct ListNode* generateList(int num_nodes) {
    
    // below would be safer bc centralizes malloc failure, but intentionally not doing it
    //struct ListNode* all_nodes = malloc(num_nodes * sizeof(struct ListNode));
    //struct ListNode *head = &all_nodes[0];
    
    // intentionally not error-checking malloc
    struct ListNode *head = malloc( sizeof(struct ListNode) );
    head->val = rand() % MAX_VALUE;
    head->next = NULL;
    
    struct ListNode* node = head;
    for (int i = 1; i < num_nodes; i++) {
        struct ListNode* new =  malloc( sizeof(struct ListNode) );
        node->next = new;
        new->val = rand() % MAX_VALUE;
        new->next = NULL;

        node = new;
    }
    return head;
}

void printList(struct ListNode* head) {
    printf("List:\n");
    struct ListNode* node = head;
    while (node) {
//        printf("%d\n", head->val);
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}
