#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kMaxN = 201, kMaxL = 8, kMod = 1e9 + 7;
struct V {
  int r, s, c, d, f[kMaxL];
  LL g, ans, h[kMaxN][kMaxN];
  vector<int> e;
} v[kMaxN];
int n, s;
LL ans, fact[kMaxN], _fact[kMaxN];

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

bool Son(int x, int y) {
  return v[x].r <= v[y].r && v[x].r + v[x].s > v[y].r;
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int F(int x, int d) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (d >> i & 1) {
      x = v[x].f[i];
    }
  }
  return x;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Init(int f, int x) {
  static int k = 0;
  v[x].r = ++k, v[x].s = 1, v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      Init(x, i);
      v[x].s += v[i].s;
    }
  }
}

void Calc1(int f, int x, int y) {
  v[x].g = 1, v[x].c = 1;
  for (int i : v[x].e) {
    if (i != f) {
      Calc1(x, i, y);
      v[i].c -= i == y;
      v[x].g = v[x].g * v[i].g % kMod * C(v[x].c + v[i].c - 1, v[x].c - 1) % kMod;
      v[x].c += v[i].c;
    }
  }
}

void Calc2(int f, int x, int y) {
  if (x == y) {
    fill(&v[x].h[y][1], &v[x].h[y][v[x].s], 0);
    v[x].h[y][v[x].s] = v[x].g, v[x].c = v[x].s;
  } else {
    int p;
    for (int i : v[x].e) {
      if (i != f && Son(i, y)) {
        p = i, Calc2(x, i, y);
      }
    }
    v[x].c = v[p].c + 1;
    copy(&v[p].h[y][1], &v[p].h[y][v[p].c] + 1, &v[x].h[y][1]);
    v[x].h[y][v[p].c + 1] = 0;
    for (int i : v[x].e) {
      if (i != f && i != p) {
        LL h[v[x].c + v[i].c + 1] = {};
        for (int j = 1; j < v[x].c; j++) {
          for (int k = 0; k <= v[i].c; k++) {
            h[j + k] = (h[j + k] + v[x].h[y][j] * v[i].g % kMod * C(j + k - 1, j - 1) % kMod * C(v[x].c + v[i].c - j - k - 1, v[x].c - j - 1)) % kMod;
          }
        }
        copy(&h[1], &h[v[x].c + v[i].c] + 1, &v[x].h[y][1]);
        v[x].c += v[i].s;
      }
    }
  }
}

void Calc3(int f, int x, int y) {
  if (x != y) {
    int p;
    for (int i : v[x].e) {
      if (i != f && Son(i, y)) {
        p = i, Calc3(x, i, y);
      }
    }
    v[x].ans = v[p].ans, v[x].c = v[p].c + 1;
    for (int i : v[x].e) {
      if (i != f && i != p) {
        v[x].ans = v[x].ans * v[i].g % kMod * C(v[x].c + v[i].s - 2, v[x].c - 2) % kMod;
        v[x].c += v[i].s;
      }
    }
  }
}

void M(int p, int q) {
  int lca = Lca(p, q);
  int x = F(p, v[p].d - v[lca].d - 1);
  int y = F(q, v[q].d - v[lca].d - 1);
  v[lca].ans = 0, v[lca].c = v[x].c + v[y].c + 1;
  for (int i = 1; i <= v[x].c; i++) {
    for (int j = 1; j <= v[y].c; j++) {
      v[lca].ans = (v[lca].ans + v[x].h[p][i] * v[y].h[q][j] % kMod * C(i + j - 2, i - 1) % kMod * C(v[x].c + v[y].c - i - j, v[x].c - i)) % kMod;
    }
  }
  for (int i : v[lca].e) {
    if (i != v[lca].f[0] && i != x && i != y) {
      v[lca].ans = v[lca].ans * v[i].g % kMod * C(v[lca].c + v[i].s - 2, v[lca].c - 2) % kMod;
      v[lca].c += v[i].s;
    }
  }
  Calc3(0, s, lca);
  ans = (ans + v[s].ans * abs(p - q) * 2) % kMod;
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
  cin >> n >> s;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init(0, s);
  for (int i = 1; i <= n; i++) {
    if (i != s) {
      Calc1(0, s, i), ans = (ans + v[s].g * abs(v[i].f[0] - i)) % kMod;
    }
  }
  Calc1(0, s, 0);
  for (int i = 1; i <= n; i++) {
    Calc2(0, s, i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (!Son(i, j) && !Son(j, i)) {
        M(i, j);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
