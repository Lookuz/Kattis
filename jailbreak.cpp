// Algorithm that uses BFS and Steiner Tree to find the steiner vertex that has minimum sum of doors 
// to each prisoner and the source. 
// Original floor plan is padded with 0 sentinels to allow traversal around the floor and start from any point
// Along the side of the floor plan. To obtain the mininum number of doors from each source and prisoner, 
// BFS is used while maintaining a DP table of minimum number of doors from given source to that point.
// Every possible point in the floor is then checked for possible steiner vertex that gives the minimum sum of doors.
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 105;

char floor[MAX][MAX]; // Floor plan
int bfs0[MAX][MAX], bfs1[MAX][MAX], bfs2[MAX][MAX]; // DP table for minimum number of doors traversed from each source
vector<pair<int, int>> sources; // Coordinates for prisoners
int coordx[4] = {-1, 1, 0, 0}; // BFS directions 
int coordy[4] = {0, 0, -1, 1};
int n, h, w, currMin, curr, nextX, nextY, result;
pair<int, int> p, source;
queue<pair<int, int>> nextq[2] = {
    queue<pair<int, int>>(),
    queue<pair<int, int>>()
}; // Queue for BFS nodes


// Performs BFS to find the minimum number of doors from source x, y to every other reachable point
// Maintains two queues for BFS; Current queue represents the nodes that can be reached in currMin number of doors
// When no more nodes that can be reached in currMin doors is available(queue is empty), other queue is toggled
// and currMin is incremented to represent the BFS to these nodes from opening 1 more door. 
// Only nodes where the dp table value is unupdate(-1) is updated. If dp table already has value >= 0,
// Current node can be reached in less or equal number of doors than the currMin
void bfs(int x, int y, int h, int w, int dp[MAX][MAX]) {
    curr = 0;
    currMin = 0;
    memset(dp, -1, MAX * MAX * sizeof(int)); // Set all values to unupdated

    nextq[curr].push(make_pair(x, y)); // Push source into BFS queue
    dp[x][y] = 0;

    while (!nextq[0].empty() || !nextq[1].empty()) {
        if (nextq[curr].empty()) { // Alternate queue if current empty
            currMin++;
            curr ^= 1;
        }

        p = nextq[curr].front();
        nextq[curr].pop();
        for (int i = 0; i < 4; i++) { // Go through each search direction
            nextX = p.first + coordx[i];
            nextY = p.second + coordy[i];
            if (nextX >= 0 && nextX < h && nextY >= 0 && nextY < w && floor[nextX][nextY] != '*' && dp[nextX][nextY] == -1) { // If not yet traversed, update min number of doors to pass through to this point from source
                dp[nextX][nextY] = currMin;
                if (floor[nextX][nextY] == '#') { // If door, add to other queue
                    nextq[curr^1].push(make_pair(nextX, nextY));
                } else {
                    nextq[curr].push(make_pair(nextX, nextY));
                }
            }
        }

    }
}

int main(void) {

    scanf("%d", &n);

    while (n > 0) {

        scanf("%d %d\n", &h, &w);
        sources.push_back(make_pair(0, 0)); // Add top left starting point to sources

        for (int i = 0; i <= h+1; i++) {
            if (i == 0 || i == h+1) { // Pad sentinels around the original map
                for (int j = 0; j <= w+1; j++) {
                    floor[i][j] = '.';
                }
            } else {
                scanf("%s\n", floor[i] + 1);
                floor[i][0] = floor[i][w+1] = '.'; // Pad sentinels on the edges
            }
        }

        for (int i = 0; i <= h+1; i++) {
            for (int j = 0; j <= w+1; j++) {
                if (floor[i][j] == '$') {
                    sources.push_back(make_pair(i, j));
                }
            }
        }

        // Run minimum path from source and each prisoner
        bfs(sources[0].first, sources[0].second, h + 2, w + 2, bfs0);
        bfs(sources[1].first, sources[1].second, h + 2, w + 2, bfs1);
        bfs(sources[2].first, sources[2].second, h + 2, w + 2, bfs2);

        // Find minimum steiner vertex
        currMin = bfs0[0][0] + bfs1[0][0] + bfs2[0][0];
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (bfs0[i][j] >= 0) { // If node is reachable
                    curr = bfs0[i][j] + bfs1[i][j] + bfs2[i][j];
                    if (floor[i][j] == '#') { // if steiner vertex is a door, add back the door count
                        curr++;
                    }
                    currMin = min(currMin, curr);
                }
            }
        }
        printf("%d\n", currMin);
        
        n--;
        sources.clear();
    }

    return 0;
}