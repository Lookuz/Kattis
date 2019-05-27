#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[31002];
int items[101];
int orders[31002];
int n, m, s, curr;
int M_MAX = 30001;

int main() {
    fill_n(dp, 31002, -2);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> items[i];
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> orders[i];
    }

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < M_MAX; j++) {
            if (dp[j] >= 0) {
                if (dp[j + items[i]] == -2) {
                    dp[j + items[i]] = i;
                } else {
                    dp[j + items[i]]= -1;
                }
            }
            if (dp[j] == -1) {
                dp[j + items[i]] = -1;
            }
        }    
    }

    for (int i = 0; i < m; i++) {
        if (dp[orders[i]] == -2) {
            printf("Impossible\n");
            continue;
        } else if (dp[orders[i]] == -1) {
            printf("Ambiguous\n");
            continue;
        }
        
        vector<int> ans;
        curr = orders[i];
        while (curr > 0) {
            ans.push_back(dp[curr] + 1);
            curr -= items[dp[curr]];  
        }

        sort(ans.begin(), ans.end());
        for (auto& j : ans) {
            printf("%d ", j);
        }
        printf("\n");
    }
}