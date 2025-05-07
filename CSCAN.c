#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void cscan() {
    int size, n, head, total_movement = 0;

    // 1) Read inputs
    printf("Enter size of disk: ");
    scanf("%d", &size);

    printf("Enter number of track requests: ");
    scanf("%d", &n);

    int requests[n + 3];
    printf("Enter the track requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // 2) Append head, start (0) and end (size-1)
    requests[n++] = head;
    requests[n++] = 0;
    requests[n++] = size - 1;

    // 3) Sort all entries
    sort(requests, n);

    // 4) Find sorted index of head
    int pos;
    for (pos = 0; pos < n; pos++)
        if (requests[pos] == head)
            break;

    // 5) Print header info
    printf("\n----- CSCAN DISK SCHEDULING -----\n");
    printf("Disk size             : %d\n", size);
    printf("Initial head position : %d\n", head);

    printf("Request sequence      : ");
    for (int i = 0; i < n; i++) {
        int r = requests[i];
        // skip the artificial 0 and size‑1 markers in the sequence display
        if (r != head && r != 0 && r != size - 1)
            printf("%d ", r);
    }
    printf("\n\n%-15s %-15s %-20s\n", "FROM", "TO", "SEEK(TRACKS)");
    printf("------------------------------------------------------\n");

    // 6) Service from head up to end‑of‑disk
    for (int i = pos; i < n; i++) {
        int move = abs(head - requests[i]);
        printf("%-15d %-15d %-20d\n", head, requests[i], move);
        total_movement += move;
        head = requests[i];
    }

    // 7) Jump from end to start (zero cost in SCAN logic? we count full jump)
    if (requests[0] == 0) {
        int move = abs(head - 0);
        printf("%-15d %-15d %-20d\n", head, 0, move);
        total_movement += move;
        head = 0;
    }

    // 8) Service the remaining from start up to just before original head
    for (int i = 0; i < pos; i++) {
        int move = abs(head - requests[i]);
        printf("%-15d %-15d %-20d\n", head, requests[i], move);
        total_movement += move;
        head = requests[i];
    }

    // 9) Compute average (exclude 3 artificial entries)
    float avg_seek_time = (float)total_movement / (n - 3);

    // 10) Print summary
    printf("\nTotal tracks moved   : %d\n", total_movement);
    printf("Average seek time    : %.2f\n", avg_seek_time);
}

int main() {
    cscan();
    return 0;
}
