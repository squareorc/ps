#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MAX_TREE_NODES 1024

typedef struct BuddyNode
{
    int size;       // Size of this block
    int start;      // Start address (offset)
    int is_free;    // 1 if free, 0 if allocated
    int process_id; // -1 if free, else process number
    struct BuddyNode *left, *right;
} BuddyNode;

// Utility: Next power of two >= n
int next_power_of_two(int n)
{
    int p = 1;
    while (p < n)
        p <<= 1;
    return p;
}

// Create a buddy node
BuddyNode *create_node(int size, int start)
{
    BuddyNode *node = (BuddyNode *)malloc(sizeof(BuddyNode));
    node->size = size;
    node->start = start;
    node->is_free = 1;
    node->process_id = -1;
    node->left = node->right = NULL;
    return node;
}

// Allocate memory for a process
BuddyNode *allocate(BuddyNode *node, int req_size, int pid)
{
    if (!node->is_free)
        return NULL;
    if (node->size < req_size)
        return NULL;

    // If this node is a perfect fit
    if (node->size == req_size && node->is_free && node->left == NULL && node->right == NULL)
    {
        node->is_free = 0;
        node->process_id = pid;
        return node;
    }

    // If not already split, split the node
    if (node->left == NULL && node->right == NULL)
    {
        int half = node->size / 2;
        node->left = create_node(half, node->start);
        node->right = create_node(half, node->start + half);
    }

    // Try to allocate in left, then right
    BuddyNode *res = allocate(node->left, req_size, pid);
    if (res)
    {
        // If allocation happened in left, check if both children are allocated to mark this as not free
        node->is_free = (node->left->is_free || node->right->is_free);
        return res;
    }
    res = allocate(node->right, req_size, pid);
    node->is_free = (node->left->is_free || node->right->is_free);
    return res;
}

// Print buddy tree (pre-order, as a tree)
void print_tree(BuddyNode *node, int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("|-- ");
    if (node->is_free)
        printf("Free block: size=%d, start=%d\n", node->size, node->start);
    else if (node->left == NULL && node->right == NULL)
        printf("Allocated to P%d: size=%d, start=%d\n", node->process_id, node->size, node->start);
    else
        printf("Split block: size=%d, start=%d\n", node->size, node->start);
    if (node->left)
        print_tree(node->left, depth + 1);
    if (node->right)
        print_tree(node->right, depth + 1);
}

// Show allocation table
void show_allocations(BuddyNode *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        if (!node->is_free)
            printf("Process P%d allocated block: start=%d, size=%d\n", node->process_id, node->start, node->size);
        else
            printf("Free block: start=%d, size=%d\n", node->start, node->size);
        return;
    }
    show_allocations(node->left);
    show_allocations(node->right);
}

int main()
{
    int total_size, n, i;
    int process_size[MAX_PROCESSES];

    printf("Enter total memory size (power of 2): ");
    scanf("%d", &total_size);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter size for process %d: ", i + 1);
        scanf("%d", &process_size[i]);
    }

    BuddyNode *root = create_node(total_size, 0);

    for (i = 0; i < n; i++)
    {
        int req_size = next_power_of_two(process_size[i]);
        BuddyNode *res = allocate(root, req_size, i + 1);
        if (!res)
            printf("Process P%d (size=%d) cannot be allocated (not enough space or no suitable buddy).\n", i + 1, process_size[i]);
    }

    printf("\n=== Allocation Table ===\n");
    show_allocations(root);

    printf("\n=== Buddy System Tree ===\n");
    print_tree(root, 0);

    return 0;
}
