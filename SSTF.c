#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf() {
    int size, n, head, total_movement = 0;

    // Read disk size and requests
    printf("Enter size of disk: ");
    scanf("%d", &size);

    printf("Enter number of track requests: ");
    scanf("%d", &n);

    int requests[n], visited[n];
    printf("Enter the track requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Header info
    printf("\n----- SSTF DISK SCHEDULING -----\n");
    printf("Disk size             : %d\n", size);
    printf("Initial head position : %d\n", head);
    printf("Request sequence      : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n%-15s %-15s %-20s\n", "FROM", "TO", "SEEK(TRACKS)");
    printf("------------------------------------------------------\n");

    // Service requests by SSTF
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - head) < min_distance) {
                min_distance = abs(requests[j] - head);
                index = j;
            }
        }
        visited[index] = 1;
        printf("%-15d %-15d %-20d\n", head, requests[index], min_distance);
        total_movement += min_distance;
        head = requests[index];
    }

    float avg_seek_time = (float)total_movement / n;
    printf("\nTotal tracks moved   : %d\n", total_movement);
    printf("Average seek time    : %.2f\n", avg_seek_time);
}

int main() {
    sstf();
    return 0;
}
