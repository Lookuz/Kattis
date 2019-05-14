#include <iostream>
using namespace std;

typedef long long ll;

int fenwick[1000002] = {0};
int N;
int K;

void add(int* fenwick, int index) {
    while (index <= N) {
        fenwick[index] += 1;

        index += index & (-index);
    }
}

void subtract(int* fenwick, int index) {
    while (index <= N) {
        fenwick[index] -= 1;

        index += index & (-index);
    }
}

int sum(int* fenwick, int index) {
    ll sum = fenwick[0];

    while(index > 0) {
        sum += fenwick[index];

        index -= index & (-index);
    }

    return sum;
}

int main() {
    scanf("%d%d\n", &N, &K);
    char c;
    int index, val;
    int l, r;
    for (int i = 0; i < K; i++) {
        cin >> c;
        if (c == 'F') {
            cin >> index;
            val = sum(fenwick, index) - sum(fenwick, index - 1);
            if (val == 0) {
                add(fenwick, index);
            } else {
                subtract(fenwick, index);
            }
        }
        if (c == 'C') {
            cin >> l >> r;
            printf("%d\n", sum(fenwick, r) - sum(fenwick, l-1));
        }
    }
}