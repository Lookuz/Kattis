#include <cstdio>
#include <cstring>
using namespace std;

// Program first takes in each word of the dictionary, and forms a bitmap of each word with the ith bit 
// representing the ith letter in the alphabet. If the ith letter is present, the ith bit in the bitmap is set to 1
// The function getMaxSentences is then called recursively which greedily chooses whether to pick each word or not in the sentence.
// If the word is picked, the word's bitmap is OR-ed with the current bitmap to included letters from 
// words that have previously been added, and the current word. If the current bitmap already has the first 26 bits set to 1 (it has all 26 letters),
// the answer count is incremented.

int N; // Number of words in the dictionary
int word_bitmap[28] = {0}; // Array that stores bitmaps of each word in the dictionary; bitmap records a 1 if the ith letter is present
char word[105];
int length, ans = 0;

int MAX_LETTERS = (1 << 26) - 1; // Threshold for all letters in a sentence; has last 26 bits set to 1

// Function that greedily chooses either to take each word or not
// If word is taken, it's bitmap is OR-ed with the current bitmap to represent all letters that are currently included in the sentence
// Time complexity: O(2^n)
int getMaxSentences(int pos, int bitmap) {
    // If no more words left to choose,
    // If all letters are present
    if (pos == N) {
        if (bitmap == MAX_LETTERS) {
            ans++;
        }

        return 0;
    }

    getMaxSentences(pos + 1, bitmap | word_bitmap[pos]); // Take current word
    getMaxSentences(pos + 1, bitmap); // Don't take current word

    return ans;
}

int main(void) {

    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%s", word);
        length = strlen(word);
        for(int j = 0; j < length; j++) { // Record a 1 at the ith position if the ith letter is present in this word
            // Does the operation: bitmap[i] = bitmap[i] OR 2^p where p is the position of the jth letter in the word in the alphabet
            word_bitmap[i] |= 1 << (word[j] - 'a');
        }
    }

    getMaxSentences(0, 0);

    printf("%d", ans);

    return 0;
}