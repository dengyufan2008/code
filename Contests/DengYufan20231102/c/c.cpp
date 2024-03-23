#include <iostream>
#define LL long long
#define PLI pair<LL, int>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2e5 + 1;
struct V {
  LL w;
  int p, t;
} v[kMaxN << 2];
int n, m;
char c;
string s;

int W(int x, int y) {
  if (x == y) {
    return 0;
  } else if (x + 3 == y || (x ^ (x & -x)) == y) {
    return -1;
  }
  return 1;
}

void Init(int p, int l, int r) {
  v[p].p = l;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
}

void Pushdown(int p) {
  if (v[p].t) {
    v[p << 1].w += v[p].t, v[p << 1].t += v[p].t;
    v[p << 1 | 1].w += v[p].t, v[p << 1 | 1].t += v[p].t;
    v[p].t = 0;
  }
}

void Change(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p].w += k, v[p].t += k;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Change(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Change(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  if (v[p << 1].w <= v[p << 1 | 1].w) {
    v[p].w = v[p << 1].w, v[p].p = v[p << 1].p;
  } else {
    v[p].w = v[p << 1 | 1].w, v[p].p = v[p << 1 | 1].p;
  }
}

PLI Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return {v[p].w, v[p].p};
  }
  Pushdown(p);
  int mid = l + r >> 1;
  PLI ans = {1145141919810, 0};
  if (mid >= _l) {
    ans = min(ans, Ask(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = min(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s;
  s = '~' + s, Init(1, 1, n);
  for (int i = 2; i <= n; i++) {
    Change(1, 1, n, i, n, W(s[i - 1], s[i]));
  }
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> c;
      if (x > 1) {
        Change(1, 1, n, x, n, W(s[x - 1], c) - W(s[x - 1], s[x]));
      }
      if (x < n) {
        Change(1, 1, n, x + 1, n, W(c, s[x + 1]) - W(s[x], s[x + 1]));
      }
      s[x] = c;
    } else {
      cin >> y;
      cout << s[Ask(1, 1, n, x, y).second] << '\n';
    }
  }
  return 0;
}
