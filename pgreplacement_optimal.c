#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to get page number from logical address
int get_page_number(int logical_address, int page_size) {
    return logical_address / page_size;
}

// Function to get offset from logical address
int get_offset(int logical_address, int page_size) {
    return logical_address % page_size;
}

// Find the frame to replace using Optimal algorithm
int find_optimal(int frames[], int n_frames, int page_seq[], int n_pages, int current_index) {
    int farthest = current_index, pos = -1, i, j;
    int found;

    for (i = 0; i < n_frames; i++) {
        found = 0;
        for (j = current_index + 1; j < n_pages; j++) {
            if (frames[i] == page_seq[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        // If the page is never used again, replace it
        if (!found)
            return i;
    }
    // If all pages will be used again, replace the one with the farthest next use
    if (pos == -1)
        return 0;
    else
        return pos;
}

int main() {
    int page_size, num_frames, num_addresses;
    int logical_addresses[MAX_PAGES];

    printf("Enter page size (in bytes): ");
    scanf("%d", &page_size);

    printf("Enter number of frames in memory: ");
    scanf("%d", &num_frames);

    printf("Enter number of logical addresses to access: ");
    scanf("%d", &num_addresses);

    printf("Enter logical addresses (space-separated):\n");
    for (int i = 0; i < num_addresses; i++) {
        scanf("%d", &logical_addresses[i]);
    }

    int page_seq[MAX_PAGES];
    for (int i = 0; i < num_addresses; i++)
        page_seq[i] = get_page_number(logical_addresses[i], page_size);

    int frames[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++)
        frames[i] = -1; // Initialize frames as empty

    int page_faults = 0;

    printf("\nAddress\tPage#\tOffset\tFrame#\tPhysical Addr\tPage Fault\tFrame State\n");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_addresses; i++) {
        int logical_address = logical_addresses[i];
        int page_number = page_seq[i];
        int offset = get_offset(logical_address, page_size);

        // Check if page is already in a frame
        int found = 0, frame_index = -1;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page_number) {
                found = 1;
                frame_index = j;
                break;
            }
        }

        int physical_address = -1;
        char page_fault_str[8] = "No";
        if (!found) {
            // Page fault, replace using Optimal
            int empty_found = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    frame_index = j;
                    empty_found = 1;
                    break;
                }
            }
            if (!empty_found) {
                frame_index = find_optimal(frames, num_frames, page_seq, num_addresses, i);
            }
            frames[frame_index] = page_number;
            page_faults++;
            strcpy(page_fault_str, "Yes");
        }

        // Calculate physical address if page is present
        if (frame_index != -1)
            physical_address = frame_index * page_size + offset;

        // Print details
        printf("%d\t%d\t%d\t%d\t", logical_address, page_number, offset, frame_index);
        if (physical_address != -1)
            printf("%d\t\t", physical_address);
        else
            printf("-\t\t");
        printf("%s\t\t[", page_fault_str);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1)
                printf(" %d", frames[j]);
            else
                printf(" -");
        }
        printf(" ]\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
