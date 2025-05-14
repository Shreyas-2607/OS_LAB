#include <stdio.h>

#define MAX_BLOCKS 20
#define MAX_PROCESSES 10

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

   
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

  
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

 
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) {
                    worstIdx = j;
                }
            }
        }

   
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }


    printf("\nWorst-fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];


    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }


    for (int i = 0; i < n; i++) {
        int bestIdx = -1;

        
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

   
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }


    printf("\nBest-fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];


    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }


    printf("\nFirst-fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

int main() {
    int m, n;
    

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];


    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
    }


    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }


    worstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    firstFit(blockSize, m, processSize, n);

    return 0;
}
