#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_H = 52;
const int MAX_W = 12;

int cases, h, w, curr, res;

char grid[MAX_H][MAX_W]; // Original grid
int vertex[MAX_H][MAX_W]; // Labelled antenna points 
int graph[MAX_H * MAX_W][MAX_H * MAX_W]; // Edge graph containing (u, v)
int matched[MAX_H * MAX_W]; // Currently matched points
bool visited[MAX_H * MAX_W];

// Attempt to match current point with unmatched point
bool canMatch(int current, int total) {

    // Attempt to match all neighbours
    for (int i = 1; i <= total; i++) {
        // Neighbouring point
        if (graph[current][i] > 0 && !visited[i]) {
            visited[i] = true;

            // Unmatched point
            if (matched[i] == -1) {
                matched[i] = current; // Match to this
                return true;
            } 
            if (canMatch(matched[i], total)) { // Attempt to rematch current pairing
                matched[i] = current;
                return true;
            }
        }
    }

    return false;
}

int main(void) {

    scanf(" %d", &cases);

    while (cases--) {

        scanf(" %d %d", &h, &w);

        curr = 1;
        memset(vertex, 0, sizeof(vertex));
        memset(graph, 0, sizeof(graph));
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                scanf(" %c", &grid[i][j]);
                if (grid[i][j] == '*') {
                    vertex[i][j] = curr++;
                }
            }
        }

        // Creating matching edges
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (grid[i][j] != '*') {
                    continue;
                }

                if (i-1 >= 1 && grid[i-1][j] == '*') {
                    graph[vertex[i][j]][vertex[i-1][j]] = 1;
                }
                if (i+1 <= h && grid[i+1][j] == '*') {
                    graph[vertex[i][j]][vertex[i+1][j]] = 1;
                }
                if (j-1 >= 1 && grid[i][j-1] == '*') {
                    graph[vertex[i][j]][vertex[i][j-1]] = 1;
                }
                if (j+1 <= w && grid[i][j+1] == '*') {
                    graph[vertex[i][j]][vertex[i][j+1]] = 1;
                }
            }
        } 

        res = 0;
        int totalPoints = curr - 1;
        // Initialize all not matched
        for (int i = 0; i <= totalPoints; i++) {
            matched[i] = -1;
        }

        // Match points
        for (int i = 1; i <= totalPoints; i++) {
            memset(visited, 0, sizeof(visited));
            if (canMatch(i, totalPoints)) {
                res++;
            }
        }

        res = totalPoints - (res/2);

        printf("%d\n", res);
    }

    return 0;
}