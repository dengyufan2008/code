#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("dfs.in");
ofstream cout("dfs.out");

const int kMaxN = 28, kMaxM = kMaxN * (kMaxN - 1) / 2, kMod = 1e9 + 7;
int n, m, c, ans, e[kMaxM], f[1 << kMaxN - 1];

int R(int s) {
  if (s >> n - 1 & 1) {
    return s ^ 1 << n - 1;
  }
  return s;
}

void Update(int &x, long long y) {
  x = (x + y) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> c;
  for (int i = 0, x, y; i < m; i++) {
    cin >> x >> y, e[i] = 1 << x - 1 | 1 << y - 1, f[R(e[i])] = c;
  }
  sort(e, e + m, [](int i, int j) {
    return (i & -i) < (j & -j);
  });
  ans = 1;
  for (int s = 1; s < 1 << n - 1; s++) {
    if (f[s]) {
      int t = s;
      if (__builtin_popcount(t) & 1) {
        t |= 1 << n - 1;
      }
      ans = (ans + f[s]) % kMod;
      for (int i = 0; i < m && (e[i] & -e[i]) < (s & -s); i++) {
        if (!(t & e[i])) {
          Update(f[R(s | e[i])], 1LL * f[s] * c);
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
