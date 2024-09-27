#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("mex.in");
ofstream cout("mex.out");

const int kMaxN = 201, kMod = 998244353;
struct V {
  int l;
  LL f[kMaxN], g[kMaxN];
  vector<int> e;
} v[kMaxN];
int n, c[kMaxN];
LL fact[kMaxN], _fact[kMaxN], pw[kMaxN][kMaxN];

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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int CalcB(int fa, int x) {
  static vector<int> e;
  fill(&c[0], &c[n], 0);
  for (int i : v[x].e) {
    if (i != fa) {
      c[v[i].l]++;
      if (v[i].l) {
        e.push_back(i);
      }
    }
  }
  v[x].e.swap(e), e.clear();
  int b = n - 1;
  for (int i = n - 1; i >= 0; i--) {
    c[i] += c[i + 1];
    if (i + c[i] < b + c[b]) {
      b = i;
    }
  }
  v[x].l = c[0];
  return b;
}

void Dp(int x, int b, int l, int w) {
  LL f[1 << b], g[1 << l][w + 1], h[1 << l][w + 1];
  sort(v[x].e.begin(), v[x].e.end(), [](int i, int j) {
    return v[i].l > v[j].l;
  });
  f[0] = 1, fill(&f[1], &f[1 << b], 0);
  for (int i = l; i < v[x].e.size(); i++) {
    int y = v[x].e[i];
    for (int s = (1 << b) - 1; s >= 0; s--) {
      if (f[s]) {
        LL w = f[s];
        f[s] = 0;
        for (int j = 0; j <= v[y].l; j++) {
          f[s | 1 << j] = (f[s | 1 << j] + w * v[y].f[j]) % kMod;
        }
      }
    }
  }
  fill(&h[0][0], &h[1 << l][0], 0);
  for (int s = 0; s < 1 << b; s++) {
    if (!f[s]) {
      continue;
    }
    g[0][0] = f[s], fill(&g[0][1], &g[1 << l][0], 0);
    for (int i = 0; i <= v[x].l; i++) {
      if ((1LL << i <= s) && (s >> i & 1)) {
        for (int j = 0; j < l; j++) {
          int y = v[x].e[j];
          for (int t = 0; t < 1 << l; t++) {
            if (t >> j & 1 ^ 1) {
              for (int k = 0; k <= w; k++) {
                g[t | 1 << j][k] = (g[t | 1 << j][k] + g[t][k] * v[y].f[i]) % kMod;
              }
            }
          }
        }
        for (int j = w - 1; j >= 0; j--) {
          for (int k = j + 1; k <= w; k++) {
            for (int t = 0; t < 1 << l; t++) {
              g[t][k] = (g[t][k] + g[t][j] * C(w - j, k - j)) % kMod;
            }
          }
        }
      } else {
        for (int t = 0; t < 1 << l; t++) {
          LL d = 1;
          for (int j = 0; j < l; j++) {
            if (t >> j & 1 ^ 1) {
              d = d * v[v[x].e[j]].g[i + 1] % kMod;
            }
          }
          for (int j = 0; j <= w; j++) {
            v[x].f[i] = (v[x].f[i] + g[t][j] * d % kMod * pw[n - i][w - j]) % kMod;
          }
        }
        for (int j = 0; j < l; j++) {
          int y = v[x].e[j];
          for (int t = 0; t < 1 << l; t++) {
            if (t >> j & 1 ^ 1) {
              for (int k = 0; k <= w; k++) {
                h[t | 1 << j][k] = (h[t | 1 << j][k] + (g[t][k] + h[t][k]) * v[y].f[i]) % kMod;
              }
            }
          }
        }
        for (int j = w - 1; j >= 0; j--) {
          for (int k = j + 1; k <= w; k++) {
            for (int t = 0; t < 1 << l; t++) {
              h[t][k] = (h[t][k] + (g[t][j] + h[t][j]) * C(w - j, k - j)) % kMod;
            }
          }
        }
        for (int t = 0; t < 1 << l; t++) {
          for (int j = 0; j <= w; j++) {
            g[t][j] = h[t][j], h[t][j] = 0;
          }
        }
      }
    }
  }
  for (int i = v[x].l; i >= 0; i--) {
    v[x].g[i] = (v[x].g[i + 1] + v[x].f[i]) % kMod;
  }
}

void T(int fa, int x) {
  for (int i : v[x].e) {
    if (i != fa) {
      if (v[i].e.size() > 1) {
        T(x, i);
      } else {
        v[i].e.clear();
      }
    }
  }
  int b = CalcB(fa, x);
  Dp(x, b, c[b], c[0] - c[1]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j < kMaxN; j++) {
      pw[i][j] = Pow(i, j);
    }
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (n == 1) {
    cout << "1\n1\n";
    return 0;
  }
  T(0, 1);
  for (int i = 0; i <= n; i++) {
    cout << v[1].f[i] << '\n';
  }
  return 0;
}
