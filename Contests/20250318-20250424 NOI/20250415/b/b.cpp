#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 201, kMod = 998244353, kMaxB = 16;
struct V {
  int c;
  LL f[kMaxN], fs[kMaxN];
  vector<int> e;
} v[kMaxN];
int n;
LL h[kMaxN][kMaxN];
LL fact[kMaxN], _fact[kMaxN];

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

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void CalcH() {  // i 个互相区分的元素, n 种取值, 其中有 j 种取值一定要有
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= j; k++) {
        LL w = C(j, k) * Pow(n - k, i) % kMod;
        Update(h[i][j], k & 1 ? kMod - w : w);
      }
    }
  }
}

void DelE(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    DelE(x, i);
  }
}

void DelE2(int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (v[i].e.empty()) {
      v[x].c++;
    } else {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    DelE2(i);
  }
}

int CalcB(int x) {
  int b = 0, w1 = v[x].e.size(), w2 = w1;  // 2^(b+m) * m
  for (int i = 0; i < v[x].e.size(); i++) {
    int _b = v[v[x].e[i]].e.size() + v[v[x].e[i]].c + 1;
    int _w1 = _b + i, _w2 = i;
    if (w1 >= _w1) {
      if (w1 - _w1 > 20 || Pow(2, w1 - _w1) * w2 > _w2) {
        b = _b, w1 = _w1, w2 = _w2;
      }
    } else {
      if (_w1 - w1 < 20 && w2 > _w2 * Pow(2, _w1 - w1)) {
        b = _b, w1 = _w1, w2 = _w2;
      }
    }
  }
  return b;
}

void Dp(int x) {
  sort(v[x].e.begin(), v[x].e.end(), [](int i, int j) {
    return v[i].e.size() + v[i].c > v[j].e.size() + v[j].c;
  });
  int b = min(CalcB(x), kMaxB), m = 0;
  static LL *g;
  g = new LL[1 << b];
  fill(&g[1], &g[1 << b], 0), g[0] = 1;
  for (int i : v[x].e) {
    if (v[i].e.size() + v[i].c >= b) {
      m++;
      continue;
    }
    static LL *_g;
    _g = new LL[1 << b];
    fill(&_g[0], &_g[1 << b], 0);
    for (int s = 0; s < 1 << b; s++) {
      for (int j = 0; j <= v[i].e.size() + v[i].c; j++) {
        Update(_g[s | 1 << j], g[s] * v[i].f[j]);
      }
    }
    copy(&_g[0], &_g[1 << b], &g[0]);
    delete _g;
  }
  for (int s = 0; s < 1 << b; s++) {  // O(2^b s 2^m m (c+1))
    if (g[s]) {
      static LL *u, *f[kMaxN];  // f:已经选择的儿子个数大于等于 b 的儿子集合为 s, 钦定了 i 个位置必须由叶子填
      u = new LL[v[x].c + 1 << m];
      for (int i = 0; i <= v[x].c; i++) {
        f[i] = &u[i << m];
      }
      fill(&f[0][1], &f[v[x].c][1 << m], 0), f[0][0] = 1;
      for (int i = 0; i <= v[x].e.size() + v[x].c; i++) {
        bool o = 0;
        for (int j = 0; j < (v[x].c + 1 << m); j++) {
          o |= u[j];
        }
        if (!o) {
          break;
        }
        static LL *_u, *_f[kMaxN];
        _u = new LL[v[x].c + 1 << m];
        for (int j = 0; j <= v[x].c; j++) {
          _f[j] = &_u[j << m];
        }
        copy(&f[0][0], &f[v[x].c][1 << m], &_f[0][0]);
        for (int j = 0; j < m; j++) {
          LL w = v[v[x].e[j]].f[i];
          if (w) {
            for (int t = 0; t < 1 << m; t++) {
              if (t >> j & 1 ^ 1) {
                for (int k = 0; k <= v[x].c; k++) {
                  Update(f[k][t | 1 << j], f[k][t] * w);
                }
              }
            }
          }
        }
        if (i >= b || (s >> i & 1 ^ 1)) {
          for (int t = 0; t < 1 << m; t++) {
            LL w = g[s];
            for (int j = 0; j < m; j++) {
              if (t >> j & 1 ^ 1) {
                w = w * v[v[x].e[j]].fs[i + 1] % kMod;
              }
            }
            for (int j = 0; j <= v[x].c; j++) {
              if (_f[j][t]) {
                Update(f[j][t], kMod - _f[j][t]);
                if (j < v[x].c) {
                  Update(f[j + 1][t], _f[j][t]);
                }
                Update(v[x].f[i], _f[j][t] * w % kMod * h[v[x].c][j]);
              }
            }
          }
        }
        delete _u;
      }
      delete u;
    }
  }
  v[x].fs[v[x].e.size() + v[x].c] = v[x].f[v[x].e.size() + v[x].c];
  for (int i = v[x].e.size() + v[x].c - 1; i >= 0; i--) {
    v[x].fs[i] = (v[x].fs[i + 1] + v[x].f[i]) % kMod;
  }
  delete g;
}

void T(int x) {
  for (int i : v[x].e) {
    T(i);
  }
  Dp(x);
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
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  CalcH(), DelE(0, 1), DelE2(1), T(1);
  for (int i = 0; i <= n; i++) {
    cout << (v[1].f[i] + kMod) % kMod << '\n';
  }
  return 0;
}
