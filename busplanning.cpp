#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int MAX_N = 20;
int n, k, c, from, to, curr, combinations, mismatches;
int dislike[MAX_N] = {0}; // Stores the mismatches in bitwise form
int combinationCounts[1<<MAX_N];
bool validCombination[1<<MAX_N];
map<string, int> nameIndex;
map<int, string> names;
string name, first, second;

void solve(map<int, string> names, int dislike[], int n, int c) {
    int maxCombinations = 1 << n; // Max number of combinations 
    memset(combinationCounts, 0x01, sizeof(combinationCounts));

    // Get valid combinations
    for (int i = 1; i < maxCombinations; i++) {
        combinations = 0; // Current combination is bitwise form
        mismatches = 0; // mismatches for kids in combinations in bitwise form
        for (int j = 0; j < n; j++) {
            if (i & (1<<j)) { // If kid in current combination
                combinations |= (1<<j); // Add to combination
                mismatches |= (dislike[j]); // Add kid's mismatches
            }
        }
        // Check if number of kids < c and none of kids are mismatched
        if (__builtin_popcount(i) <= c && ((combinations & mismatches) == 0)) {
            validCombination[i] = true;
        } else {
            validCombination[i] = false;
        }
    }

    // Count combinations
    combinationCounts[0] = 0;
    for (int i = 1; i < maxCombinations; i++) {
        int best = MAX_N;
        for (int j = i; j > 0; j = (j - 1) & i) { 
            // Invalid pairing
            if (validCombination[j]) {
                curr = i ^ j; // Current kid
                best = min(best, combinationCounts[curr] + 1);
            }
        }
        combinationCounts[i] = best;
    }
 
    curr = maxCombinations - 1;
    int result = combinationCounts[curr];
    cout << result << endl;
    for (int i = result - 1; i >= 0; i--) {
        for (int j = curr; j > 0; j = (j - 1) & curr) {
            if (validCombination[j] && (combinationCounts[curr ^ j] == i)) {
                curr ^= j;
                int count = __builtin_popcount(j);
                for (int k = 0; k < n; k++) {
                    if (j & (1<<k)) {
                        cout << names[k];
                        if ((--count) != 0) {
                            cout << " ";
                        } 
                    }
                }
                break;
            }
        }
        cout << endl;
    }
}

int main(void) {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // Use cin for strings for easy input
    cin >> n >> k >> c;
    for (int i = 0; i < n; i++) {
        cin >> name;
        names[i] = name;
        nameIndex[name] = i;
    }

    for (int i = 0; i < k; i++) {
        cin >> first >> second;
        from = nameIndex[first];
        to = nameIndex[second];
        dislike[from] |= (1<<to);
        dislike[to] |= (1<<from);
    }

    solve(names, dislike, n, c);

    return 0;
}