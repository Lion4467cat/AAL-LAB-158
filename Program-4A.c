#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent a graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Structure to represent a MinHeap node
struct MinHeapNode {
    int v;      // Vertex number
    int key;    // Key value used for min-heap property
};

// Structure to represent a MinHeap
struct MinHeap {
    int capacity; // Maximum size of min heap
    int size;     // Current size of min heap
    struct MinHeapNode** array; // Array of minheap nodes
    int* pos;     // Needed for decreaseKey() to get the index of a vertex in heap
};

// Function to create a new MinHeapNode
struct MinHeapNode* newMinHeapNode(int v, int key) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

// Function to create a MinHeap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    return minHeap;
}

// Function to swap two MinHeap nodes
void swapMinHeapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify a subtree rooted with index i
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        // Update position in pos array
        minHeap->pos[minHeap->array[smallest]->v] = idx;
        minHeap->pos[minHeap->array[idx]->v] = smallest;

        // Swap nodes
        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Function to check if the min heap is empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Function to extract the minimum value node from the min heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace root with the last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of the last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify the root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease the key value of a given vertex v
void decreaseKey(struct MinHeap* minHeap, int v, int newKey) {
    int i = minHeap->pos[v];

    minHeap->array[i]->key = newKey;

    while (i > 0 && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // Move to the parent index
        i = (i - 1) / 2;
    }
}

// Function to check if a given vertex 'v' is in MinHeap
bool isInMinHeap(struct MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

// Function to implement Prim's algorithm
void primMST(struct Graph* graph) {
    int V = graph->V; // Number of vertices
    int parent[V];    // Array to store constructed MST
    int key[V];       // Key values used to pick minimum weight edge in cut
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize all keys as INFINITE
    for (int v = 0; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // Make key of first vertex as 0 so that it is extracted first
    key[0] = 0;
    minHeap->array[0]->key = 0;
    minHeap->size = V;
    minHeap->pos[0] = 0;

    // While min heap is not empty
    while (!isEmpty(minHeap)) {
        // Extract the vertex with minimum key value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the extracted vertex)
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;

            // If v is in min heap and weight of (u, v) is smaller than key of v
            if (isInMinHeap(minHeap, v) && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the constructed MST
    printf("Edges of MST are:\n");
    int mst_weight = 0;
    for (int i = 1; i < V; ++i) {
        printf("%d - %d    Weight: %d\n", parent[i], i, key[i]);
        mst_weight += key[i];
    }
    printf("Total weight of MST: %d\n", mst_weight);

    // Free allocated memory for min heap
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

// Example Usage:
int main() {
    // Create a graph with 6 vertices
    int V = 6;
    struct Graph* graph = createGraph(V);

    // Add edges to the graph (representing an undirected weighted graph)
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 6);

    printf("Adjacency List of the Graph:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: ", i);
        struct AdjListNode* current = graph->array[i].head;
        while (current) {
            printf("(%d, %d) -> ", current->dest, current->weight);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");

    // Run Prim's algorithm to find the Minimum Spanning Tree
    primMST(graph);

    // Free graph memory (optional, but good practice)
    for (int i = 0; i < V; ++i) {
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
