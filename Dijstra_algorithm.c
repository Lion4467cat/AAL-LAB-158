#include <stdio.h>
#include <limits.h>

#define V 9  // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to implement Dijkstra's algorithm and find the shortest path tree (SPT)
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // dist[i] holds the shortest distance from src to i
    int sptSet[V];  // sptSet[i] will be 1 if vertex i is included in the shortest path tree
    int parent[V];  // To store the parent of each vertex in the SPT

    // Initialize all distances as INFINITE, sptSet[] as 0 (false), and parents as -1
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] if and only if the edge u-v exists, v is not in sptSet,
            // and the new distance is smaller than the current distance
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;  // Set the parent of v to u
            }
        }
    }

    // Print the constructed distance array
    printf("Vertex\t Distance from Source (%d)\t Parent\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\t\t %d\n", i, dist[i], parent[i]);
    }

    // Print the Shortest Path Tree (SPT)
    printf("\nShortest Path Tree (SPT):\n");
    for (int i = 0; i < V; i++) {
        if (i != src && parent[i] != -1) {
            printf("Edge: %d -> %d with weight %d\n", parent[i], i, graph[parent[i]][i]);
        }
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 0, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 0},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 0, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 0, 0, 0, 0, 6, 7, 0}
    };

    // Run Dijkstra's algorithm starting from vertex 0
    dijkstra(graph, 0);

    return 0;
}
