#include <bits/stdc++.h>
using namespace std;

int N, M, up, down, curr;
char direction;
int arr[42];
int dp[42][1003];
int dir[42][1003];

int main() {
    cin >> N;

    while(N-- > 0) {
        cin >> M;

        for(int i = 0; i < M; i++) {
            cin >> arr[i];
        }

        memset(dp, -1, sizeof(dp));
        dp[M][0] = 0;
         for (int i = M - 1; i >= 0; i--) {
            for (int j = 0; j < 1003; j++) {
                if (arr[i] + j < 1003 && dp[i + 1][arr[i] + j] != -1) {
                    dp[i][j] = max(j, dp[i + 1][arr[i] + j]);
                    dir[i][j] = 1;
                }

                if (j - arr[i] >= 0 && dp[i + 1][j - arr[i]] != -1 && (dp[i][j] == -1 || dp[i][j] > dp[i + 1][j - arr[i]])) {
                    dp[i][j] = max(j, dp[i + 1][j - arr[i]]);
                    dir[i][j] = -1;
                }
            }
        }

        if (dp[0][0] == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            curr = 0;
            for (int i = 0; i < M; i++) {
                direction = dir[i][curr] == 1 ? 'U' : 'D';
                cout << direction;
                curr += dir[i][curr] * arr[i];
            }
            cout << endl;
        }
    }

    return 0;
}