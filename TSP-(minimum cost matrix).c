#include <stdio.h>
#include <limits.h>

#define MAX 10

int tsp(int graph[MAX][MAX], int visited[MAX], int pos, int n, int count, int cost, int start) {
    if (count == n && graph[pos][start]) {
        return cost + graph[pos][start];
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[pos][i]) {
            visited[i] = 1;
            int temp = tsp(graph, visited, i, n, count + 1, cost + graph[pos][i], start);
            ans = (temp < ans) ? temp : ans;
            visited[i] = 0;
        }
    }
    return ans;
}

int main() {
    int n;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    int graph[MAX][MAX];
    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int visited[MAX] = {0};
    visited[0] = 1; // Start from city 0

    int minCost = tsp(graph, visited, 0, n, 1, 0, 0);
    printf("Minimum cost of visiting all cities: %d\n", minCost);

    return 0;
}
