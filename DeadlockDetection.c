#include <stdio.h>
#include <stdbool.h>

#define MAX 10  

bool isSafe(int n, int m, int avail[], int max[][MAX], int allot[][MAX]);
bool isRequestValid(int request[], int avail[], int m);
bool canAllocate(int request[], int avail[], int m);
void requestResources(int n, int m, int avail[], int max[][MAX], int allot[][MAX], int processID, int request[]);
bool isDeadlocked(int n, int m, int avail[], int max[][MAX], int allot[][MAX]);
void detectDeadlock(int n, int m, int avail[], int max[][MAX], int allot[][MAX]);

int main() {
    int n, m, choice;
    int avail[MAX], max[MAX][MAX], allot[MAX][MAX], request[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    printf("\nEnter available resources: ");

    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    printf("\nEnter max resources for each process:\n");
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) scanf("%d", &max[i][j]);

    printf("\nEnter allocated resources for each process:\n");
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) scanf("%d", &allot[i][j]);

    printf("\n1. Banker's Algorithm for Deadlock Avoidance\n");
    printf("2. Deadlock Detection\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nEnter process ID to request resources: ");
            int processID;
            scanf("%d", &processID);
            printf("Enter resource request: ");
            for (int i = 0; i < m; i++) scanf("%d", &request[i]);
            if (isRequestValid(request, avail, m) && canAllocate(request, avail, m)) {
                requestResources(n, m, avail, max, allot, processID, request);
                if (isSafe(n, m, avail, max, allot)) 
                    printf("\nRequest granted, system is in a safe state.\n");
                else 
                    printf("\nRequest denied, system is not in a safe state.\n");
            } else 
                printf("\nRequest denied.\n");
            break;
        case 2:
            detectDeadlock(n, m, avail, max, allot);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}

bool isRequestValid(int request[], int avail[], int m) {
    for (int i = 0; i < m; i++) if (request[i] < 0 || request[i] > avail[i]) return false;
    return true;
}

bool canAllocate(int request[], int avail[], int m) {
    for (int i = 0; i < m; i++) if (request[i] > avail[i]) return false;
    return true;
}

void requestResources(int n, int m, int avail[], int max[][MAX], int allot[][MAX], int processID, int request[]) {
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
        max[processID][i] -= request[i];
    }
}

bool isSafe(int n, int m, int avail[], int max[][MAX], int allot[][MAX]) {
    int work[m], finish[n];
    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int r = 0; r < m; r++) if (max[p][r] - allot[p][r] > work[r]) canFinish = false;
                if (canFinish) {
                    for (int r = 0; r < m; r++) work[r] += allot[p][r];
                    finish[p] = 1;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool isDeadlocked(int n, int m, int avail[], int max[][MAX], int allot[][MAX]) {
    int work[m], finish[n];
    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int r = 0; r < m; r++) if (max[p][r] - allot[p][r] > work[r]) canFinish = false;
                if (canFinish) {
                    for (int r = 0; r < m; r++) work[r] += allot[p][r];
                    finish[p] = 1;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) return true;
    }
    return false;
}

void detectDeadlock(int n, int m, int avail[], int max[][MAX], int allot[][MAX]) {
    if (isDeadlocked(n, m, avail, max, allot)) 
        printf("\nDeadlock detected!\n");
    else 
        printf("\nNo deadlock detected.\n");
}