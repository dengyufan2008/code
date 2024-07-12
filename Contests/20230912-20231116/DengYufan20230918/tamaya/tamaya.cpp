#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 5e5 + 1, kMaxM = 19;
struct Pair {
  int first, second;
} b[kMaxN], p[kMaxM][kMaxN];
struct V {
  int d, l, r;
} v[kMaxN * 51];
int n, m, q, o, s[kMaxN], d[kMaxN << 2];

int Read() {
  int x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

int Max(int x, int y) {
  return x < y ? y : x;
}

void ChangeVal(int &p, int l, int r, int _l, int _r, int k) {
  v[++o] = v[p], p = o;
  if (l >= _l && r <= _r) {
    v[p].d = k;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    ChangeVal(v[p].l, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    ChangeVal(v[p].r, mid + 1, r, _l, _r, k);
  }
}

int AskVal(int p, int l, int r, int x) {
  if (l == r) {
    return v[p].d;
  }
  int mid = l + r >> 1;
  return Max(v[p].d, mid >= x ? AskVal(v[p].l, l, mid, x) : AskVal(v[p].r, mid + 1, r, x));
}

void ChangeMax(int p, int l, int r, int x, int k) {
  if (l == r) {
    d[p] = k;
    return;
  }
  int mid = l + r >> 1;
  mid >= x ? ChangeMax(p << 1, l, mid, x, k) : ChangeMax(p << 1 | 1, mid + 1, r, x, k);
  d[p] = Max(d[p << 1], d[p << 1 | 1]);
}

int AskMax(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return d[p];
  }
  int mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans = Max(ans, AskMax(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = Max(ans, AskMax(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

int main() {
  freopen("tamaya.in", "r", stdin);
  freopen("tamaya.out", "w", stdout);
  n = Read(), m = Read();
  for (int i = 1, x; i <= n; i++) {
    ChangeMax(1, 1, n, i, Read());
  }
  for (int i = 1; i <= m; i++) {
    b[i].first = Read(), b[i].second = Read();
  }
  for (int i = 1; i <= m; i++) {
    p[0][i].first = AskVal(s[i - 1], 1, n, b[i].first);
    p[0][i].second = AskVal(s[i - 1], 1, n, b[i].second);
    ChangeVal(s[i] = s[i - 1], 1, n, b[i].first, b[i].second, i);
  }
  for (int i = 1; i < kMaxM; i++) {
    for (int j = 1; j <= m; j++) {
      p[i][j].first = p[i - 1][p[i - 1][j].first].first;
      p[i][j].second = p[i - 1][p[i - 1][j].second].second;
    }
  }
  q = Read();
  for (int i = 1, o, x, y; i <= q; i++) {
    o = Read();
    if (o == 1) {
      x = Read(), y = Read();
      ChangeMax(1, 1, n, x, y);
    } else {
      x = Read(), y = Read(), o = Read();
      int c = AskVal(s[y], 1, n, o), l = c >= x ? b[c].first : o, r = c >= x ? b[c].second : o;
      for (int j = kMaxM - 1, _l = c, _r = c; j >= 0; j--) {
        if (p[j][_l].first >= x) {
          _l = p[j][_l].first, l = b[_l].first;
        }
        if (p[j][_r].second >= x) {
          _r = p[j][_r].second, r = b[_r].second;
        }
      }
      printf("%d\n", AskMax(1, 1, n, l, r));
    }
  }
  return 0;
}
