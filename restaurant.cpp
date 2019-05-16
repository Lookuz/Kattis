#include <iostream>
#include <string>
using namespace std;

int N, m;
int pile1;
int pile2;
string op;

int main() {
    while(true) {
        scanf("%d\n", &N);
        if (N == 0) {
            break;
        }
        pile1 = 0;
        pile2 = 0;
        for (int i = 0; i < N; i++) {
            cin >> op >> m;
            if (op.compare("DROP") == 0) {
                printf("DROP 2 %d\n", m);
                pile2 += m;
            }
            if (op.compare("TAKE") == 0) {
                if (pile1 >= m) {
                    printf("TAKE 1 %d\n", m);
                    pile1 -= m;
                } else {
                    if (pile1 != 0) {
                        printf("TAKE 1 %d\n", pile1);
                        m -= pile1;
                    }
                    printf("MOVE 2->1 %d\n", pile2);
                    printf("TAKE 1 %d\n", m);
                    pile1 = pile2 - m;
                    pile2 = 0;
                }
            }
        }
        printf("\n");
    }
}