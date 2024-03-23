#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 16, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n, m, k, ans, a[kMaxN][kMaxN], b[kMaxN][kMaxN], lg[1 << kMaxN],
    c[1 << kMaxN], d[1 << kMaxN], f[1 << kMaxN], g[kMaxN][1 << kMaxN];

int PopCount(int x) {
  int ans = 0;
  for (; x; x >>= 1) {
    ans += x & 1;
  }
  return ans;
}

int Pow(int x, int y = kMod - 2) {
  int ans = 1;
  for (; y; y >>= 1) {
    if (y & 1) {
      ans = 1LL * ans * x % kMod;
    }
    x = 1LL * x * x % kMod;
  }
  return ans;
}

int SpanningTree(int n, int g[kMaxN][kMaxN]) {
  static int e[kMaxN][kMaxN];
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      e[i][j] = kMod - g[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      e[i][i] += g[i][j];
    }
  }
  n--;
  int s = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (e[j][i]) {
        if (i ^ j) {
          s = kMod - s, swap(e[i], e[j]);
        }
        break;
      }
    }
    if (!e[i][i]) {
      return 0;
    }
    int inv = Pow(e[i][i]);
    for (int j = i + 1; j < n; j++) {
      int c = 1LL * e[j][i] * inv % kMod;
      for (int k = i; k < n; k++) {
        e[j][k] = (e[j][k] - 1LL * e[i][k] * c % kMod + kMod) % kMod;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    s = 1LL * s * e[i][i] % kMod;
  }
  return s;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    lg[1 << i] = i;
  }
  for (int i = 0; i < (1 << n); i++) {
    fill(&b[0][0], &b[kMaxN][0], 0);
    for (int j = 0, _j = i; _j; j++, _j ^= _j & -_j) {
      for (int k = 0, _k = i; _k; k++, _k ^= _k & -_k) {
        b[j][k] = a[lg[_j & -_j]][lg[_k & -_k]];
      }
    }
    d[i] = SpanningTree(PopCount(i), b);
  }
  ans = 1LL * (kMod - d[~(-1 << n)]) * (n - 1) % kMod;
  for (int i = 0; i < n; i++) {
    f[0] = 1, fill(&f[1], &f[1 << n], 0), fill(&c[0], &c[1 << n], 0);
    for (int j = 1; j < (1 << n); j++) {
      for (int k = j; k; k ^= k & -k) {
        c[j] += a[i][lg[k & -k]];
      }
    }
    for (int j = 1; j < (1 << n); j++) {
      if (!(j & 1 << i)) {
        int _j = j ^ (j & -j);
        if (a[i][lg[j & -j]]) {
          f[j] = (f[j] + f[_j]) % kMod;
        }
        for (int _k = _j; _k; _k = _k - 1 & _j) {
          int k = _k ^ (j & -j);
          f[j] = (f[j] + 1LL * f[j ^ k] * d[k] % kMod * (c[k] * (c[k] + 1) / 2) % kMod) % kMod;
        }
      }
    }
    ans = (ans + f[~(-1 << n) ^ (1 << i)]) % kMod;
  }
  for (int i = 0; i < n; i++) {
    g[i][1 << i] = 1;
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int j = i ^ (i & -i); j; j ^= j & -j) {
      for (int k = i ^ (j & -j); k; k ^= k & -k) {
        if (a[lg[j & -j]][lg[k & -k]]) {
          g[lg[j & -j]][i] = (g[lg[j & -j]][i] + g[lg[k & -k]][i ^ (j & -j)]) % kMod;
        }
      }
    }
  }
  for (int i = 0; i < (1 << n); i++) {
    if (PopCount(i) > 2) {
      int w = 1;
      if (i != ~(-1 << n)) {
        fill(&b[0][0], &b[kMaxN][0], 0);
        for (int j = 0; j < n; j++) {
          if (!(i & 1 << j)) {
            for (int k = i ^ (i & -i); k; k ^= k & -k) {
              b[j][lg[k & -k]] = b[lg[k & -k]][j] = 1;
            }
            break;
          }
        }
        for (int _j = 0; _j < n; _j++) {
          for (int _k = 0; _k < n; _k++) {
            int j = _j, k = _k;
            if (i & 1 << j) {
              j = lg[i & -i];
            }
            if (i & 1 << k) {
              k = lg[i & -i];
            }
            b[j][k] += j != k && a[_j][_k];
          }
        }
        w = SpanningTree(n, b);
      }
      w = 1LL * w * (PopCount(i) - 1) % kMod * kInv2 % kMod;
      for (int j = i; j; j ^= j & -j) {
        if (a[lg[i & -i]][lg[j & -j]]) {
          ans = (ans - 1LL * w * g[lg[j & -j]][i] % kMod + kMod) % kMod;
        }
      }
    }
  }
  cout << ans;
  return 0;
}
