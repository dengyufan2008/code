#include <iostream>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 1502, kInf = 1e9;
int n, m, ans, a[2][kMaxN], d[2][kMaxN][kMaxN], f[kMaxN][kMaxN];

void Change(int x, int y, int z, bool b) {
  b ? swap(x, y) : (void)0, y = n - y;
  for (int i = y + 1; i <= n + 1; i += i & -i) {
    d[b][x][i] = min(d[b][x][i], z);
  }
}

int Min(int x, int y, bool b) {
  int ans = kInf;
  b ? swap(x, y) : (void)0, y = n - y;
  for (int i = y + 1; i >= 1; i -= i & -i) {
    ans = min(ans, d[b][x][i]);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int o = 0; o < 2; o++) {
    for (int i = 1; i <= n; i++) {
      cin >> a[o][i];
      ans += a[o][i];
    }
  }
  fill(&f[0][1], &f[kMaxN][0], kInf);
  fill(&d[0][0][0], &d[2][0][0], kInf);
  Change(0, 0, 0, 0), Change(0, 0, 0, 1);
  for (int i = 1; i <= n; i++) {
    int li = max(i - m - 1, 0), ri = min(i + m, n);
    f[i][ri] = min(f[i][ri], Min(i - 1, li, 0) + a[0][i]);
    f[ri][i] = min(f[ri][i], Min(li, i - 1, 1) + a[1][i]);
    for (int j = 0; j <= n; j++) {
      f[j][ri] = min(f[j][ri], Min(j, li, 0) + a[0][i]);
    }
    for (int j = 0; j <= n; j++) {
      f[ri][j] = min(f[ri][j], Min(li, j, 1) + a[1][i]);
    }
    for (int j = li; j <= ri; j++) {
      f[ri][ri] = min(f[ri][ri], Min(j, li, 0) + a[0][i] + a[1][i]);
    }
    for (int j = 0; j <= n; j++) {
      Change(j, ri, f[j][ri], 0), Change(j, ri, f[j][ri], 1);
      Change(ri, j, f[ri][j], 0), Change(ri, j, f[ri][j], 1);
    }
  }
  cout << ans - f[n][n];
  return 0;
}
