#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef long long ll;

int n, k;
int start, finish, res;
vector<pair<int, int> > events;
multiset<int> endtimes;

bool compare(const pair<int, int>& i, const pair<int, int>& j) {
    if (i.first == j.first) {
        return i.second < j.second;
    }
    return i.first < j.first;
}

int main() {
    scanf("%d%d\n", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d%d\n", &start, &finish);
        events.push_back(make_pair(finish, start));
    }

    sort(events.begin(), events.end(), compare);

    for (int i = 0; i < k; ++i) {
        endtimes.insert(0);
    }

    res = 0;
    for (auto& event : events) {
        auto pos = endtimes.upper_bound(event.second);
        if (pos != endtimes.begin()) {
            pos = prev(pos);
            endtimes.erase(pos);
            endtimes.insert(event.first + 1);
            ++res;
        }
    }

    printf("%d\n", res);

    return 0;
}