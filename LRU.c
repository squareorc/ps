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

// Find the least recently used frame
int find_lru(int time[], int n_frames) {
    int min = time[0], pos = 0;
    for(int i = 1; i < n_frames; i++) {
        if(time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
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

    int frames[MAX_FRAMES];
    int time[MAX_FRAMES]; // To track last used time for LRU
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1; // Initialize frames as empty
        time[i] = 0;
    }

    int page_faults = 0, counter = 0;

    printf("\nAddress\tPage#\tOffset\tFrame#\tPhysical Addr\tPage Fault\tFrame State\n");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_addresses; i++) {
        int logical_address = logical_addresses[i];
        int page_number = get_page_number(logical_address, page_size);
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
            // Page fault, replace using LRU
            int empty_found = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    frame_index = j;
                    empty_found = 1;
                    break;
                }
            }
            if (!empty_found) {
                frame_index = find_lru(time, num_frames);
            }
            frames[frame_index] = page_number;
            page_faults++;
            strcpy(page_fault_str, "Yes");
        }
        // Update the time for LRU
        counter++;
        time[frame_index] = counter;

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
