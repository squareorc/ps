#include <stdio.h>

int main() {
    int num_segments;
    printf("Enter number of segments: ");
    scanf("%d", &num_segments);

    int base[num_segments], limit[num_segments];
    for (int i = 0; i < num_segments; i++) {
        printf("Enter base (start address) of segment %d: ", i);
        scanf("%d", &base[i]);
        printf("Enter limit (length) of segment %d: ", i);
        scanf("%d", &limit[i]);
    }

    int seg_num, offset;
    printf("\nEnter logical address (segment number and offset):\n");
    printf("Segment number: ");
    scanf("%d", &seg_num);
    printf("Offset: ");
    scanf("%d", &offset);

    printf("\nStep 1: Index segment table with segment number\n");
    printf("  Segment number: %d\n", seg_num);

    if (seg_num < 0 || seg_num >= num_segments) {
        printf("  Error: Segment number %d out of range!\n", seg_num);
        return 1;
    }

    printf("  Base: %d\n", base[seg_num]);
    printf("  Limit: %d\n", limit[seg_num]);

    printf("\nStep 2: Check if offset is within segment limit\n");
    printf("  Offset: %d\n", offset);

    if (offset < 0 || offset >= limit[seg_num]) {
        printf("  Error: Offset %d exceeds segment limit %d! Segmentation fault.\n", offset, limit[seg_num]);
        return 1;
    }

    printf("\nStep 3: Calculate physical (real) address\n");
    int physical_address = base[seg_num] + offset;
    printf("  Physical Address = Base + Offset = %d + %d = %d\n", base[seg_num], offset, physical_address);

    printf("\nFinal Result:\n");
    printf("  Logical Address (Segment %d, Offset %d) -> Physical Address %d\n", seg_num, offset, physical_address);

    return 0;
}
