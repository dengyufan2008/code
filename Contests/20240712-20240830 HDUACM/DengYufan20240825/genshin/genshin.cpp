#include <fstream>

using namespace std;

ifstream cin("genshin.in");
ofstream cout("genshin.out");

struct A {
  int a[5][5];
};
const int kMaxN = 2e5 + 1, kMaxM = 524286;
const int kMod = 998244853, kInv2 = 499122427, kInv4 = 748683640;
const int kLeft[5] = {0, 0, 2, 2, 4};
const A one = {{{1, 0, 0, 0, 0},
                {0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 0, 1}}};
const A same = {{{kInv2, kInv2, 0, kInv4, kInv4},
                 {0, 1, 0, kInv2, kInv2},
                 {0, 0, kInv4, kInv2, kInv4},
                 {0, 0, 0, 1, kInv2},
                 {0, 0, 0, 0, 1}}};
const A diff = {{{1, 0, 0, 0, 0},
                 {kInv2, kInv2, 0, kInv4, kInv4},
                 {0, 0, kInv2, 0, 0},
                 {0, 0, kInv4, kInv2, kInv4},
                 {0, 0, 0, 0, 1}}};
int n, m, ans, w[26], a[kMaxN];

void Mul(A &x, A &y, A &z) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < kLeft[i]; j++) {
      x.a[i][j] = 0;
    }
  }
  x.a[4][4] = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = kLeft[i]; j < 5; j++) {
      long long s = 0;
      for (int k = 0; k < 5; k++) {
        s += 1LL * y.a[i][k] * z.a[k][j];
      }
      x.a[i][j] = s % kMod;
    }
  }
}

class Seg {
  A v[kMaxM];

  void Init(int p, int l, int r, int c) {
    if (l == r) {
      v[p] = a[l] == c ? same : diff;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid, c);
    Init(p << 1 | 1, mid + 1, r, c);
    Mul(v[p], v[p << 1], v[p << 1 | 1]);
  }

  void Change(int p, int l, int r, int x, bool o) {
    if (l == r) {
      v[p] = o ? same : diff;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, o);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, o);
    }
    Mul(v[p], v[p << 1], v[p << 1 | 1]);
  }

 public:
  void Init(int c) { Init(1, 1, n, c); }
  void Change(int x, bool o) { Change(1, 1, n, x, o); }
  int Ask() { return v[1].a[0][4]; }
} seg[26];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c, a[i] = c - 'a';
  }
  for (int c = 0; c < 26; c++) {
    seg[c].Init(c);
    w[c] = seg[c].Ask();
    ans = (ans + w[c]) % kMod;
  }
  for (int i = 1, x; i <= m; i++) {
    static char c;
    cin >> x >> c;
    if (a[x] != c - 'a') {
      for (int o = 0; o < 2; o++) {
        ans = (ans - w[a[x]] + kMod) % kMod;
        seg[a[x]].Change(x, o), w[a[x]] = seg[a[x]].Ask();
        ans = (ans + w[a[x]]) % kMod;
        a[x] = c - 'a';
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
