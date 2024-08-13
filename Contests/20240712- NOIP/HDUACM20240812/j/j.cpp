#include <fstream>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 1e6 + 1, kMaxM = 60, kMod = 998244353;
int t, n, m;
LL l, r, s, a[kMaxN], pw[kMaxN];
LL f[kMaxM][2][2], g[kMaxN][2][2];  // 有无没顶到的 异或和为多少

void CalcF() {
  for (int i = kMaxM - 1; i >= 0; i--) {
    g[0][0][0] = 1;
    for (int j = 1; j <= n; j++) {
      LL w = ((a[j] & ~(-1LL << i)) + 1) % kMod;
      if (a[j] >> i & 1) {
        g[j][0][0] = g[j - 1][0][1] * w % kMod;
        g[j][0][1] = g[j - 1][0][0] * w % kMod;
        g[j][1][0] = (g[j - 1][0][0] + g[j - 1][1][0] * pw[i] + g[j - 1][1][1] * w) % kMod;
        g[j][1][1] = (g[j - 1][0][1] + g[j - 1][1][1] * pw[i] + g[j - 1][1][0] * w) % kMod;
      } else {
        g[j][0][0] = g[j - 1][0][0] * w % kMod;
        g[j][0][1] = g[j - 1][0][1] * w % kMod;
        g[j][1][0] = g[j - 1][1][0] * w % kMod;
        g[j][1][1] = g[j - 1][1][1] * w % kMod;
      }
    }
    f[i][0][0] = g[n][0][0], f[i][0][1] = g[n][0][1];
    f[i][1][0] = g[n][1][0], f[i][1][1] = g[n][1][1];
  }
}

LL CalcAns(LL x) {
  LL ans = 0;
  for (int i = kMaxM - 1; i >= 0; i--) {
    LL w = ((x & ~(-1LL << i)) + 1) % kMod;
    if (x >> i & 1) {
      ans = (ans + f[i][0][0] + f[i][1][0] * pw[i] + f[i][1][1] * w) % kMod;
      if (s >> i & 1 ^ 1) {
        return ans;
      }
    } else {
      ans = (ans + f[i][1][0] * w) % kMod;
      if (s >> i & 1) {
        return ans;
      }
    }
  }
  return (ans + 1) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  cin >> t;
  while (t--) {
    s = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], s ^= a[i];
    }
    CalcF();
    for (int i = 1; i <= m; i++) {
      cin >> l >> r;
      if (l) {
        cout << (CalcAns(r) - CalcAns(l - 1) + kMod) % kMod << '\n';
      } else {
        cout << CalcAns(r) << '\n';
      }
    }
  }
  return 0;
}
