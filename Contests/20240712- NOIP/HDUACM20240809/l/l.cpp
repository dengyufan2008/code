#include <fstream>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 1e5 + 1;
struct V {
  LL mn, t;
} v[kMaxN << 2];
int o, n, m, q, c, a[kMaxN];
LL w;

void Init(int p, int l, int r) {
  v[p].mn = v[p].t = 0;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void Tag(int p, LL t) {
  v[p].mn += t, v[p].t += t;
}

void Pushdown(int p) {
  Tag(p << 1, v[p].t);
  Tag(p << 1 | 1, v[p].t);
  v[p].t = 0;
}

void Add(int p, int l, int r, int x, LL y) {
  if (l >= x) {
    return Tag(p, y);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  Add(p << 1 | 1, mid + 1, r, x, y);
  if (mid >= x) {
    Add(p << 1, l, mid, x, y);
  }
  v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    c = w = 0, cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], c += a[i] > 0, w += a[i] - 1;
    }
    Init(1, 0, n - 1);
    for (int i = 1; i < n; i++) {
      Add(1, 0, n - 1, i, a[i] - 1);
    }
    cin >> q;
    for (int i = 1, x, y; i <= q; i++) {
      cin >> x >> y;
      c += !a[x] && y, c -= a[x] && !y;
      if (x < n) {
        Add(1, 0, n - 1, x, y - a[x]);
      }
      w += y - a[x], a[x] = y;
      cout << (w + m <= 0 || c <= 1 ? -1 : -v[1].mn / m + 1) << '\n';
    }
  }
  return 0;
}
