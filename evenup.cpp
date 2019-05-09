#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#include <iostream>
#include <stack>
using namespace std;

stack<int> s;

inline int getint(){
	char c;
	while ((c = getchar_unlocked()) <= ' ');
	int v = 0;
	do { v = (v << 3) + (v << 1) + (c ^ '0'); }
	while ((c = getchar_unlocked()) >= '0' && c <= '9');
	return v;
}

int main() {
    int N = getint();
    int curr;

    for (int i = 0; i < N; i++) {
        curr = getint();
        if (!s.empty() && ((s.top() + curr) % 2 == 0)) {
            s.pop();
        } else {
            s.push(curr);
        }
    }

    printf("%lu", s.size());
}