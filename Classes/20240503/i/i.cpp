#include <fstream>
#include <map>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 101, kMaxM = 2101, kMod = 998244353;
struct A {
  int c, f[3][3][2];

  A() {}
  A(int _c, int _f) : c(_c) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        f[i][j][0] = f[i][j][1] = -1;
      }
    }
    f[0][0][0] = _f;
  }

  bool operator<(const A &x) const {
    if (c != x.c) {
      return c < x.c;
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (f[i][j][0] != x.f[i][j][0]) {
          return f[i][j][0] < x.f[i][j][0];
        } else if (f[i][j][1] != x.f[i][j][1]) {
          return f[i][j][1] < x.f[i][j][1];
        }
      }
    }
    return 0;
  }

  bool C() {
    if (c == 7) {
      return 1;
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (f[i][j][1] == 4) {
          return 1;
        }
      }
    }
    return 0;
  }
} q[kMaxM];
int n, m, a[kMaxN], e[kMaxM][5];
LL ans, f[kMaxN][kMaxN * 4][kMaxM], fact[kMaxN * 4], _fact[kMaxN * 4];
map<A, int> s;

void CheckMax(int &x, int y) { x = max(x, min(y, 4)); }
void Add(LL &x, LL y) { x = (x + y) % kMod; }

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

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN * 4; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN * 4 - 1] = Pow(fact[kMaxN * 4 - 1]);
  for (int i = kMaxN * 4 - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1, x, y; i <= 13; i++) {
    cin >> x >> y, a[x]++;
  }
  e[1][0] = e[1][1] = e[1][2] = e[1][3] = e[1][4] = 1;
  q[1] = A(7, -1), s[A(7, -1)] = 1;
  q[2] = A(0, 0), s[A(0, 0)] = 2;
  for (int i = m = 2; i <= m; i++) {
    A x = q[i];
    for (int t = 0; t < 5; t++) {
      A y = A(x.c + (t > 1), -1);
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3 && k <= t - i - j; k++) {
            int w = t - i - j - k;
            if (~x.f[i][j][1]) {
              CheckMax(y.f[j][k][1], x.f[i][j][1] + i + w / 3);
            }
            if (~x.f[i][j][0]) {
              CheckMax(y.f[j][k][0], x.f[i][j][0] + i + w / 3);
              if (w > 1) {
                CheckMax(y.f[j][k][1], x.f[i][j][0] + i + (w - 2) / 3);
              }
            }
          }
        }
      }
      if (y.C()) {
        e[s[x]][t] = 1;
      } else if (!s.count(y)) {
        e[s[x]][t] = s[y] = ++m, q[m] = y;
      } else {
        e[s[x]][t] = s[y];
      }
    }
  }
  f[0][0][2] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i * 4; j++) {
      for (int k = 1; k <= m; k++) {
        for (int o = a[i + 1]; o < 5; o++) {
          Add(f[i + 1][j + o][e[k][o]], f[i][j][k] * C(4 - a[i + 1], o - a[i + 1]));
        }
      }
    }
  }
  for (int i = 13; i <= n * 4; i++) {
    LL w = 0;
    for (int j = 2; j <= m; j++) {
      Add(w, f[n][i][j]);
    }
    Add(ans, w * fact[i - 13] % kMod * fact[n * 4 - i]);
  }
  cout << ans * _fact[n * 4 - 13] % kMod << '\n';
  return 0;
}
