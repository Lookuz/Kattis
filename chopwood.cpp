#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;
queue<int> q;
map<int, int> out;
int N;
int curr;

inline int getint(){
	char c;
	while ((c = getchar_unlocked()) <= ' ');
	int v = 0;
	do { v = (v << 3) + (v << 1) + (c ^ '0'); }
	while ((c = getchar_unlocked()) >= '0' && c <= '9');
	return v;
}

int main() {
    N = getint();

    for (int i = 0; i < N; i++) {
        curr = getint();
        if (i == N - 1 && curr != N + 1) {
            printf("Error");
            return 0;
        }
        q.push(curr);
        if (out.find(curr) == out.end()) {
            out[curr] = 1;
        } else {
            out[curr]++;
        }
    }

    for (int i = 1; i <= N + 1; i++) {
        if (out.find(i) == out.end()) {
            pq.push(i);
        }
    }

    if (pq.empty()) {
        printf("Error");
        return 0;
    }

    while(!q.empty()) {
        curr = q.front();
        q.pop();
        
        printf("%d\n", pq.top());
        pq.pop();
        out[curr]--;
        if (out[curr] == 0) {
            out.erase(curr);
            pq.push(curr);
        }
    }
}