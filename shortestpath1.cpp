#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

inline int getint(){
	char c;
	while ((c = getchar_unlocked()) <= ' ');
	int v = 0;
	do { v = (v << 3) + (v << 1) + (c ^ '0'); }
	while ((c = getchar_unlocked()) >= '0' && c <= '9');
	return v;
}

int getShortestPath(int s, int d, int v, vector<vector<pair<int, int>>>& adjList) {
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
	vector<bool> visited(v, false);
	vector<int> distances(v, numeric_limits<int>::max());
	distances[s] = 0;
	pq.push(make_pair(0, s));

	while (!pq.empty()) {
		int curr = pq.top().second;
		pq.pop();

		if (visited[curr]) {
			continue;
		}

		for (pair<int, int> p : adjList[curr]) {
			if (distances[p.second] > distances[curr] + p.first) {
				distances[p.second] = distances[curr] + p.first;
				pq.push(make_pair(distances[p.second], p.second));
			}
		}
		visited[curr] = true;
	}

	return distances[d];

}

int main(){
    int n, m, q, s, d;
    int to, from, weight, result;

    n = getint();
    m = getint();
    q = getint();
    s = getint();

    while (true) {
        
        vector< vector< pair<int, int> > > adjList(n);
        for (int i = 0; i < m; i++) { 
            from = getint();
            to = getint();
            weight = getint();
            adjList[from].push_back(make_pair(weight, to));
	    }

        for (int i = 0; i < q; i++) {
            d = getint();
            result = getShortestPath(s, d, n, adjList);
            if (result == numeric_limits<int>::max()) {
                printf("Impossible\n");
            } else {
                printf("%d\n", result);
            }
        }

        n = getint();
        m = getint();
        q = getint();
        s = getint();

        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        printf("\n");
    }

    return 0;
}