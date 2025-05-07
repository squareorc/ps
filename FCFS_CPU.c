#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void sort_by_arrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
    }

    // Sort processes by arrival time
    sort_by_arrival(p, n);

    // Calculate times
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;

        p[i].start_time = current_time;
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].start_time - p[i].arrival_time;

        current_time = p[i].completion_time;
    }

    // Output Table
    printf("\n%-10s%-15s%-15s%-15s%-20s%-15s%-15s\n",
        "PID", "Arrival Time", "Burst Time", "Start Time", "Completion Time", "TAT", "Waiting Time");
    
    for (int i = 0; i < n; i++) {
        printf("P%-9d%-15d%-15d%-15d%-20d%-15d%-15d\n",
            p[i].pid, p[i].arrival_time, p[i].burst_time,
            p[i].start_time, p[i].completion_time,
            p[i].turnaround_time, p[i].waiting_time);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", p[i].pid);
    }

    // Time markers
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("     %2d", p[i].completion_time);
    }

    // Avg TAT and WT
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }
    avg_tat /= n;
    avg_wt /= n;

    printf("\n\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);

    return 0;
}
