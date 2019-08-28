// Algorithm that uses brute force with meet in the middle to calculate all possible wins
// Using meet in the middle, the array is split into half and partial sums in both subarrays are calculated
// 3 cases are calculated: partial sums in both subarrays that add up to t, and partial sums across subarrays that add up to t
// To calculate partial sums adding to t, the count of each partial sum in each subarray is added to the dp tables left and right
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXSUM = 300005;
const int MAXELEMENTS = 35;
const int MAXN = 35;
const int MAXCOMBINATIONS = (1<<30) + 2;

int _g, g, m, n, t, sum, curr, win, lose;
pair<int, int> p;
int leftSize, rightSize;
int tiles[MAXELEMENTS];
int factorial[MAXELEMENTS];
int left[MAXN][MAXSUM];
int right[MAXN][MAXSUM];

// Use pascal triangle to compute n choose k
int getFactorial(int n, int k) {
    
    memset(factorial, 0, sizeof(factorial));
    factorial[0] = 1; // Zero factorial = 1

    for (int i = 1; i <= n; i++) {
        for (int j = min(i, k); j > 0; j--) {
            factorial[j] = factorial[j] + factorial[j - 1]; // Calculate current factorial based on the previous pascal triangle row
        }
    }
    return factorial[k];
}

// Function that counts the number of partial sums of subarray
void countSubArray(int tiles[], int n, int m, int sub[][MAXSUM], int offset) {

    int maxSize = (1 << m);

     for (int i = 0; i < maxSize; i++) {
        sum = 0;
        curr = 0;
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) { // If still have elements to take
                sum += tiles[j + offset];
                curr++;
            }
        }
        sub[curr][sum]++; // Add to the count of getting partial sum sum with curr number of elements
    }
}

// Implementation of subset sum algorithm using meet in the middle technique
pair<int, int> countCombinations(int tiles[], int t, int n, int m) {

    if ((n == 0 && t ==0) || m == 0) {
        return make_pair(1, 0);
    } else if (n == 0 && t > 0) {
        return make_pair(0, 1);
    }

    // Calculate partial sums of left and right subarray
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    countSubArray(tiles, n, m/2, left, 0);
    countSubArray(tiles, n, (m - m/2), right, m/2);


    // Calculate number of partial sums that lead to k-subset sum = t
    win = 0;
    lose = 0;
    for (int i = 1; i < n; i++) {

        // sort(right[n - i].begin(), right[n - i].end()); // Sort right subarray containing n - i sized subset sums

        for (int j = 1; j <= t; j++) { // For each partial sum in left subarray of size i
            curr = left[i][j]; // Current number of partial sums equals to i 
            win += curr * right[n - i][t - j]; // Match with total sum = t and total    
        }
    }

    win += left[n][t] + right[n][t];

    return make_pair(win, lose);
}

int main(void) {

    scanf("%d", &g);
    _g = 0;

    while (g > 0) {
        _g++;

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &tiles[i]);
        }
        scanf("%d %d", &n, &t);

        p = countCombinations(tiles, t, n, m);

        printf("Game %d -- %d : %d\n", _g, p.first, getFactorial(m, n) - p.first);

        g--;
    }
}