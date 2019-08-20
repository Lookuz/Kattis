// This algorithm is a modified version of the algorithm for MVC on trees using DP
// The algorithm considers 3 cases:
// If current node is taken, then children of the current node cannot be taken
// If current node is not taken, then the children node may or may not be taken depending on the minimum cost
// of taking/ not taking the current node yet making sure the children are covered. For this case, it does not ensure the current node is covered
// Current node not taken, but at least one child node is taken. This ensures that the current node is covered by the taken child

#include <cstdio>
#include <cstring>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

typedef long long ll;    

int N, u, sub, root;
ll currCost;
ll cost[100005]; // Cost of bribing member i
ll MAX_VAL = (ll) 1 << 61;
int deg[100005]; // Number of subordinates of member i
ll in[100005]; // Minimum cost of member i and subordinates if member i is bribed
ll out[100005]; // Minimum cost of member i and subordinates if member i is not bribed
ll outS[100005]; // Special case of out; Minimum cost if member i is not bribed but at least one child of member i covered
vector<vector<int>> subordinates(100005); // List of subordinates of member i

// Recursively gets minimum cost of children using top-down DP
void getMinCost(int curr) {

    // Base case: No more subordinates
    if (subordinates[curr].size() == 0) {
        in[curr] = cost[curr];
        out[curr] = 0;
        outS[curr] = cost[curr]; // Take at least the child
        return;
    }

    // Bribe current member
    in[curr] = cost[curr];
    for(int sub: subordinates[curr]) { // Get minimum cost of not bribing subordinates
        if (out[sub] == -1) {
            getMinCost(sub);
        }
        in[curr] += out[sub];
    }

    // Don't bribe current member
    out[curr] = 0;
    for(int sub: subordinates[curr]) { // Get minimum cost of bribing subordinates
        if (in[sub] == -1 || outS[sub] == -1) {
            getMinCost(sub);
        }
        out[curr] += min(in[sub], outS[sub]);
    }

    outS[curr] = MAX_VAL;
    for(int sub : subordinates[curr]) { // Get minimum cost of not bribing current but at least one subordinate is bribed
        currCost = out[curr] - min(in[sub], outS[sub]);
        currCost += in[sub]; // Pick current child; Ensure that at least one child is covered
        outS[curr] = min(currCost, outS[curr]);
    }
}

int main(void) {

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%lld %d", &cost[i], &u);
        for (int j = 0; j < u; j++) {
            scanf("%d", &sub);
            deg[sub]++;
            subordinates[i].push_back(sub);
        }
    }

    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) {
            root = i;
        }
    }

    // Initialize to all -1 default values
    memset(in, -1, sizeof(in));
    memset(out, -1, sizeof(out));
    memset(outS, -1, sizeof(outS));

    getMinCost(root);

    printf("%lld", min(in[root], outS[root]));

    return 0;
}