#include <stdio.h>

int main() {
    int n, i, time = 0, smallest, end;
    int at[20], bt[20], prio[20], rt[20], wt[20], tat[20], completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &prio[i]);
        rt[i] = bt[i];
    }

    while (completed != n) {
        int highest_priority = 9999;
        int index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && prio[i] < highest_priority) {
                highest_priority = prio[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        rt[index]--;
        time++;

        if (rt[index] == 0) {
            completed++;
            end = time;
            tat[index] = end - at[index];
            wt[index] = tat[index] - bt[index];
            avg_wt += wt[index];
            avg_tat += tat[index];
        }
    }

    printf("\nPROCESS\tAT\tBT\tPRIORITY\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, at[i], bt[i], prio[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
