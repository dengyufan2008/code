#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#define LL long long

using namespace std;

ifstream cin("silksong.in");
ofstream cout("silksong.out");

const int kMod = 1e9 + 7;
int n, m;

namespace Solve1 {
const int kMaxN = 22;
LL f[1 << kMaxN];

int main() {
  f[0] = 1;
  for (int i = 0, x, y; i < m; i++) {
    cin >> x >> y, x--, y--;
    if (x == y) {
      for (int s = ~(-1 << n); s >= 0; s--) {
        if (s >> x & 1) {
          f[s] = (f[s] + f[s] + f[s ^ 1 << x]) % kMod;
        }
      }
    } else {
      for (int s = ~(-1 << n); s >= 0; s--) {
        if (s >> x & s >> y & 1) {
          f[s] = (f[s] + f[s] + f[s ^ 1 << x] + f[s ^ 1 << y]) % kMod;
          f[s] = (f[s] + f[s ^ 1 << x ^ 1 << y]) % kMod;
        }
      }
    }
  }
  cout << f[~(-1 << n)] << '\n';
  return 0;
}
}  // namespace Solve1

namespace Solve2 {
const int kMaxN = 40, kMaxM = 60, kMidN = 24, kMidM = 24, kTimes = 20;
int t, k, p, a[kMaxN], b[kMaxN], c[kMaxN];
LL ans, f[1 << kMidN], g[1 << kMidN];
pair<int, int> e[kMaxM], w[kMaxM];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int Calc() {
  int o = 0;
  for (int i = 0; i < m; i++) {
    o += (b[e[i].first] == k) ^ (b[e[i].second] == k);
  }
  return o;
}

bool C() {
  k++, t = Rand() % (kMidN + kMidN - kMaxN + 1) + kMaxN - kMidN;
  for (int i = 0; i < t; i++) {
    b[i] = k;
  }
  int o = Calc();
  for (int i = 0; i < kTimes && o > kMidM; i++) {
    int x = Rand() % t + 1, y = Rand() % (n - t) + 1;
    int p = 0, q = 0;
    for (int j = 0; j < n && (!p || !q); j++) {
      if (b[j] == k && !--x) {
        p = j;
      } else if (b[j] != k && !--y) {
        q = j;
      }
    }
    b[p] = 0, b[q] = k;
    int _o = Calc();
    if (_o < o) {
      o = _o;
    } else {
      b[p] = k, b[q] = 0;
    }
  }
  return o <= kMidM;
}

int main() {
  for (int i = 0; i < m; i++) {
    cin >> e[i].first >> e[i].second;
    e[i].first--, e[i].second--;
  }
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
  for (shuffle(a, a + n, Rand); !C(); shuffle(a, a + n, Rand)) {
  }
  for (int i = 0, l = 0, r = 0; i < n; i++) {
    if (b[i] == k) {
      c[i] = l++;
    } else {
      c[i] = r++;
    }
  }
  f[0] = g[0] = 1;
  for (int i = 0; i < m; i++) {
    int x = e[i].first, y = e[i].second;
    int _x = c[x], _y = c[y];
    if (b[x] == k && b[y] == k) {
      if (_x == _y) {
        for (int s = ~(-1 << t); s >= 0; s--) {
          if (s >> _x & 1) {
            f[s] = (f[s] + f[s] + f[s ^ 1 << _x]) % kMod;
          }
        }
      } else {
        for (int s = ~(-1 << t); s >= 0; s--) {
          if (s >> _x & s >> _y & 1) {
            f[s] = (f[s] + f[s] + f[s ^ 1 << _x] + f[s ^ 1 << _y]) % kMod;
            f[s] = (f[s] + f[s ^ 1 << _x ^ 1 << _y]) % kMod;
          }
        }
      }
    } else if (b[x] != k && b[y] != k) {
      if (_x == _y) {
        for (int s = ~(-1 << n - t); s >= 0; s--) {
          if (s >> _x & 1) {
            g[s] = (g[s] + g[s] + g[s ^ 1 << _x]) % kMod;
          }
        }
      } else {
        for (int s = ~(-1 << n - t); s >= 0; s--) {
          if (s >> _x & s >> _y & 1) {
            g[s] = (g[s] + g[s] + g[s ^ 1 << _x] + g[s ^ 1 << _y]) % kMod;
            g[s] = (g[s] + g[s ^ 1 << _x ^ 1 << _y]) % kMod;
          }
        }
      }
    } else {
      b[x] != k ? swap(_x, _y) : void();
      w[p++] = {_x, _y};
    }
  }
  for (int i = 0; i < t; i++) {
    for (int s = 0; s < 1 << t; s++) {
      if (s >> i & 1 ^ 1) {
        f[s] += f[s | 1 << i];
        f[s] >= kMod && (f[s] -= kMod);
      }
    }
  }
  for (int i = 0; i < n - t; i++) {
    for (int s = 0; s < 1 << n - t; s++) {
      if (s >> i & 1 ^ 1) {
        g[s] += g[s | 1 << i];
        g[s] >= kMod && (g[s] -= kMod);
      }
    }
  }
  ans = f[~(-1 << t)] * g[~(-1 << n - t)] % kMod;
  for (int s = 1; s < 1 << p; s++) {
    int l = 0, r = 0;
    for (int i = 0; i < p; i++) {
      if (s >> i & 1) {
        l |= 1 << w[i].first;
        r |= 1 << w[i].second;
      }
    }
    LL w1 = f[(~(-1 << t)) ^ l];
    LL w2 = g[(~(-1 << n - t)) ^ r];
    ans = (ans + w1 * w2) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Solve2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  if (n <= 22) {
    return Solve1::main();
  } else {
    return Solve2::main();
  }
}
