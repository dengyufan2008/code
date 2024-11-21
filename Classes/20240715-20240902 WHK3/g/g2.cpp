#include <iostream>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxL = 100, kMod = 1e9 + 7;
LL f[kMaxL][kMaxL];

LLL Read() {
  LLL x = 0;
  int c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

void Init() {
  for (int i = 0; i < kMaxL; i++) {
    f[i][i] = 1;
    for (int j = 0; j < i; j++) {
      for (int k = 0; k <= j; k++) {
        f[i][j] = (f[i][j] + f[i - 1][k] * f[i - 1 - k][j - k]) % kMod;
      }
    }
  }
}

LL Solve(LLL n) {
  static LL ans, g[kMaxL], h[kMaxL];
  ans = 0, fill(g, g + kMaxL, 0);
  for (int i = 0, o = 0; i < kMaxL; i++) {
    if (n >> i & 1 ^ 1) {
      continue;
    }
    if (o) {
      for (int j = 0; j <= i; j++) {
        h[j] = 0;
        for (int k = 0; k <= j; k++) {
          h[j] = (h[j] + g[k] * f[i - k][j - k]) % kMod;
        }
      }
      for (int j = 0; j <= i; j++) {
        g[j] = h[j];
      }
    } else {
      o = 1, copy(f[i], f[i] + i + 1, g);
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    ans = (ans + g[i]) % kMod;
  }
  return ans;
}

int main() {
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), cout << Solve(Read()) << '\n';
  return 0;
}
