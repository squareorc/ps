#include <stdio.h>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int start_time;
    int is_started;
};

int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].is_started = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0, visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    printf("\nGantt Chart:\n|");

    while (completed != n)
    {
        if (front == rear)
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && p[i].arrival_time <= time)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (!p[idx].is_started)
        {
            p[idx].start_time = time;
            p[idx].is_started = 1;
        }

        int exec_time = (p[idx].remaining_time >= tq) ? tq : p[idx].remaining_time;
        printf(" P%d |", p[idx].pid);

        time += exec_time;
        p[idx].remaining_time -= exec_time;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].arrival_time <= time)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remaining_time > 0)
        {
            queue[rear++] = idx;
        }
        else
        {
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            completed++;
        }
    }

    // Time markers
    printf("\n0");
    time = 0;
    front = rear = 0;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n)
    {
        if (front == rear)
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && p[i].arrival_time <= time)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int exec_time = (p[idx].remaining_time >= tq) ? tq : p[idx].remaining_time;
        time += exec_time;

        printf("   %2d", time);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].arrival_time <= time)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remaining_time > 0)
        {
            queue[rear++] = idx;
        }
        else
        {
            completed++;
        }
    }

    // Output Table
    float total_tat = 0, total_wt = 0;
    printf("\n\n%-5s %-15s %-15s %-15s %-15s %-15s\n",
           "PID", "Arrival Time", "Burst Time", "Start Time", "TAT", "Waiting Time");

    for (int i = 0; i < n; i++)
    {
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
