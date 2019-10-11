#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, num, to;

bool canMatch(vector<bool>& visited, vector<int>& matching, vector<vector<int>>& adjList, int lesson) {
    // Not yet matched, can assign
    if (matching[lesson] == -1) {
        return true;
    } 

    visited[lesson] = true;
    // Try to re-match current match
    int current = matching[lesson];
    bool possible = false;
    for (int other : adjList[current]) {
        // Rematch to unmatched class in currently matched student's schedule
        if (!visited[other] && canMatch(visited, matching, adjList, other)) {
            matching[other] = current;
            possible = true;
            break;
        }
    }

    // Unable to match any class
    return possible;
}

int main(void) {

    scanf(" %d %d", &N, &M);
    vector<vector<int>> adjList(N);

    for (int i = 0; i < N; i++) {
        scanf(" %d", &num);
        for (int j = 0; j < num; j++) {
            scanf(" %d", &to);
            adjList[i].push_back(to - 1);
        }
    }

    vector<int> matching(M, -1);
    vector<bool> visited(M, false);

    // Match each student
    for (int i = 0; i < N; i++) {
        // Find matching class that is not occupied
        visited.assign(M, false);
        for (int lesson : adjList[i]) {
            if (canMatch(visited, matching, adjList, lesson)) { // Student can match
                matching[lesson] = i;
                break;
            }
        }
    }

    num = 0;
    // Count classes that were matched
    for (int i = 0; i < M; i++) {
        if (matching[i] != -1) { 
            num++;
        }
    }

    printf("%d\n", num);

    return 0;
}