#include <stdio.h>

int main() {
    int page_size, num_pages, logical_address;
    printf("Enter page size (in bytes): ");
    scanf("%d", &page_size);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    int page_table[num_pages];
    printf("Enter the frame number for each page (page table):\n");
    for(int i = 0; i < num_pages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &page_table[i]);
    }

    printf("\nEnter the logical (virtual) address to translate: ");
    scanf("%d", &logical_address);

    // Step 1: Calculate page number and offset
    int page_number = logical_address / page_size;
    int offset = logical_address % page_size;

    printf("\nStep 1: Calculate page number and offset\n");
    printf("  Logical Address: %d\n", logical_address);
    printf("  Page Size: %d bytes\n", page_size);
    printf("  Page Number (Logical Address / Page Size): %d\n", page_number);
    printf("  Offset (Logical Address %% Page Size): %d\n", offset);

    // Step 2: Use page number as index in page table to get frame number
    int frame_number;
    if(page_number < 0 || page_number >= num_pages) {
        printf("\nError: Page number %d out of range!\n", page_number);
        return 1;
    }
    frame_number = page_table[page_number];

    printf("\nStep 2: Index page table\n");
    printf("  Page Table[%d] = %d (Frame Number)\n", page_number, frame_number);

    // Step 3: Calculate physical address
    int physical_address = frame_number * page_size + offset;

    printf("\nStep 3: Calculate physical (real) address\n");
    printf("  Physical Address = Frame Number * Page Size + Offset\n");
    printf("  Physical Address = %d * %d + %d = %d\n", frame_number, page_size, offset, physical_address);

    printf("\nFinal Result:\n");
    printf("  Logical Address %d -> Physical Address %d\n", logical_address, physical_address);

    return 0;
}
