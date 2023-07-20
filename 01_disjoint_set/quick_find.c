#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUM_NODES 1000
#define NUM_PAIRS 25000

// quick find

size_t _find(size_t node, size_t *parents) {
    return parents[node];
}

void _union(size_t p, size_t q, size_t *parents, size_t parentsLen) {
    size_t p_ = _find(p, parents);
    size_t q_ = _find(q, parents);

    if (p_ != q_) {
        // anything that shared p's parent gets replaced with q's parent
        for (size_t i = 0; i < parentsLen;i++) {
            if (parents[i] == p_) {
                parents[i] = q_;
            }
        }
    }
}

int main(void) {
    
    size_t pairs[NUM_PAIRS][2] = { {1,2},{2,3},{3,4} };
    size_t pairsLen = NUM_PAIRS;
    
    size_t testA = 1;
    size_t testB = 4; // 5

    size_t parents[NUM_NODES];
    for (size_t i = 0; i < NUM_NODES; i++) {
        parents[i] = i;
    }

    for (size_t p = 0; p < pairsLen; p++) {
        size_t nodeA = pairs[p][0];
        size_t nodeB = pairs[p][1];
        
        _union(nodeA, nodeB, parents, NUM_NODES);
    }

    bool connected = _find(testA, parents) == _find(testB, parents);
    printf("%zu and %zu : %sconnected\n", testA, testB, connected ? "" : "dis");

    return 0;
}
