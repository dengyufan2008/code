#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 3001;
struct A {
  bool b;
  int l, r;
} a[2][kMaxN][kMaxN];
int o, n[2], k, ans, l[kMaxN], r[kMaxN], d[kMaxN];
char ch;
class H {
  int h, t;
  int mx, suf;
  pair<int, int> q[kMaxN];

 public:
  void Clear(bool _mx, bool _suf) {
    h = 1, t = 0, mx = _mx ? 1 : -1, suf = _suf ? 1 : -1;
  }
  void Insert(int w, int x) {
    for (; t >= h && q[t].first * mx <= w * mx; t--) {
    }
    q[++t] = {w, x};
  }
  int Ask(int x) {
    for (; h <= t && q[h].second * suf <= x * suf; h++) {
    }
    return h <= t ? q[h].first : (mx == 1 ? 0 : kMaxN);
  }
} h1, h2;

bool C(int x, int y) {
  bool p = 0, q = 1;
  int ans = 0;
  x < y ? swap(p, q), swap(x, y) : void();
  for (int i = 1; i <= n[q]; i++) {
    d[i] = 0;
  }
  for (int i = x; i <= n[p]; i += x) {
    h1.Clear(1, 0), h1.Insert(i + 1, n[q] + 1);
    h2.Clear(0, 0), h2.Insert(i - 1, n[q] + 1);
    for (int j = n[q]; j >= 1; j--) {
      h1.Insert(a[p][i][j].l + 1, j);
      h2.Insert(a[p][i][j].r - 1, j);
      l[j] = h1.Ask(j + y);
      r[j] = h2.Ask(j + y);
    }
    h1.Clear(0, 1), h2.Clear(1, 1);
    for (int j = 1; j <= n[q]; j++) {
      if (r[j] - l[j] + 1 >= x) {
        h1.Insert(l[j], j);
        h2.Insert(r[j], j);
      }
      l[j] = max(h1.Ask(j - y), d[j] + 1);
      r[j] = h2.Ask(j - y);
      d[j] = max(d[j], r[j]);
      ans += max(r[j] - l[j] + 1, 0);
    }
  }
  return ans < k;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n[0] >> n[1] >> k;
    for (int i = 1; i <= n[0]; i++) {
      for (int j = 1; j <= n[1]; j++) {
        cin >> ch, a[0][i][j].b = a[1][j][i].b = ch == '1';
      }
    }
    for (int i = 1; i <= n[0]; i++) {
      for (int j = 1; j <= n[1]; j++) {
        a[0][i][j].l = i == 1 ? 0 : a[0][i - 1][j].l;
        a[1][j][i].l = j == 1 ? 0 : a[1][j - 1][i].l;
        if (a[0][i][j].b) {
          a[0][i][j].l = i, a[1][j][i].l = j;
        }
      }
    }
    for (int i = n[0]; i >= 1; i--) {
      for (int j = n[1]; j >= 1; j--) {
        a[0][i][j].r = i == n[0] ? n[0] + 1 : a[0][i + 1][j].r;
        a[1][j][i].r = j == n[1] ? n[1] + 1 : a[1][j + 1][i].r;
        if (a[0][i][j].b) {
          a[0][i][j].r = i, a[1][j][i].r = j;
        }
      }
    }
    for (int i = 1, j = n[1]; i <= n[0]; i++) {
      for (; j >= 1 && C(i, j); j--) {
      }
      ans += j;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
