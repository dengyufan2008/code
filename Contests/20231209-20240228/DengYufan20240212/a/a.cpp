#include <algorithm>
#include <fstream>
#define ULL unsigned long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 1;
struct E {
  int x, y, t;
} e[kMaxN << 1];
struct V {
  ULL n, c, s;
  int t;
} v[kMaxN << 2];
int n, q;
ULL m, ans;

void Init(int p, int l, int r) {
  v[p].n = r - l + 1, v[p].c = v[p].n * m, v[p].s = v[p].c * m;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void Tag(int p, int t) {
  v[p].c = v[p].n * t, v[p].s = v[p].c * t, v[p].t = t;
}

void Pushdown(int p) {
  if (v[p].t) {
    Tag(p << 1, v[p].t);
    Tag(p << 1 | 1, v[p].t);
    v[p].t = 0;
  }
}

void Pushup(int p) {
  v[p].n = v[p << 1].n + v[p << 1 | 1].n;
  v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  v[p].s = v[p << 1].s + v[p << 1 | 1].s;
}

void Fill(int p, int l, int r, int _l, int _r, int t) {
  if (_l == 1 && _r == v[p].n) {
    ans += v[p].n * (t - 1) * (t - 1) * 4 - v[p].c * (t - 1) * 8 + v[p].s * 4;
    Tag(p, t);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1, c = v[p << 1].n;
  if (_l <= v[p << 1].n) {
    Fill(p << 1, l, r, _l, min(_r, c), t);
  }
  if (_r > v[p << 1].n) {
    Fill(p << 1 | 1, mid + 1, r, max(_l - c, 1), _r - c, t);
  }
  Pushup(p);
}

void Delete(int p, int l, int r, int x, int t) {
  if (l == r) {
    ans += ((v[p].c - t) * 2 + 1) * ((v[p].c - t) * 2 + 1);
    v[p].n = v[p].c = v[p].s = 0;
    return;
  }
  int mid = l + r >> 1;
  Pushdown(p);
  if (mid >= x) {
    Delete(p << 1, l, mid, x, t);
  } else {
    Delete(p << 1 | 1, mid + 1, r, x, t);
  }
  Pushup(p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  n--;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].t;
    e[i].x = i;
  }
  cin >> ans >> ans >> ans;
  q += n - 1, ans = 0;
  for (int i = n + 1; i <= q; i++) {
    cin >> e[i].t >> e[i].x >> e[i].y;
    e[i].y--;
  }
  sort(e + 1, e + q + 1, [](E i, E j) {
    return i.t > j.t || i.t == j.t && i.y < j.y;
  });
  Init(1, 1, n);
  for (int i = 1; i <= q; i++) {
    if (e[i].y) {
      Fill(1, 1, n, e[i].x, e[i].y, e[i].t);
    } else {
      Delete(1, 1, n, e[i].x, e[i].t);
    }
  }
  cout << ans << '\n';
  return 0;
}
