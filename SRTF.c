#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
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
    int total_time = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = 0;
        total_time += p[i].burst_time;
    }

    int time = 0, completed = 0;
    int gantt[1000];  // For Gantt chart
    int last_pid = -1;

    while (completed != n) {
        int idx = -1;
        int min_time = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0) {
                if (p[i].remaining_time < min_time) {
                    min_time = p[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].remaining_time == p[idx].burst_time)
                p[idx].start_time = time;

            p[idx].remaining_time--;
            gantt[time] = p[idx].pid;
            time++;

            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].is_completed = 1;
                completed++;
            }
        } else {
            gantt[time] = -1; // Idle
            time++;
        }
    }

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    last_pid = -1;
    for (int i = 0; i < time; i++) {
        if (gantt[i] != last_pid) {
            if (gantt[i] == -1)
                printf(" IDLE |");
            else
                printf(" P%d |", gantt[i]);
            last_pid = gantt[i];
        }
    }

    // Time markers
    printf("\n0");
    last_pid = -1;
    for (int i = 1; i <= time; i++) {
        if (gantt[i] != last_pid) {
            printf("    %2d", i);
            last_pid = gantt[i];
        }
    }

    // Output Table
    float total_tat = 0, total_wt = 0;
    printf("\n\n%-5s %-15s %-15s %-15s %-15s %-15s\n",
           "PID", "Arrival Time", "Burst Time", "Start Time", "TAT", "Waiting Time");

    for (int i = 0; i < n; i++) {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        printf("P%-4d %-15d %-15d %-15d %-15d %-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
