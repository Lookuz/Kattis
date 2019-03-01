#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main() {
    int c, n;
    double cDouble;

    while (cin >> cDouble && cin >> n) {
        c = floor(cDouble);

        vector< vector<int> > temp;
        temp.resize(n + 1, vector<int>(c + 1, 0));

        vector< pair<int, int> > weights;
        weights.push_back({0, 0});
        pair<int, int> p;
        for(int i = 0; i < n; i++) {
            cin >> p.first >> p.second;
            weights.push_back(p);
        }

        // knapsack
        for (int i = 1; i <= n; i ++){
            for (int j = 1; j <= c; j++) {
                if (weights[i].second <= j) {
                    temp[i][j] = max(weights[i].first + temp[i-1][j - weights[i].second], temp[i-1][j]);
                } else {
                    temp[i][j] = temp[i-1][j];
                }
            }
        }

        vector<int> indices;
        int j = c;
        for (int i = n; i > 0; i--) {
            if (temp[i][j] != temp[i - 1][j]) {
                j -= weights[i].second;
                indices.push_back(i - 1);
            }
        }
        cout << indices.size() << endl;
        for (auto i : indices) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}