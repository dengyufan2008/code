#include <algorithm>
#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 10, kMod = 998244353;
int n, m, t, x, y, d[kMaxN];
LL ans, p[kMaxN][kMaxN], px[kMaxN], py[kMaxN];
unordered_map<int, LL> f[kMaxN];

LL Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> x >> y, n = 6, m = 7, x /= n, y /= m;
  for (int i = 0; i <= m; i++) {
    p[i][0] = px[i] = py[i] = 1;
    for (int j = 1; j <= i; j++) {
      p[i][j] = (p[i - 1][j - 1] + p[i - 1][j]) % kMod;
      Update(px[i], Pow(p[i][j], x)), Update(py[i], Pow(p[i][j], y));
    }
  }
  f[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (auto u : f[i]) {
      for (int s = 0; s < 1 << m; s++) {
        int w = u.first, c = 0;
        for (int j = 0; j < m; j++) {
          d[j] = w % 10, w /= 10;
        }
        for (int j = 0; j < m; j++) {
          s >> j & 1 ? d[j]++ : c++;
        }
        w = 0, sort(d, d + m);
        for (int j = m - 1; j >= 0; j--) {
          w = w * 10 + d[j];
        }
        Update(f[i + 1][w], u.second * px[c]);
      }
    }
  }
  for (auto u : f[n]) {
    int w = u.first;
    LL s = 1;
    for (int i = 0; i < m; i++) {
      int c = w % 10;
      LL t = 0;
      for (int j = 0; j <= c; j++) {
        LL r = (p[c][j] << j) % kMod * py[c - j] % kMod;
        Update(t, j & 1 ? kMod - r : r);
      }
      s = s * t % kMod, w /= 10;
    }
    ans = (ans + u.second * s) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
