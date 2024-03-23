#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxN = 201, kMaxM = 101, kMod = 1e9 + 7;
struct A {
  LL k, w;
  LLL s;
};
int n, m, c, b[kMaxM], r[kMaxM], gcd[kMaxM][kMaxM];
LL ans, f[kMaxN], g[kMaxN], pw[kMaxN];
vector<A> v;

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

int PopCount(LLL s) {
  int c = 0;
  for (; s; s >>= 1) {
    c += s & 1;
  }
  return c;
}

int GetRoot(int x) { return r[x] == x ? x : r[x] = GetRoot(r[x]); }

void Calc(LLL s) {
  LL k = 0, w = 0;
  for (int i = 1; i <= n; i++) {
    if (i >= m) {
      f[i] = g[i - m];
      for (int j = 1; j < m; j++) {
        if (s >> j & 1) {
          f[i] = (f[i] - f[i - j] + kMod) % kMod;
        }
      }
    }
    g[i] = (g[i - 1] * c - f[i] + kMod) % kMod;
    k = (k + f[i] * pw[n - i]) % kMod;
  }
  for (int i = 1; i <= m; i++) {
    r[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    if (s >> i & 1) {
      for (int j = 1; j + i <= m; j++) {
        if (GetRoot(j) != GetRoot(j + i)) {
          r[GetRoot(j)] = GetRoot(j + i);
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    w += GetRoot(i) == i;
  }
  v.push_back({k, pw[w], s});
}

void S(int x, int p, LLL s) {
  if (x == m) {
    return Calc(s);
  }
  int y = m - x;
  for (int i = 1; i <= y; i++) {
    if (!p || i == p || i + p - gcd[i][p] > y) {
      if (i * 2 <= y) {
        int z = y / i * i - i, o = 1;
        LLL t = s;
        for (int j = 1; j <= z; j++) {
          if (j % i) {
            o &= !b[x + j];
          } else {
            t |= (LLL)1 << x + j;
          }
        }
        if (o) {
          if (z + i < y) {
            b[x + z + i]++;
          }
          S(x + z, i, t);
          if (z + i < y) {
            b[x + z + i]--;
          }
        }
      } else {
        S(x + i, 0, s | (LLL)1 << x + i);
      }
    }
    if (b[x + i]) {
      break;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> c;
  g[0] = pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * c % kMod;
  }
  for (int i = 0; i < kMaxM; i++) {
    for (int j = 0; j < kMaxM; j++) {
      gcd[i][j] = Gcd(i, j);
    }
  }
  S(0, 0, 0);
  sort(v.begin(), v.end(), [](A i, A j) {
    return PopCount(i.s) > PopCount(j.s);
  });
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < i; j++) {
      if ((v[i].s & v[j].s) == v[i].s) {
        v[i].w = (v[i].w - v[j].w + kMod) % kMod;
      }
    }
  }
  for (A i : v) {
    ans = (ans + i.k * i.w) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
