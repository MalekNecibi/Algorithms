#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#define STACK_DTYPE int
#define STACK_ERROR_VAL INT_MIN
#include "../utils/stack.h"


#ifndef NUM_DISKS
#define NUM_DISKS 5
#endif

enum Tower { Left = 0 , Middle = 1 , Right = 2 };
enum Direction { Leftward = (-1) , Rightward = (+1) };

size_t hanoi(int num_disks);

int main(void) {
    printf("\n%d disks require %zu moves\n", NUM_DISKS, hanoi(NUM_DISKS));
    
    return 0;
}

void moveDisk(int disk, int dir, Stack* towers, int* disk_tower, int* disk_above) {
    int orig_tower = disk_tower[ disk ];
    int dir_tower  = (orig_tower + dir + 3) % 3;
    
    pop(towers[orig_tower]);
    
    // set the new top disk
    int orig_new_top = peek(towers[orig_tower]);
    if (STACK_ERROR_VAL != orig_new_top) {
        disk_above[orig_new_top] = 0;
    }

    int dir_old_top = peek(towers[dir_tower]);
    if (STACK_ERROR_VAL != dir_old_top) {
        disk_above[dir_old_top] = disk;
    }
    
    push(towers[dir_tower], disk);
    printf("disk %d: %d -> %d\n", disk, orig_tower, dir_tower);
    disk_tower[disk] = dir_tower;
    disk_above[disk] = 0;  // redundant but safe
}

size_t hanoi(int num_disks) {
    Stack l = initStack();
    Stack m = initStack();
    Stack r = initStack();
    
    Stack towers[3] = { l , m , r };
    
    //  1-indexed, [0] is unused

    // which tower am I inside
    int* disk_tower = malloc((1 + num_disks) * sizeof(int));
    // which disk is currently above me?
    int* disk_above = malloc((1 + num_disks) * sizeof(int));
    
    // pre-populate center-stack with disks (0 == top)
    for (size_t i = num_disks; i > 0; i--) {
        push(m, i);
        disk_tower[i] = Middle;
        disk_above[i] = i-1;
    }
    
    
    Stack next_moves = initStack();
    push(next_moves, num_disks * Rightward);
    
    size_t num_moves = 0;
    
    while (!isEmpty(next_moves)) {
        int move = pop(next_moves);
        
        int dir = (move > 0) ? (+1) : (-1) ;
        int disk = move / dir;
        
        // if disk is on top of stack
        if ( 0 == disk_above[disk] ) {
            moveDisk(disk, dir, towers, disk_tower, disk_above);
            num_moves++;
            
        } else {
            int above = disk_above[disk];
            
            // NOTE: processed in reverse order, but not relevant here bc operations are symmetrical
            push(next_moves, -dir * above);
            push(next_moves, dir * disk);
            push(next_moves, -dir * above);
        
        }
    }
    
    deleteStack(&next_moves);

    deleteStack(&l);
    deleteStack(&m);
    deleteStack(&r);
    
    free(disk_tower);
    free(disk_above);
    return num_moves;
}



