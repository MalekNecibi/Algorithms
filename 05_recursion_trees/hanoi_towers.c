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
    size_t num_moves = hanoi(NUM_DISKS);
    printf("\n%zu moves\n", num_moves);
    
    return 0;
}


size_t _hanoi(Stack towers[3], int tower, int depth, enum Direction dir) {
    int orig_tower = tower % 3;
    int dir_tower  = (tower + dir + 3) % 3;
    int ndir_tower  = (tower - dir + 3) % 3;
    
    size_t num_moves = 0;

    if (1 == depth) {
        int disk = pop(towers[orig_tower]);
        printf("disk %d: %d -> %d\n", disk, tower, dir_tower);
        push(towers[dir_tower], disk);
        return 1;
        
    } else if (depth > 1) {
        num_moves += _hanoi(towers, orig_tower, depth-1, -dir);
        num_moves += _hanoi(towers, orig_tower, 1      , dir);    
        num_moves += _hanoi(towers, ndir_tower, depth-1, -dir);    
    } else {
        printf("error: invalid depth? %d\n", depth);
    }
    return num_moves;
}

size_t hanoi(int num_disks) {
    // 1 stack per tower
    Stack l = initStack();
    Stack m = initStack();
    Stack r = initStack();
    
    Stack towers[3] = { l , m , r };
    
    // pre-populate center-stack with disks
    for (size_t i = num_disks; i > 0; i--) {
        push(m, i);
    }
    
    enum Tower tower = Middle;
    size_t num_moves = _hanoi(towers, tower, num_disks, Rightward);

    deleteStack(&l);
    deleteStack(&m);
    deleteStack(&r);
    
    return num_moves;
}



