#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_NAME_LENGTH 20

typedef struct {
    int pid;  
    char name[MAX_NAME_LENGTH]; 
    int burst_time;  
} Process;


void FCFS(Process queue[], int n) {
    int total_wait_time = 0, total_turnaround_time = 0;
    printf("\nScheduling processes with FCFS...\n");
    printf("PID\tName\tBurst Time\tWaiting Time\tTurnaround Time\n");                     

    int waiting_time = 0;  
    for (int i = 0; i < n; i++) {
        int turnaround_time = queue[i].burst_time + waiting_time;
        printf("%d\t%s\t%d\t\t%d\t\t%d\n", queue[i].pid, queue[i].name, queue[i].burst_time, waiting_time, turnaround_time);
       
        total_wait_time += waiting_time;
        total_turnaround_time += turnaround_time;
       
        waiting_time += queue[i].burst_time;  
    }
   
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void input_processes(Process queue[], int *n) {
    printf("Enter the number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        queue[i].pid = i + 1;
        printf("Enter the name of process %d: ", i + 1);
        scanf("%s", queue[i].name);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &queue[i].burst_time);
    }
}

int main() {
    Process system_queue[MAX_PROCESSES], user_queue[MAX_PROCESSES];
    int system_count, user_count;

    printf("Enter details for system processes:\n");
    input_processes(system_queue, &system_count);

    printf("\nEnter details for user processes:\n");
    input_processes(user_queue, &user_count);

    printf("\nScheduling system processes:\n");
    FCFS(system_queue, system_count);

    printf("\nScheduling user processes:\n");
    FCFS(user_queue, user_count);

    return 0;
}