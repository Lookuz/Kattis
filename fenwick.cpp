#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll fenwick[5000001];
ll N, Q;

void add(ll* fenwick, ll index, ll val) {
    while (index <= N) {
        fenwick[index] += val;

        index += index & (-index);
    }
}

int sum(ll* fenwick, ll index) {
    ll sum = fenwick[0];

    while(index > 0) {
        sum += fenwick[index];

        index -= index & (-index);
    }

    return sum;
}

int main() {
    scanf("%lld%lld\n", &N, &Q);
    char c;
    ll index;
    ll val;

    for (int i = 0; i <= N + 1; i++) {
         fenwick[i] = 0;
    }

    for (int i = 0; i < Q; i++) {
        scanf("%c", &c);

        if (c == '+') {
            scanf("%lld%lld\n", &index, &val);
            add(fenwick, index + 1, val);
        }
        if (c == '?') {
            scanf("%lld\n", &index);
            printf("%lld\n", sum(fenwick, index));
        }
    }
}