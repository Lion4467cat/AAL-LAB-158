#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find the set of an element i (path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two sets (union by rank)
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function to sort edges by weight (for qsort)
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to implement Kruskal's algorithm to find the MST
void kruskalMST(int V, struct Edge edges[], int E) {
    // Allocate memory for the resulting MST edges
    struct Edge* result = (struct Edge*)malloc(sizeof(struct Edge) * (V - 1));
    int e = 0; // Index for the next available edge in result
    int i = 0; // Index for iterating through sorted edges

    // Sort the edges by weight in ascending order
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Allocate memory for V subsets
    struct Subset* subsets = (struct Subset*)malloc(sizeof(struct Subset) * V);

    // Initialize V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Iterate through the sorted edges
    while (e < V - 1 && i < E) {
        // Pick the smallest edge
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it
        // in the result and increment the index of result for the next edge
        if (x != y) {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // Print the edges in the constructed MST
    printf("Edges in the Minimum Spanning Tree:\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d    Weight: %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }

    printf("Minimum Cost of MST: %d\n", minimumCost);

    // Free allocated memory
    free(result);
    free(subsets);
}

// Example usage:
int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(V, edges, E);

    return 0;
}
