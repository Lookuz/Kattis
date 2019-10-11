#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_R = 1005;

int P, R, L, from, to, maxFlow, maxEdge, currFlow, source, sink;
int edge[MAX_R][MAX_R];
int capacity[MAX_R][MAX_R];
int flow[MAX_R][MAX_R];
int parent[MAX_R];
int current[MAX_R];
bool hasAP;

bool getPaths(int source, int sink, int capacity[][MAX_R], int edge[][MAX_R], int parent[], 
    int current[], int flow[][MAX_R], int size) {
    vector<bool> visited(size + 1, false);
    vector<int> distance(size + 1, MAX_R);

    distance[0] = 0;
    int next, dist, curr;
    curr = source;

    // While there are still augmenting paths
    while(curr != size) {
        next = size;
        visited[curr] = true;
        // BFS
        for (int i = 0; i < size; i++) {
            if (visited[i]) {
                continue;
            }
            // Forward flow
            if (flow[curr][i] < capacity[curr][i]) {
                dist = distance[curr] + current[curr] - current[i] + edge[curr][i];
                if (dist < distance[i]) {
                    distance[i] = dist;
                    parent[i] = curr;
                }
            }
            // Back flow
            if (flow[i][curr] > 0) {
                dist = distance[curr] + current[curr] - current[i] - edge[i][curr];
                if (dist < distance[i]) {
                    distance[i] = dist;
                    parent[i] = curr;
                }
            }
            if (distance[i] < distance[next]) {
                next = i;
            }
        }
        curr = next;
    }

    for (int i = 0; i < size; i++) {
        current[i] = min(current[i] + distance[i], MAX_R);
    }

    return visited[sink];
}

int main(void) {
    
    scanf(" %d %d %d", &P, &R, &L);

    memset(edge, 0, sizeof edge);
    memset(capacity, 0, sizeof capacity);
    for (int i = 0; i < L; i++) {
        scanf(" %d %d", &from, &to);
        // Endpoint conversion, 0 is dummy sink and 1 left bank, R + 2 is right bank and R + 3 is dummy sink
        if (from == -2) {
            from = 1;
        } else if (from == -1) {
            from = R + 2;
        } else {
            from = from +2;
        }

        if (to == -2) {
            to = 1;
        } else if (to == -1) {
            to = R + 2;
        } else {
            to = to +2;
        }
        capacity[from][to] = 1;
        capacity[to][from] = 1;
        edge[from][to] = 1;
        edge[to][from] = 1;
    }
    // Dummy source and sink to bottleneck number of people
    capacity[0][1] = P;
    capacity[R+2][R+3] = P;
    source = 0;
    sink = R + 3;

    memset(parent, 0, sizeof parent);
    memset(current, 0, sizeof current);
    memset(flow, 0, sizeof flow);
    maxFlow = maxEdge = 0;
    hasAP = getPaths(source, sink, capacity, edge, parent, current, flow, R+4);

    while(hasAP) {
        currFlow = MAX_R;
        // Backtrack to find AP
        for (int i = sink; i != source; i = parent[i]) {
            if (flow[i][parent[i]] > 0) {
                currFlow = min(currFlow, flow[i][parent[i]]); // Back flow
            } else {
                currFlow = min(currFlow, capacity[parent[i]][i] - flow[parent[i]][i]); // Forward flow
            }
        }
        for (int i = sink; i != source; i = parent[i]) {
            // Push flow back
            if (flow[i][parent[i]] > 0) {
                flow[i][parent[i]] -= currFlow;
                maxEdge -= (edge[i][parent[i]] > 0)? currFlow : 0;
            } else { // Increase forward flow
                flow[parent[i]][i] += currFlow;
                maxEdge += (edge[i][parent[i]] > 0)? currFlow : 0;
            }
        }
        maxFlow += currFlow;
        hasAP = getPaths(source, sink, capacity, edge, parent, current, flow, R+4);
    }

    if (maxFlow < P) {
        printf("%d people left behind\n", P - maxFlow);
    } else {
        printf("%d\n", maxEdge);
    }

    return 0;
}