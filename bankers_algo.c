#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int Allocation[n][m], Max[n][m], Need[n][m], Available[m];
    int i, j;

    // Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    // Input Max Matrix
    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    // Input Available Resources
    printf("Enter Available Resources (%d):\n", m);
    for(j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    // Calculate Need Matrix
    printf("\nCalculating Need Matrix (Max - Allocation):\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for(j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    // Safety Algorithm
    bool Finish[n];
    int SafeSeq[n], count = 0;
    int Work[m];
    for(j = 0; j < m; j++)
        Work[j] = Available[j];
    for(i = 0; i < n; i++)
        Finish[i] = false;

    printf("\nStarting Safety Algorithm:\n");
    while(count < n) {
        bool found = false;
        for(i = 0; i < n; i++) {
            if(!Finish[i]) {
                bool possible = true;
                for(j = 0; j < m; j++) {
                    if(Need[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }
                if(possible) {
                    printf("Process %d can be satisfied (Need: ", i);
                    for(j = 0; j < m; j++)
                        printf("%d ", Need[i][j]);
                    printf("| Work: ");
                    for(j = 0; j < m; j++)
                        printf("%d ", Work[j]);
                    printf(")\n");

                    // Simulate resource allocation
                    for(j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Finish[i] = true;
                    SafeSeq[count++] = i;
                    found = true;

                    printf("After executing process %d, Available becomes: ", i);
                    for(j = 0; j < m; j++)
                        printf("%d ", Work[j]);
                    printf("\n");
                }
            }
        }
        if(!found) {
            printf("\nSystem is NOT in a safe state. Deadlock possible.\n");
            return 1;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
    for(i = 0; i < n; i++)
        printf("P%d ", SafeSeq[i]);
    printf("\n");

    return 0;
}
