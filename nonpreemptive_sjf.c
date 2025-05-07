#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].is_completed = 0;
    }

    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\nExecution Order (Gantt Chart):\n|");
    while (completed != n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_tat += p[idx].turnaround_time;
            total_wt += p[idx].waiting_time;

            current_time = p[idx].completion_time;
            p[idx].is_completed = 1;
            completed++;

            printf(" P%d |", p[idx].pid);
        } else {
            printf(" IDLE |");
            current_time++;
        }
    }

    // Print timeline for Gantt Chart
    printf("\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].is_completed) {
            if (p[i].start_time > current_time) {
                printf("   %2d", p[i].start_time); // Idle time
            }
            printf("   %2d", p[i].completion_time);
            current_time = p[i].completion_time;
        }
    }

    // Output Table
    printf("\n\n%-5s %-15s %-15s %-15s %-15s %-15s\n",
           "PID", "Arrival Time", "Burst Time", "Start Time", "TAT", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("P%-4d %-15d %-15d %-15d %-15d %-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
