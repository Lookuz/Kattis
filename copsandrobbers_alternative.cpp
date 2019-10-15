#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 32;
const int MAX_C = 100005;
const long long MAX_F = 1L << 40;

int n, m, c;

char grid[MAX_N][MAX_N];
long long cost[MAX_N];
long long graph[2 * MAX_N * MAX_N + 2][2 * MAX_N * MAX_N + 2]; // Residual graph

int parent[2 * MAX_N * MAX_N + 5];
long long dp[2 * MAX_N * MAX_N + 5];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

long long getFlow(int source, int sink) {
    long long res = 0;

    while (res < MAX_F) {
        for (int i = 0; i < (2 * m * n + 2); i++) {
            parent[i] = -1;
            dp[i] = 0;
        }

        parent[source] = -2;
        dp[source] = MAX_F;
        queue<int> q;
        q.push(source);

        while (!q.empty() && dp[sink] == 0) {
            int curr = q.front();
            q.pop();

            for (int i = 0; i < (2 * m * n + 2); i++) {
                if (parent[i] == -1 && graph[curr][i] > 0) {
                    dp[i] = min(dp[curr], graph[curr][i]);
                    parent[i] = curr;
                    q.push(i);
                }
            }
        }

        // No more AP
        if (dp[sink] == 0) {
            break;
        }

        res += dp[sink];
        int curr = sink;
        while (curr != source) {
            graph[parent[curr]][curr] -= dp[sink]; // Reduce forward capacity
            graph[curr][parent[curr]] += dp[sink]; // Increase back flow
            curr = parent[curr];
        }
    }

    return res;
}

int main(void) {

    scanf(" %d %d %d", &n, &m, &c);

    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = 0; i < c; ++ i) {
        scanf(" %lld", &cost[i]);
    }

    memset(graph, 0, sizeof(graph));

    // Flow graph construction
    // Source: 2 * n * m
    // Sink: 2 * n * m + 1
    // Forward: 0 - n * m - 1 are vertices connected to source
    // Back: n * m - 2 * n * m -1 are vertices connected to sink
    // forward-back have the capacity as the cost of that vertex
    int source = 2 * m * n;
    int sink = source + 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int forward = (i * n) + j;
            int back = (i * n) + j + (m * n);
            // Connect source to starting point
            if (grid[i][j] == 'B') {
                graph[source][forward] = MAX_F;
            } 
            
            if (grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                graph[forward][back] = cost[grid[i][j]-'a'];
            } else {
                graph[forward][back] = MAX_F;
            }

            // Boundary, connect to sink
            if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                graph[back][sink] = MAX_F;
            }

            // Add cardinal directions
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if (x >= 0 && x < m && y >= 0 && y < n) {
                    int to = (x * n) + y;
                    graph[back][to] = MAX_F;
                }
            }
        }
    }

    // for (int i = 0; i < 2 * m * n + 2; i++) {
    //     for (int j = 0; j < 2 * m * n + 2; j++) {
    //         printf("%lld ", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    long long res = getFlow(source, sink);

    if (res >= MAX_F) {
        res = -1;
    }

    printf("%lld\n", res);

    return 0;
}