#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int Allocation[n][m], Request[n][m], Available[m];
    int i, j;

    // Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    // Input Request Matrix
    printf("Enter Request Matrix (%d x %d):\n", n, m);
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Request[i][j]);

    // Input Available Resources
    printf("Enter Available Resources (%d):\n", m);
    for(j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    // Initialize Work and Finish
    int Work[m];
    bool Finish[n];
    for(j = 0; j < m; j++)
        Work[j] = Available[j];

    for(i = 0; i < n; i++) {
        bool allZero = true;
        for(j = 0; j < m; j++) {
            if(Allocation[i][j] != 0) {
                allZero = false;
                break;
            }
        }
        Finish[i] = allZero;
    }

    printf("\nInitial Work (Available): ");
    for(j = 0; j < m; j++)
        printf("%d ", Work[j]);
    printf("\n");

    // Detection Algorithm
    bool found;
    do {
        found = false;
        for(i = 0; i < n; i++) {
            if(!Finish[i]) {
                bool canProceed = true;
                for(j = 0; j < m; j++) {
                    if(Request[i][j] > Work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if(canProceed) {
                    printf("Process %d can be satisfied (Request: ", i);
                    for(j = 0; j < m; j++)
                        printf("%d ", Request[i][j]);
                    printf("| Work: ");
                    for(j = 0; j < m; j++)
                        printf("%d ", Work[j]);
                    printf(")\n");

                    for(j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Finish[i] = true;
                    found = true;

                    printf("After executing process %d, Work becomes: ", i);
                    for(j = 0; j < m; j++)
                        printf("%d ", Work[j]);
                    printf("\n");
                }
            }
        }
    } while(found);

    // Output Deadlock Information
    bool deadlock = false;
    printf("\nProcesses in deadlock: ");
    for(i = 0; i < n; i++) {
        if(!Finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if(deadlock)
        printf("\nDeadlock detected!\n");
    else
        printf("None\nNo deadlock detected.\n");

    return 0;
}
