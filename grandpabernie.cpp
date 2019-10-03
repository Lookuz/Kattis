#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n, q, k, year;
string location;
unordered_map<string, vector<int>> map; 
unordered_set<string> set;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> location >> year;

        if (map.find(location) == map.end()) {
            set.insert(location);
            map.insert({location, vector<int>()});
        } 

        map[location].push_back(year);
    }

    for (auto entry : set) {
        sort(map[entry].begin(), map[entry].end());
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> location >> k;

        printf("%d\n", map[location][k-1]);
    }

    return 0;
}