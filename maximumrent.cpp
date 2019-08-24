// Algorithm that uses Linear Programming Simplex method to solve for the maximum value 
// of the equation ax + by. Simplex method adapted from the stanfordacm github repository Simplex.cc
// Constraints given via input are converted into upper bound constraints (Ax ≤ B)
// The equaton given is maximized according to constraints (Ax ≤ B) and x ≥ 0.
// Running time of Simplex method: O(m^n) where m is the number of constraints and n the number of variables
#include <cstdio>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;
const int _m = 4;
const int n = 2;

int a, b, m, o;
VD x;
DOUBLE _A[_m][n] = {
    {-1, 0},
    {0, -1},
    {1, 1},
    {-2, -1}
}; // Constraint matrix

DOUBLE _B[_m]; // Constraint value vector
DOUBLE _C[n]; // Maximization coefficients

struct LPSolver {
  int m, n;
  VI B, N;
  VVD D;

  LPSolver(const VVD &A, const VD &b, const VD &c) :
    m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)) {
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
    for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m + 1][n] = 1;
  }

  void Pivot(int r, int s) {
    double inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; i++) if (i != r)
      for (int j = 0; j < n + 2; j++) if (j != s)
        D[i][j] -= D[r][j] * D[i][s] * inv;
    for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  bool Simplex(int phase) {
    int x = phase == 1 ? m + 1 : m;
    while (true) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (phase == 2 && N[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
      }
      if (D[x][s] > -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
          ((D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r])) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
  }

  DOUBLE Solve(VD &x) {
    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -EPS) {
      Pivot(r, n);
      if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<DOUBLE>::infinity();
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; j++)
          if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
        Pivot(i, s);
      }
    }
    if (!Simplex(2)) return numeric_limits<DOUBLE>::infinity();
    x = VD(n);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return D[m][n + 1];
  }
};

int main(void) {

    scanf("%d %d", &a, &b);
    scanf("%d %d", &m, &o);

    // Initialize constraints
    _B[0] = _B[1] = -1;
    _B[2] = m;
    _B[3] = -1 * o;

    // Initialize maximization coefficients
    _C[0] = a;
    _C[1] = b;

    VVD A(4);
    VD B(_B, _B + _m);
    VD C(_C, _C + n);
    for (int i = 0; i < 4; i++) {
        A[i] = VD(_A[i], _A[i] + _m);
    }

    LPSolver solver(A, B, C);
    DOUBLE result = solver.Solve(x);

    printf("%d", int(result));

    return 0;
}