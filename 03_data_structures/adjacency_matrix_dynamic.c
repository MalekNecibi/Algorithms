#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int main(int argc, char* argv[]) {
    int nodeA = 0;
    int nodeB = 0;

    int minNode = INT_MAX;
    int maxNode = INT_MIN;
    
    int num_pairs;
    printf("How many pairs of points : ");
    scanf("%d", &num_pairs);
    
    int (*pairs)[2] = malloc(2 * num_pairs * sizeof(int));
    for (int i = 0; i < num_pairs; i++) {
        scanf("%d %d", &nodeA, &nodeB);
        
        pairs[i][0] = nodeA;
        pairs[i][1] = nodeB;

        minNode = (minNode < nodeA) ? minNode : nodeA;
        minNode = (minNode < nodeB) ? minNode : nodeB;

        maxNode = (maxNode > nodeA) ? maxNode : nodeA;
        maxNode = (maxNode > nodeB) ? maxNode : nodeB;
    }
    printf("\n");
    
    // could exclude intermediate values, but takes away from focus of exercise (needs hash table)
    int range = maxNode - minNode + 1;
    
    int* matrix = calloc(range * range, sizeof(int));
    for (int i = 0; i < num_pairs; i++) {
        int nodeA = pairs[i][0];
        int nodeB = pairs[i][1];
        // matrix[nodeA][nodeB]
        *(matrix+range*(nodeA-minNode)+(nodeB-minNode)) = 1;
        // matrix[nodeB][nodeA]
        *(matrix+range*(nodeB-minNode)+(nodeA-minNode)) = 1;
        
    }
    

    // print out the adjacency matrix
    printf("        ");
    for (int i = 0; i < range; i++) {
        printf("%5d ", minNode + i);
    }
    printf("\n        ");
    for (int i = 0; i < range; i++) {
        printf("    - ");
    }
    printf("\n");
    for (int i = 0; i < range; i++) {
        printf("%4d : ", minNode+i);
        for (int j = 0; j < range; j++) {
            printf("%6d", *(matrix+range*i+j));
        }
        printf("\n");
    }

    
    
    return 0;
}
