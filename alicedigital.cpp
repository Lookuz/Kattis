#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

int n, m, datasets, curr, best;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> datasets;

    while(datasets-- > 0) {
        cin >> n >> m;

        vector<int> arr(n);
        vector<int> indices;

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] == m) {
                indices.push_back(i);
            }
        }

        best = 0;
        for (auto i : indices) { 
            curr = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] <= m) {
                    break;
                } else {
                    curr += arr[j];
                }
            }

            for (int j = i + 1; j < n; j++) {
                if (arr[j] <= m) {
                    break;
                } else {
                    curr += arr[j];
                } 
            }

            best = max(best, curr + m);
        }

        cout << best << endl;
    }

    return 0;
}