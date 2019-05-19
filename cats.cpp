#include <bits/stdc++.h>
using namespace std;

int cats[2002];
int parent[2002];
int T, M, C, res;
int from, to, weight;

int find(int index) {
    
    while (index != parent[index]) {
        parent[index] = parent[parent[index]];
        index = parent[index];
    }
    
    return parent[index];
}

void _union(int index1, int index2) {
    int parent1 = find(index1);
    int parent2 = find(index2);

    if (parent1 != parent2) {
        parent[parent1] = parent2;
    }
}

int main() {
    scanf("%d\n", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &M, &C);
        
        vector<pair<int, pair<int, int> > > edges;
        int numEdge = C*(C - 1)/2; 
        for (int j = 0; j < numEdge; j++) {
            scanf("%d%d%d\n", &from, &to, &weight);
            edges.push_back(make_pair(weight, make_pair(from, to)));
        }

        sort(edges.begin(), edges.end());

        for (int j = 0; j < C; j++) {
            parent[j] = j;
        }

        res = 0;
        for (auto& edge : edges) {
            from = edge.second.first;
            to = edge.second.second;
            if (find(from) != find(to)) {
                _union(from, to);
                res += edge.first;
            }
        }

        if (res + C <= M) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}