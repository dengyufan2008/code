#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e6 + 1, kMaxM = 21;
int n, ans, a[kMaxN], f[1 << kMaxM];
int nt1[kMaxN][kMaxM];  // 从 i 往后的第一个 j 的位置
int nt2[kMaxN][kMaxM];  // 从 i 往后的第一个无序二元组 (a_i, j) 的靠前位置

int Merge(int s, int x) {
  if (s >> x & 1) {
    return s;
  }
  int t = s & (1 << x) - 1;
  if (t) {
    s ^= 1 << 31 - __builtin_clz(t);
  }
  return s | 1 << x;
}

void Trans(int s, int x) {
  int p = n;
  for (int i = 0; i < kMaxM; i++) {
    if (s >> i & 1) {
      continue;
    }
    for (int j = i; j < kMaxM; j++) {
      if (s >> j & 1) {
        continue;
      }
      if (nt1[x][i] != n + 1 && nt2[nt1[x][i]][j] != n + 1) {
        p = min(p, nt2[nt1[x][i]][j]);
      }
      if (nt1[x][j] != n + 1 && nt2[nt1[x][j]][i] != n + 1) {
        p = min(p, nt2[nt1[x][j]][i]);
      }
    }
  }
  f[s] = max(f[s], p - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, ans = kMaxM;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i]--;
  }
  for (int i = 0; i < kMaxM; i++) {
    nt1[n][i] = nt2[n][i] = n + 1;
  }
  nt1[n][a[n]] = n;
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j < kMaxM; j++) {
      nt1[i][j] = nt1[i + 1][j], nt2[i][j] = n + 1;
      if (nt1[i + 1][a[i]] != n + 1) {
        nt2[i][j] = min(nt2[i][j], nt2[nt1[i + 1][a[i]]][j]);
      }
      if (nt1[i + 1][j] != n + 1) {
        nt2[i][j] = min(nt2[i][j], nt2[nt1[i + 1][j]][a[i]]);
      }
    }
    nt1[i][a[i]] = nt2[i][a[i + 1]] = i;
  }
  fill(&f[1], &f[1 << kMaxM], -1);
  for (int s = 0; s < 1 << kMaxM; s++) {
    if (f[s] >= n - 1) {
      ans = min(ans, __builtin_popcount(s));
      continue;
    }
    Trans(Merge(s, a[f[s] + 1]), f[s] + 1);
    Trans(Merge(s, a[f[s] + 2]), f[s] + 2);
  }
  cout << ans << '\n';
  return 0;
}
