#include <stdio.h>
#define MAX 20

int main() {
    int bt[MAX], at[MAX], rt[MAX], wt[MAX], tat[MAX];
    int i, smallest, count = 0, time, n;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    int complete = 0;
    int min_time = 9999;
    int shortest = 0;
    int finish_time;
    int check = 0;

    for (time = 0; complete != n; time++) {
        shortest = -1;
        min_time = 9999;

        for (i = 0; i < n; i++) {
            if ((at[i] <= time) && (rt[i] < min_time) && rt[i] > 0) {
                min_time = rt[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            continue;
        }

        rt[shortest]--;

        if (rt[shortest] == 0) {
            complete++;
            finish_time = time + 1;

            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;

            tat[shortest] = wt[shortest] + bt[shortest];

            avg_wt += wt[shortest];
            avg_tat += tat[shortest];
        }
    }

    printf("\nPROCESS\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
