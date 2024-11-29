#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const LL kMaxN = 5e5 + 1, kInf = 1e16;
int w, d[kMaxN];
LL f[2], g[2];            // 开头位于奇数还是偶数
vector<int> v[kMaxN][2];  // 0:+ 1:-

void Init() {
  static int a[kMaxN], b[kMaxN], c[kMaxN], o[kMaxN];
  cin >> w;
  for (int i = 1; i <= w; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= w; i += 2) {
    b[i] = -b[i];
  }
  for (int i = 1; i <= w; i++) {
    c[i] = abs(b[i]), o[i] = i;
  }
  sort(o + 1, o + w + 1, [](int i, int j) {
    return c[i] < c[j];
  });
  a[o[1]] = c[o[1]] > 0;
  for (int i = 2; i <= w; i++) {
    a[o[i]] = a[o[i - 1]] + (c[o[i]] > c[o[i - 1]]);
  }
  for (int i = 1; i <= w; i++) {
    if (b[i] < 0) {
      v[a[i]][1].push_back(i);
      a[i] = -a[i];
    } else {
      v[a[i]][0].push_back(i);
    }
  }
}

void Add(int x, int y) {
  for (int i = x; i <= w; i += i & -i) {
    d[i] += y;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

void SolveAAA(vector<int> &a, vector<int> &b, int n, int m, int c, bool o) {
  LL s = 0, mn = 0;
  for (int i = 0; i < m; i++) {
    s += Ask(a[i + 1]) << 1, s += Ask(b[i]) << 1, s -= c << 1;
    s -= a[i + 1] >= b[i], s += b[i] >= a[i + 1], mn = min(mn, s);
  }
  LL h = f[o ^ 1] + mn;
  h += Ask(a[0]), Add(a[0], 1);
  h += c + 1 - Ask(a[1]), Add(a[1], 1);
  for (int i = 0; i < m; i++) {
    h += c + (i + 1 << 1) - Ask(b[i]), Add(b[i], 1);
    h += c + (i + 1 << 1 | 1) - Ask(a[i + 2]), Add(a[i + 2], 1);
  }
  Add(a[0], -1), Add(a[1], -1);
  for (int i = 0; i < m; i++) {
    Add(b[i], -1), Add(a[i + 2], -1);
  }
  g[o] = min(g[o], h);
}

void SolveABB(vector<int> &a, vector<int> &b, int n, int m, int c, bool o) {
  LL s = 0, mn = 0;
  for (int i = 0; i < n; i++) {
    s += Ask(b[i]) << 1, s += Ask(a[i]) << 1, s -= c << 1;
    s -= b[i] >= a[i], s += a[i] >= b[i], mn = min(mn, s);
  }
  LL h = f[o] + mn;
  for (int i = 0; i < n; i++) {
    h += c + (i << 1) - Ask(b[i]), Add(b[i], 1);
    h += c + (i << 1 | 1) - Ask(a[i]), Add(a[i], 1);
  }
  for (int i = 0; i < n; i++) {
    Add(b[i], -1), Add(a[i], -1);
  }
  g[o] = min(g[o], h);
}

void SolveABA_AAB(vector<int> &a, vector<int> &b, int n, int m, int c, bool o) {
  LL s = 0, mn0 = 0, mn1 = kInf;
  for (int i = 0; i < n; i++) {
    s += Ask(a[i]) << 1, s -= c, mn1 = min(mn1, s);
    if (i < m) {
      s += Ask(b[i]) << 1, s -= c, mn0 = min(mn0, s);
    }
  }
  LL h = 0;
  h += c - Ask(a[0]), Add(a[0], 1);
  for (int i = 0; i < m; i++) {
    h += c + (i << 1 | 1) - Ask(b[i]), Add(b[i], 1);
    h += c + (i + 1 << 1) - Ask(a[i + 1]), Add(a[i + 1], 1);
  }
  Add(a[0], -1);
  for (int i = 0; i < m; i++) {
    Add(b[i], -1), Add(a[i + 1], -1);
  }
  g[o] = min(g[o], min(f[o] + mn0 + h, f[o ^ 1] + mn1 + h));
}

void SolveOdd(int i, int n, int m, int c) {
  if (c & 1) {
    if (n - m == 0) {
      v[i][0].push_back(w), v[i][1].push_back(w);
      SolveABA_AAB(v[i][0], v[i][1], n + 1, m, c, 1);
      SolveABA_AAB(v[i][1], v[i][0], m + 1, n, c, 0);
    }
  } else {
    if (n - m == 1) {
      v[i][0].push_back(w), v[i][1].push_back(w);
      SolveAAA(v[i][0], v[i][1], n, m, c, 1);
      SolveABB(v[i][1], v[i][0], m + 1, n, c, 0);
    } else if (n - m == -1) {
      v[i][0].push_back(w), v[i][1].push_back(w);
      SolveABB(v[i][0], v[i][1], n + 1, m, c, 1);
      SolveAAA(v[i][1], v[i][0], m + 1, n, c, 0);
    }
  }
}

void SolveEven(int i, int n, int m, int c) {
  if (c & 1) {
    if (n - m == 1) {
      SolveABA_AAB(v[i][0], v[i][1], n, m, c, 1);
    } else if (n - m == -1) {
      SolveABA_AAB(v[i][1], v[i][0], m, n, c, 0);
    }
  } else {
    if (n - m == 0) {
      SolveABB(v[i][0], v[i][1], n, m, c, 1);
      SolveABB(v[i][1], v[i][0], m, n, c, 0);
    } else if (n - m == 2) {
      SolveAAA(v[i][0], v[i][1], n, m, c, 1);
    } else if (n - m == -2) {
      SolveAAA(v[i][1], v[i][0], m, n, c, 0);
    }
  }
}

void Calc() {
  int c = v[0][0].size();
  for (int i : v[0][0]) {
    Add(i, 1);
  }
  for (int i = 1; i <= w && v[i][0].size() + v[i][1].size(); i++) {
    int n = v[i][0].size(), m = v[i][1].size();
    g[0] = g[1] = kInf;
    if (c + n + m & 1) {
      SolveOdd(i, n, m, c);
    } else {
      SolveEven(i, n, m, c);
    }
    for (int j = 0; j < n; j++) {
      Add(v[i][0][j], 1);
    }
    for (int j = 0; j < m; j++) {
      Add(v[i][1][j], 1);
    }
    c += n + m, f[0] = g[0], f[1] = g[1];
  }
  cout << (f[1] == kInf ? -1 : f[1]) << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc();
  return 0;
}
