#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Function to perform DFS and topological sorting
void topologicalSortUtil(int v, int adj[MAX_VERTICES][MAX_VERTICES], bool visited[], int *st, int *top) {
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all adjacent vertices
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (adj[v][i]) {
            if (!visited[i]) {
                topologicalSortUtil(i, adj, visited, st, top);
            }
        }
    }

    // Push current vertex to stack which stores the result
    st[(*top)++] = v;
}

void constructadj(int V, int edges[][2], int edgeCount, int adj[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < edgeCount; i++) {
        adj[edges[i][0]][edges[i][1]] = 1;
    }
}

// Function to perform Topological Sort
void topologicalSort(int V, int edges[][2], int edgeCount, int *ans, int *ansSize) {
    // Stack to store the result
    int st[MAX_VERTICES];
    int top = 0;

    bool visited[MAX_VERTICES] = {false};
    int adj[MAX_VERTICES][MAX_VERTICES] = {0};

    // Construct the adjacency matrix from the edges
    constructadj(V, edges, edgeCount, adj);

    // Optional Debug: Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    // Call the recursive helper function to store
    // Topological Sort starting from all vertices one by one
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, adj, visited, st, &top);
        }
    }

    // Append contents of stack to ans
    *ansSize = top;
    for (int i = 0; i < top; i++) {
        ans[i] = st[top - 1 - i];
    }
}

int main() {
    // Graph represented as an adjacency list
    int v = 6;
    int edges[][2] = {{2, 3}, {3, 1}, {4, 0}, {4, 1}, {5, 0}, {5, 2}};
    int edgeCount = sizeof(edges) / sizeof(edges[0]);

    int ans[MAX_VERTICES];
    int ansSize = 0;

    topologicalSort(v, edges, edgeCount, ans, &ansSize);

    // Output the topological order
    printf("Topological Sort Order:\n");
    for (int i = 0; i < ansSize; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}

