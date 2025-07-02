#include <vector>
#define LL long long

using namespace std;

const LL kMaxN = 1 << 23, kInf = 1e18;
int n, a[kMaxN];
LL s, ans;
LL *h, u[kMaxN * 8];
LL **hh, *uu[kMaxN * 2];
LL **f[kMaxN];

void Update(LL &x, LL y) { x = min(x, y); }

void Dp(int x, int l) {
  f[x] = hh, hh += l;
  for (int i = 0; i < l; i++) {
    f[x][i] = h, h += l;
  }
  if (l == 1) {
    f[x][0][0] = a[x];
    return;
  }
  Dp(x << 1, l - 1), Dp(x << 1 | 1, l - 1);
  for (int i = 0; i < l - 1; i++) {
    for (int j = 0; j < l - 1; j++) {
      f[x][i][j] = kInf;
      for (int q = 0; q < l - 1; q++) {
        Update(f[x][i][j], f[x << 1][i][q - !!q] + f[x << 1 | 1][q][j]);
      }
    }
  }
  for (int i = 0; i < l - 1; i++) {
    f[x][l - 1][i] = kInf;
    for (int j = 0; j < l - 1; j++) {
      Update(f[x][l - 1][i], f[x << 1 | 1][j][i]);
    }
  }
  for (int i = 0; i < l - 1; i++) {
    f[x][i][l - 1] = f[x << 1][i][l - 2];
  }
  f[x][l - 1][l - 1] = 0;
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < l; j++) {
      f[x][i][j] += a[x];
    }
    for (int j = l - 2; j >= 0; j--) {
      Update(f[x][i][j], f[x][i][j + 1]);
    }
  }
}

LL solve(int M, vector<int> A, vector<int> B) {
  n = M, s = 0, h = u, hh = uu;
  for (int i = 1; i < 1 << n; i++) {
    s += A[i], a[i] = B[i] - A[i];
  }
  Dp(1, n), ans = 0;
  for (int i = 0; i < n; i++) {
    Update(ans, f[1][i][i]);
  }
  return s + ans;
}
