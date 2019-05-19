#include <iostream>
#include <set>
#include <cmath>
using namespace std;

typedef long long ll;

ll N, m, total, cost;
set<ll> bst;
ll dist[300002] = {0};

int main() {
    scanf("%lld\n", &N);

    total = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld\n", &m);
        // printf("Number: %d\n", m);

        bst.insert(m);
        cost = 0;
        auto curr = bst.find(m);
        if (i != 0) {
            if (curr != bst.begin()) {
                auto prev = curr;
                prev--;
                cost = max(dist[*(prev)] + 1, cost);
            }
            if (curr != bst.end()) {
                auto next = curr;
                next++;
                if (next != bst.end()) {
                    cost = max(dist[*(next)] + 1, cost);
                }
            }
        }

        total += cost;
        dist[m] = cost;

        printf("%lld\n", total);
    }

    return 0;
}