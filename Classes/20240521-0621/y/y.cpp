#include <fstream>

using namespace std;

ifstream cin("y.in");
ofstream cout("y.out");

const int kMaxN = 2.5e5 + 2, kInf = 1e9;
int u, n, m, a[kMaxN];
int l[kMaxN][2], r[kMaxN][2];
pair<int, int> f[kMaxN][2], g[kMaxN][2];

class H {
  int o, h, t;
  pair<int, int> q[kMaxN];

 public:
  void Init(int _o) {
    o = _o, h = 1, t = 0;
  }

  void Insert(int w, int x) {
    for (; t >= h && q[t].first * o <= w * o; t--) {
    }
    q[++t] = {w, x};
  }

  pair<int, int> Ask(int x) {
    for (; h <= t && q[h].second * o > x * o; h++) {
    }
    return h <= t ? q[h] : make_pair(-o * kInf, -o * kInf);
  }
} h[2];

void Init() {
  char c = '0';
  cin >> n >> m >> m;
  for (int i = 1; i <= n; i++) {
    cin >> c;
    a[i] = (c == '0') + (c == '1') * 2 - 1;
    a[i] == 1 && m++;
  }
  a[0] = a[n + 1] = -1;
  l[0][0] = l[0][1] = -1;
  for (int i = 1; i <= n; i++) {
    l[i][0] = l[i - 1][0];
    l[i][1] = l[i - 1][1];
    ~a[i] && (l[i][a[i]] = i);
  }
  r[n + 1][0] = r[n + 1][1] = n + 2;
  for (int i = n; i >= 1; i--) {
    r[i][0] = r[i + 1][0];
    r[i][1] = r[i + 1][1];
    ~a[i] && (r[i][a[i]] = i);
  }
}

bool Check(int x) {
  h[0].Init(-1), h[1].Init(-1);
  h[0].Insert(0, 0), h[1].Insert(0, 0);
  f[0][0] = f[0][1] = {0, 0};
  for (int i = 1; i <= n + 1; i++) {
    f[i][0] = h[1].Ask(max(i - x, l[i - 1][0] + 1));
    f[i][1] = h[0].Ask(max(i - x, l[i - 1][1] + 1));
    f[i][0].first += i - 1, f[i][1].first += 1;
    if (a[i] == 1) {
      f[i][0] = {kInf, kInf};
    } else if (a[i] == 0) {
      f[i][1] = {kInf, kInf};
    }
    h[0].Insert(f[i][0].first, i);
    h[1].Insert(f[i][1].first - i, i);
  }
  h[0].Init(1), h[1].Init(1);
  h[0].Insert(0, n + 1), h[1].Insert(n + 1, n + 1);
  g[n + 1][0] = g[n + 1][1] = {0, n + 1};
  for (int i = n; i >= 0; i--) {
    g[i][0] = h[1].Ask(min(i + x, r[i + 1][0] - 1));
    g[i][1] = h[0].Ask(min(i + x, r[i + 1][1] - 1));
    g[i][0].first -= i + 1, g[i][1].first += 1;
    if (a[i] == 1) {
      g[i][0] = {-kInf, -kInf};
    } else if (a[i] == 0) {
      g[i][1] = {-kInf, -kInf};
    }
    h[0].Insert(g[i][0].first, i);
    h[1].Insert(g[i][1].first + i, i);
  }
  int s = min(f[n + 1][0].first, f[n + 1][1].first - 1);
  int t = max(g[0][0].first, g[0][1].first - 1);
  return s <= m && t >= m;
}

void Print(int x) {
  int s = 0, t = 1;
  bool so = 0, to = 1, ans[kMaxN] = {};
  for (int i = 0; i <= n; i++) {
    if (a[i] != 1 && a[i + 1] != 0 && g[i][0].first >= 0 &&
        f[i + 1][1].first + g[i][0].first == m + 1) {
      s = i + 1, so = 1, t = i, to = 0;
      break;
    }
    if (a[i] != 0 && a[i + 1] != 1 && g[i][1].first >= 0 &&
        f[i + 1][0].first + g[i][1].first == m + 1) {
      s = i + 1, so = 0, t = i, to = 1;
      break;
    }
  }
  for (; s > 1; s = f[s][so].second, so ^= 1) {
    for (int i = f[s][so].second; i < s; i++) {
      ans[i] = !so;
    }
  }
  for (; t < n; t = g[t][to].second, to ^= 1) {
    for (int i = g[t][to].second; i > t; i--) {
      ans[i] = !to;
    }
  }
  cout << x << '\n';
  for (int i = 1; i <= n; i++) {
    cout << ans[i];
  }
  cout << '\n';
}

void CalcAns() {
  int x = 1, y = n;
  while (x <= y) {
    int mid = x + y >> 1;
    if (Check(mid)) {
      y = mid - 1;
    } else {
      x = mid + 1;
    }
  }
  Check(x), Print(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    Init(), CalcAns();
  }
  return 0;
}
