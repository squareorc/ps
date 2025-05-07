#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
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

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", i + 1);
        scanf("%d%d%d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = 0;
    }

    int completed = 0, current_time = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Preemptive Priority Scheduling ---\n");

    while (completed != n) {
        int idx = -1;
        int highest_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_priority) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].remaining_time == p[idx].burst_time)
                p[idx].start_time = current_time;

            p[idx].remaining_time--;
            current_time++;

            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].is_completed = 1;

                total_tat += p[idx].turnaround_time;
                total_wt += p[idx].waiting_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    // Output Table
    printf("\n%-5s %-15s %-15s %-10s %-15s %-15s %-15s\n",
           "PID", "Arrival Time", "Burst Time", "Priority", "Start Time", "TAT", "Waiting Time");
    for (int i = 0; i < n; i++) {
        printf("P%-4d %-15d %-15d %-10d %-15d %-15d %-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].start_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
