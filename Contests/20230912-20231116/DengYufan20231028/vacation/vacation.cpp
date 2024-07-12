#include <bitset>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("vacation.in");
ofstream cout("vacation.out");

const int kMaxN = 51, kMod = 998244353;
int n, m, k, ans, lg[1 << (kMaxN >> 1)], s[1 << (kMaxN >> 1)], t[1 << (kMaxN >> 1)];
bitset<kMaxN> w, e[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int PopCount(int x) {
  int c = 0;
  for (; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    e[x - 1][y - 1] = e[y - 1][x - 1] = 1;
  }
  k = n >> 1;
  for (int i = 0; i < n - k; i++) {
    lg[1 << i] = i;
  }
  fill(&s[1], &s[1 << k], -1);
  for (int i = 1; i < (1 << k); i++) {
    int x = lg[i & -i], y = PopCount(i);
    if (~s[i ^ (1 << x)]) {
      for (int j = i ^ (1 << x); j; j ^= j & -j) {
        if (!e[x][lg[j & -j]]) {
          s[i] -= y + 1;
          break;
        }
      }
      ans = max(ans, s[i] += y + 1);
    }
  }
  fill(&t[1], &t[1 << n - k], -1);
  for (int i = 1; i < (1 << n - k); i++) {
    int x = lg[i & -i], y = PopCount(i);
    if (~t[i ^ (1 << x)]) {
      for (int j = i ^ (1 << x); j; j ^= j & -j) {
        if (!e[x + k][lg[j & -j] + k]) {
          t[i] -= y + 1;
          break;
        }
      }
      ans = max(ans, t[i] += y + 1);
    }
  }
  for (int j = 0; j < n - k; j++) {
    for (int i = 0; i < (1 << n - k); i++) {
      if (i >> j & 1) {
        t[i] = max(t[i], t[i ^ (1 << j)]);
      }
    }
  }
  for (int i = 0; i < (1 << k); i++) {
    w = e[lg[i & -i]];
    for (int j = i ^ (i & -i); j; j ^= j & -j) {
      w &= e[lg[j & -j]];
    }
    int x = (w >> k).to_ulong();
    if (~s[i] && ~t[x]) {
      ans = max(ans, s[i] + t[x]);
    }
  }
  cout << 1LL * (ans - 1) * Pow(ans * 2) % kMod;
  return 0;
}
