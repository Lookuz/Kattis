#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, L, U, res, curr;
vector<pair<int, int> > temps;

int cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }

     return a.second < b.second;
}

int main() {
    scanf("%d\n", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d%d\n", &L, &U);

        temps.push_back(make_pair(L, U));
    }

    sort(temps.begin(), temps.end(), cmp);

    res = 0;
    curr = 0;
    for (auto& temp : temps) {
        if (temp.first > curr) {
            curr = temp.second;
            res++;
        }
    }
    
    printf("%d\n", res);
}