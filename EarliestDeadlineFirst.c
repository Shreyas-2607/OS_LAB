#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int deadline;
    int execution_time;
    int remaining_time;
} Task;

void sort_by_deadline(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void edf_scheduling(Task tasks[], int n, int total_time) {
    for (int t = 0; t < total_time; t++) {
        sort_by_deadline(tasks, n);
        
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                printf("Time %d: Executing Task %d\n", t, tasks[i].id);
                tasks[i].remaining_time--;

                if (tasks[i].remaining_time == 0)
                    tasks[i].remaining_time = tasks[i].execution_time; // Reset for next cycle

                executed = 1;
                break;
            }
        }
        if (!executed) {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    Task tasks[MAX_TASKS] = {
        {1, 3, 1, 1},
        {2, 5, 2, 2},
        {3, 7, 2, 2}
    };
    int num_tasks = 3;
    int total_time = 15; // Simulation time

    edf_scheduling(tasks, num_tasks, total_time);
    return 0;
}