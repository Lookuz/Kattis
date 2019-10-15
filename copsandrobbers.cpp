#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_N = 32;
const int MAX_C = 100005;
const int MAX_F = MAX_C * 1000;
const int MAX_V = MAX_N * MAX_N * 2 + 1;
const int MAX_E = MAX_N * MAX_N * 5 * 2 + 1;

char grid[MAX_N][MAX_N + 1]; 
int graph[MAX_E]; // Residual Graph
int nextv[MAX_E];
int capacity[MAX_E]; //
int distances[MAX_V];
int front[MAX_V];
int previous[MAX_V]; // Backtracking AP
int cost[MAX_N]; // Cost of each barricade
int n, m, c, currE, sink, s;
int source = -1;
long long maxFlow;

// Cardinal directions for edges
int directionX[4] = {1, -1, 0, 0};
int directionY[4] = {0, 0, 1, -1};

// Converts an edge in original grid to edge in residual graph
void convert(int forward, int back, int cost) {
    // Forward flow
    graph[currE] = back;
    capacity[currE] = cost; // Initialize forward edge to capacity
    nextv[currE] = front[forward];
    front[forward] = currE++;

    // Back flow
    graph[currE] = forward;
    capacity[currE] = 0; // Initialize back edge to 0
    nextv[currE] = front[back];
    front[back] = currE++;
}

// Convert original grid into flow graph
void constructGraph(int n, int m, int c) {

    memset(front, -1, sizeof(front));
    currE = 0;
    source = -1;
    sink = 2 * m * n;

    // source -> B
    // sink = 2 * m * n (dummy sink)
    // 0 - m * n - 1 contains forward flow edges
    // m * n - 2 * m * n - 1 contains back flow edges
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Initialize start point as source
            if (grid[i][j] == 'B') {
                int x = i * n;
                int y = j;

                source = x + y + n * m;
            } else {
                // Barricade or impossible
                int curr = grid[i][j] - 'a';
                int weight = (grid[i][j] == '.')? MAX_F : cost[curr];
                int forward = (i * n) + j; // Forward flow edge
                int back = (i * n) + j + (n * m); // Back flow edge

                convert(forward, back, weight);
            }

            // Add edges in cardinal direction
            for (int k = 0; k < 4; ++ k) {
                int x = i + directionX[k], y = j + directionY[k];
                int back;

                if (x >= 0 && x < m && y >= 0 && y < n) {
                    back = (x * n) + y;
                } else {
                    // Nodes outside the range are at boundary: connect to sink for flow
                    back = sink;
                }

                convert(i * n + j + n * m, back, MAX_F);
            }
        }
    }
}

// BFS to search for AP
bool getPaths(int source, int sink) {
    queue<int> bfsQueue;
    bool possible = false;

    for (int i = 0; i <= sink; ++ i) {
        distances[i] = MAX_F;
    }

    bfsQueue.push(source);
    distances[source] = 0;

    // BFS
    while (!bfsQueue.empty()) {
        int curr = bfsQueue.front();
        bfsQueue.pop();    
        int prev = front[curr];

        while (prev != -1) {
            int to = graph[prev];
            // Find shorter APs
            if (capacity[prev] > 0 && distances[curr] + 1 < distances[to]) {
                distances[to] = distances[curr] + 1;
                // Augmenting Path found
                if (to == sink) { 
                    possible = true;
                    return possible;
                }

                bfsQueue.push(to);
            }
            prev = nextv[prev];
        }
    }

    return possible;
}

// FF algorithm
void getFlow(int source, int vertex, int sink) {

    // Base case: Backtrack to find AP from sink
    if (vertex == sink) {

        int currFlow = MAX_F;
        int curr = sink;
        int prev;

        while (curr != source) {
            prev = previous[curr];
            currFlow = min(currFlow, capacity[prev]);
            prev ^= 1;

            curr = graph[prev];
        }

        curr = sink;
        while (curr != source) {

            prev = previous[curr];
            capacity[prev] -= currFlow;

            if (capacity[prev] == 0) {
                s = graph[prev ^ 1];
            }
            prev ^= 1;
            capacity[prev] += currFlow;

            curr = graph[prev];
        }

        maxFlow += currFlow;
        return;
    }

    // Recursively find flow down AP
    int prev = front[vertex];
    while(prev != -1) {
        int curr = graph[prev];
        if (capacity[prev] > 0 && distances[curr] == distances[vertex] + 1) {
            previous[curr] = prev;
            getFlow(source, curr, sink);

            if (distances[s] < distances[vertex]) {
                return;
            }

            s = sink;
        }

        prev = nextv[prev];
    }

    distances[vertex] = MAX_F;
}

int main(void) {

    scanf(" %d %d %d", &n, &m, &c);

    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = 0; i < c; ++ i) {
        scanf(" %d", &cost[i]);
    }
    // Construct residual graph
    constructGraph(n, m, c);

    // Run max flow
    maxFlow = 0;
    while (getPaths(source, sink) && maxFlow < MAX_F) {
        getFlow(source, source, sink);
    }

    if (maxFlow < MAX_F) {
        printf("%lld\n", maxFlow);
    } else { // Cost at maximal, impossible
        printf("-1\n");
    }

    return 0;
}
