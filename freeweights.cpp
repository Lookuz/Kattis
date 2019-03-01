#include <math.h>
#include <limits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

bool check(vector<ll>& row, ll constraint) {
    int currHigh = -1;
    for (auto& item : row) {
        if (item <= constraint) {
            continue;
        } else if(currHigh == -1) {
            currHigh = item;
        } else {
            if (item != currHigh) {
                return false;
            }

            currHigh = -1;
        }
    }

    return currHigh == -1;
}

int main() {
    int n;
    cin >> n;
    vector<ll> row1(n), row2(n);

    for (auto& item : row1) {
        cin >> item;
    }

    for (auto& item : row2) {
        cin >> item;
    }

    ll low = 0;
    ll high = 1000000000;
    ll mid;

    while(low < high) {
        mid = (low + high)/2;
        if (check(row1, mid) && check(row2, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << low << endl;
}