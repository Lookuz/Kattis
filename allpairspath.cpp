#include <iostream>
#include <climits>
using namespace std;

typedef long long ll;

int n, m, q;
int u, v, w;
ll distances[152][152];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while (true) {

        cin >> n >> m >> q;

        if (n == 0 && m == 0 && q == 0) {
            break;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    distances[i][j] = 0;
                } else {
                    distances[i][j] = LONG_MAX;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;

            if (w < distances[u][v]) {
                distances[u][v] = w;
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (distances[i][k] < LONG_MAX && distances[k][j] < LONG_MAX
                    && distances[i][k] + distances[k][j] < distances[i][j]) {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (distances[i][k] != LONG_MAX && distances[k][j] != LONG_MAX && distances[k][k] < 0) {
                        distances[i][j] = LONG_MIN;
                    }
                }
            }
        }

        for (int i = 0; i < q; i++) {
            cin >> u >> v;

            if (distances[u][v] == LONG_MAX) {
                cout << "Impossible" << endl;
            } else if (distances[u][v] == LONG_MIN) {
                cout << "-Infinity" << endl;
            } else {
                cout << distances[u][v] << endl;
            } 
        }
        cout << endl;

    }

    return 0;
}