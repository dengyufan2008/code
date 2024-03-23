#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("dp.in");
ofstream cout("dp.out");

const int kMaxN = 2e5 + 2, kMaxL = 18;
struct Q {
  int h, a[kMaxN], b[kMaxN];

  void Clear(int x) { h = 0, b[0] = x; }

  int Insert(int x, int p) {
    for (; h && (a[h] > x || a[h] == x && b[h] > p); h--) {
    }
    a[++h] = x, b[h] = p;
    return b[h - 1];
  }
} q;
struct T {
  int a[kMaxN];

  void Add(int x) {
    for (int i = x; i < kMaxN; i += i & -i) {
      a[i]++;
    }
  }

  int Ask(int x) {
    int s = 0;
    for (int i = x; i > 0; i -= i & -i) {
      s += a[i];
    }
    return s;
  }

  int Ask(int x, int y) {
    if (x > y) {
      return 0;
    }
    return Ask(y) - Ask(x - 1);
  }
} t;
int lg[kMaxN];
struct V {
  int v[kMaxL][kMaxN], l[kMaxN], r[kMaxN], mx[kMaxN], d[kMaxN];

  int Ask(int x, int y) {
    int z = lg[y - x + 1];
    return max(v[z][x], v[z][y - (1 << z) + 1]);
  }

  void Calc(int n) {
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        v[i][j] = v[i - 1][j];
        if (j + (1 << i) <= n) {
          v[i][j] = max(v[i][j], v[i - 1][j + (1 << i - 1)]);
        }
      }
    }
    q.Clear(0);
    for (int i = 1; i <= n; i++) {
      l[i] = q.Insert(v[0][i], i);
    }
    q.Clear(n + 1);
    for (int i = n; i >= 1; i--) {
      r[i] = q.Insert(v[0][i], i);
    }
    for (int i = 1; i <= n; i++) {
      int s = l[i] == 0 ? kMaxN - 1 : Ask(l[i] + 1, i);
      int t = r[i] == n + 1 ? kMaxN - 1 : Ask(i, r[i] - 1);
      mx[i] = min(s, t), d[i] = i;
    }
  }
} a, b;
int n, m, k;
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a.v[0][i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b.v[0][i];
  }
  for (int i = 1, j = 0; i < kMaxN; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  a.Calc(n), b.Calc(m);
  sort(a.d + 1, a.d + n + 1, [](int i, int j) { return a.v[0][i] < a.v[0][j]; });
  sort(b.d + 1, b.d + m + 1, [](int i, int j) { return b.mx[i] < b.mx[j]; });
  for (int i = 1, j = m; i <= n; i++) {
    for (; j >= 1 && b.mx[b.d[j]] > k - a.v[0][a.d[i]]; j--) {
      t.Add(b.v[0][b.d[j]]);
    }
    ans += t.Ask(k - a.mx[a.d[i]] + 1, k - a.v[0][a.d[i]]);
  }
  cout << ans;
  return 0;
}
