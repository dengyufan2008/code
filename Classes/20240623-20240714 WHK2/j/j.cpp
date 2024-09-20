#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 5e5 + 1, kMaxM = 1e6 + 2, kMaxL = 5e6 + 1;
struct V {
  int f, c, o, e[26];
} v[kMaxM];
int n, m, k, l, d[kMaxL << 2];
LL c[kMaxL], o[kMaxL];
string s, t[kMaxN];
vector<LL> w[kMaxN];

void Insert(int x) {
  int p = 1;
  for (char c : t[x]) {
    if (!v[p].e[c - 'a']) {
      v[p].e[c - 'a'] = ++k, v[k] = v[0];
    }
    p = v[p].e[c - 'a'];
  }
  v[p].c = 1, v[p].o = x;
}

void CalcFail() {
  static int q[kMaxM];
  q[1] = 1;
  for (int h = 1, t = 1; h <= t; h++) {
    int x = q[h], y, z;
    for (int i = 0; i < 26; i++) {
      y = v[x].e[i];
      if (y) {
        q[++t] = y;
        if (x > 1) {
          for (z = v[x].f; z > 1 && !v[z].e[i]; z = v[z].f) {
          }
          v[y].f = v[z].e[i] ? v[z].e[i] : 1;
        }
      }
    }
  }
  v[1].f = 0;
  for (int i = 1; i <= k; i++) {
    v[q[i]].c += v[v[q[i]].f].c;
    !v[q[i]].o && (v[q[i]].o = v[v[q[i]].f].o);
  }
}

void CalcCO() {
  k = 1, v[1] = v[0];
  for (int i = 1; i <= n; i++) {
    Insert(i);
  }
  CalcFail();
  for (int i = 1, p = 1; i <= l; i++) {
    for (; p && !v[p].e[s[i] - 'a']; p = v[p].f) {
    }
    p = p ? v[p].e[s[i] - 'a'] : 1;
    c[i] = c[i - 1] + v[p].c, o[i] = v[p].o;
  }
}

void CalcW() {
  k = 1, v[1] = v[0];
  for (int i = 1; i <= n; i++) {
    reverse(t[i].begin(), t[i].end()), Insert(i);
  }
  CalcFail();
  for (int i = 1; i <= n; i++) {
    w[i].resize(t[i].size());
    for (int j = 0, p = 1; j < t[i].size(); j++) {
      for (; p && !v[p].e[t[i][j] - 'a']; p = v[p].f) {
      }
      p = p ? v[p].e[t[i][j] - 'a'] : 1;
      w[i][j] = (j ? w[i][j - 1] : 0) + v[p].c;
    }
  }
}

void Init(int p, int l, int r) {
  if (l == r) {
    d[p] = l - t[o[l]].size() + 1;
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  d[p] = min(d[p << 1], d[p << 1 | 1]);
}

int Find(int p, int l, int r, int x) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (d[p << 1 | 1] < x) {
    return Find(p << 1 | 1, mid + 1, r, x);
  } else {
    return Find(p << 1, l, mid, x);
  }
}

int Find(int p, int l, int r, int x, int y) {
  if (r <= y) {
    return d[p] < x ? Find(p, l, r, x) : 0;
  }
  int mid = l + r >> 1, ans = 0;
  if (mid < y) {
    ans = Find(p << 1 | 1, mid + 1, r, x, y);
  }
  if (!ans) {
    ans = Find(p << 1, l, mid, x, y);
  }
  return ans;
}

LL CalcAns(int x, int y) {
  int mid = Find(1, 1, l, x, y);
  if (mid >= x) {
    return c[y] - c[mid] + w[o[mid]][mid - x];
  } else {
    return c[y] - c[x - 1];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s, v[0].f = 1, l = s.size(), s = '~' + s;
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
  }
  CalcCO(), CalcW(), Init(1, 1, l);
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << CalcAns(x, y) << '\n';
  }
  return 0;
}
