#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define STACK_DTYPE int
#include "../04_abstract_data_types/stack.h"

#ifndef NUM_DISKS
#define NUM_DISKS 2
#endif

int main(void) {
    
    //3 stacks
    Stack l = initStack();
    Stack m = initStack();
    Stack r = initStack();
    
    Stack* towers[3] = { l , m , r }

    (void)l;
    (void)m;
    (void)r;

    for (size_t i = NUM_DISKS; i > 0; i--) {
        push(m, i);
    }
    
    hanoi(towers, m
    
    return 0;
}

// implement peek()

hanoi(Stack towers[3], int tower, int disk, bool right) {
    // find which stack it's in

    if (1 == disk) {
        int disk = pop(towers[tower]);  // disk 1
        int new_tower = (right) ? (tower+1) % 3 : (tower-1+3) % 3;
        push(towers[new_tower], disk);

    } else {
        // if the current value is smaller than me, have to move it first
        if (
        hanoi(towers, tower, 
    }
}

// hanoi
// moving 5
    // move 4 left
    // move 5 right
    // move 4 left

// moving 4
    // move 3 left
    // move 4 right
    // move 4 left

// moving N
    // move N-1 left
    // move N right
    // move N-1 left

// moving 1
    // move 1 right

