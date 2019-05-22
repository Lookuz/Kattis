#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll l, d, n, bird, res, curr;
vector<ll> birds;

int main() {
    // scanf("%lld%lld%lld\n", &l, &d, &n);
    cin >> l >> d >> n;

    for (int i = 0; i < n; i++) {
        cin >> bird;
        birds.push_back(bird);
    }

    sort(birds.begin(), birds.end());

    res = 0;
    curr = 6;

    if (n == 0) {
        res += (l - 12)/d + 1;
    } else {
        for (int i = 0; i < n; i++) {
            while (birds[i] - curr >= d) {
                curr += d;
                res++;
            }
            curr = birds[i] + d;
        }

        while (curr <= l - 6) {
            res++;
            curr += d;
        }
    }

    printf("%lld\n", res);

    return 0;
}