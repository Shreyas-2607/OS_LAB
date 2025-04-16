#include <stdio.h>
int main() {
    int n, i, time = 0, tq, remain;
    int at[20], bt[20], rt[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    remain = n;
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    int flag = 0;
    int queue_empty = 0;
    for (time = 0, i = 0; remain != 0;) {
        if (rt[i] > 0 && at[i] <= time) {
            if (rt[i] <= tq) {
                time += rt[i];
                rt[i] = 0;
                flag = 1;
            } else {
                rt[i] -= tq;
                time += tq;
            }
            if (rt[i] == 0 && flag == 1) {
                remain--;
                tat[i] = time - at[i];
                wt[i] = tat[i] - bt[i];
                avg_wt += wt[i];
                avg_tat += tat[i];
                flag = 0;
            }
        }
        i = (i + 1) % n;
        queue_empty = 1;
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && rt[j] > 0) {
                queue_empty = 0;
                break;
            }
        }
        if (queue_empty) time++;
    }
    printf("\nPROCESS\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
