#include <stdio.h>

int main() {
    int n_blocks, n_procs, i, j;
    printf("Enter number of memory blocks: ");
    scanf("%d", &n_blocks);

    int block_size[n_blocks], block_alloc[n_blocks];
    printf("Enter sizes of each memory block:\n");
    for(i = 0; i < n_blocks; i++) {
        scanf("%d", &block_size[i]);
        block_alloc[i] = -1; // -1 means block is free
    }

    printf("Enter number of processes: ");
    scanf("%d", &n_procs);

    int proc_size[n_procs], proc_alloc[n_procs];
    printf("Enter sizes of each process:\n");
    for(i = 0; i < n_procs; i++) {
        scanf("%d", &proc_size[i]);
        proc_alloc[i] = -1; // -1 means process not allocated
    }

    // Best Fit Allocation
    for(i = 0; i < n_procs; i++) {
        int best_idx = -1;
        for(j = 0; j < n_blocks; j++) {
            if(block_alloc[j] == -1 && block_size[j] >= proc_size[i]) {
                if(best_idx == -1 || block_size[j] < block_size[best_idx]) {
                    best_idx = j;
                }
            }
        }
        if(best_idx != -1) {
            block_alloc[best_idx] = i;    // Allocate block to process
            proc_alloc[i] = best_idx;     // Process gets block
        }
    }

    // Output allocation table
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(i = 0; i < n_procs; i++) {
        printf("%d\t\t%d\t\t", i+1, proc_size[i]);
        if(proc_alloc[i] != -1)
            printf("%d\n", proc_alloc[i]+1);
        else
            printf("Not Allocated\n");
    }

    // Calculate external fragmentation only if any process is unallocated
    int total_external_frag = 0, any_unallocated = 0;
    for(i = 0; i < n_procs; i++) {
        if(proc_alloc[i] == -1) {
            any_unallocated = 1;
            break;
        }
    }
    if(any_unallocated) {
        for(i = 0; i < n_blocks; i++) {
            if(block_alloc[i] == -1)
                total_external_frag += block_size[i];
        }
        printf("\nTotal External Fragmentation: %d\n", total_external_frag);
    } else {
        printf("\nNo External Fragmentation (all processes allocated).\n");
    }

    return 0;
}
