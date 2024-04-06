#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 101, kMaxM = kMaxN * 2, kInf = 1e9, kMod = 1e9 + 7;
struct A {
  int x, d;
  bool operator<(const A &a) const {
    return d > a.d;
  }
};
struct V {
  int d[2];
  vector<int> e;
} v[kMaxN];
int t, n, m;
LL ans, f[kMaxM][kMaxM][kMaxN], g[kMaxM][kMaxM][kMaxN];
LL pw[kMaxN], pw2[kMaxN][kMaxN], fact[kMaxN], _fact[kMaxN];
LL d[kMaxN][kMaxN][kMaxN], s[kMaxN][kMaxN];
priority_queue<A> q;

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

void Pre1() {
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j < kMaxN; j++) {
      pw2[i][j] = Pow(pw[i] - 1, j);
    }
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
}

void Pre2() {
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < kMaxN; k++) {
        for (int l = 0; l <= j; l++) {
          LL w = C(j, l) * pw2[i - l][k] % kMod;
          if (l & 1) {
            d[i][j][k] = (d[i][j][k] - w + kMod) % kMod;
          } else {
            d[i][j][k] = (d[i][j][k] + w) % kMod;
          }
        }
      }
    }
  }
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= j; k++) {
        LL w = C(j, k) * Pow(2, (i - k) * (i - k + 1) / 2) % kMod;
        if (k & 1) {
          s[i][j] = (s[i][j] - w + kMod) % kMod;
        } else {
          s[i][j] = (s[i][j] + w) % kMod;
        }
      }
    }
  }
}

void Init() {
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  for (int i = 0; i < n * 2; i++) {
    for (int j = 0; j < n * 2; j++) {
      for (int k = 0; k <= n; k++) {
        f[i][j][k] = g[i][j][k] = 0;
      }
    }
  }
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  ans = 1;
  for (int i = 1; i <= n; i++) {
    v[i].d[0] = (i > 1) * kInf;
    v[i].d[1] = kInf;
  }
}

void Dij() {
  for (q.push({1, 0}); !q.empty();) {
    int x = q.top().x, d = q.top().d;
    q.pop();
    for (int i : v[x].e) {
      if (v[i].d[d & 1 ^ 1] > d + 1) {
        v[i].d[d & 1 ^ 1] = d + 1, q.push({i, d + 1});
      }
    }
  }
}

void Calc1() {
  int c[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    c[v[i].d[0] ^ v[i].d[1] ^ kInf]++;
  }
  for (int i = 1; i <= n; i++) {
    ans = ans * pw2[c[i - 1]][c[i]] % kMod;
  }
}

void Calc2() {
  int c[kMaxM][kMaxM] = {};
  for (int i = 1; i <= n; i++) {
    c[min(v[i].d[0], v[i].d[1])][max(v[i].d[0], v[i].d[1])]++;
  }
  for (int o = 3, i, j; o < n * 2; o += 2) {
    f[0][o][c[0][o]] = 1;
    for (i = 1, j = o - 1; i < j; i++, j--) {
      for (int k = 0; k <= c[i][j]; k++) {
        for (int l = 0; l <= c[i - 1][j + 1]; l++) {
          LL w = d[c[i - 1][j + 1]][l][k];
          g[i][j][k] = (g[i][j][k] + f[i - 1][j + 1][l] * w) % kMod;
        }
      }
      for (int k = 0; k <= c[i][j]; k++) {
        for (int l = k; l <= c[i][j]; l++) {
          LL w = C(c[i][j], l) * C(l, k) % kMod;
          f[i][j][k] = (f[i][j][k] + g[i][j][l] * w) % kMod;
        }
        f[i][j][k] = f[i][j][k] * pw2[c[i - 1][j - 1]][c[i][j] - k] % kMod;
      }
    }
    LL w = 0;
    for (int k = 0; k <= c[j][i]; k++) {  // CHICK
      w = (w + f[j][i][k] * s[c[j][i]][k]) % kMod;
    }
    ans = ans * w % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Pre1(), Pre2(), cin >> t;
  while (t--) {
    Init(), Dij();
    v[1].d[1] == kInf ? Calc1() : Calc2();
    cout << ans << '\n';
  }
  return 0;
}
