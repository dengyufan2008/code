#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 3;
struct V {
  int w, l, r;
} v[kMaxN * 90];
int n, m, k, p[kMaxN], s[kMaxN];

void Init() {
  int a[kMaxN], d[kMaxN];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&d[1], &d[n] + 1, n + 1);
  for (int i = n; i >= 1; i--) {
    p[i] = d[a[i]], d[a[i]] = i;
  }
}

void Tag(int &p, int t) {
  v[++k] = v[p], p = k, v[p].w += t;
}

void Pushdown(int p) {
  if (v[p].w) {
    Tag(v[p].l, v[p].w), Tag(v[p].r, v[p].w), v[p].w = 0;
  }
}

void Copy(int &p, int q1, int q2, int l, int r, int x) {
  if (r <= x || l > x) {
    p = r <= x ? q1 : q2;
    return;
  }
  p = ++k, Pushdown(q1), Pushdown(q2);
  int mid = l + r >> 1;
  if (mid >= x) {
    v[p].r = v[q2].r;
    Copy(v[p].l, v[q1].l, v[q2].l, l, mid, x);
  } else {
    v[p].l = v[q1].l;
    Copy(v[p].r, v[q1].r, v[q2].r, mid + 1, r, x);
  }
}

void Add(int &p, int l, int r, int _l, int _r) {
  v[++k] = v[p], p = k;
  if (l >= _l && r <= _r) {
    return Tag(p, 1);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(v[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    Add(v[p].r, mid + 1, r, _l, _r);
  }
}

int Ask(int p, int l, int r, int x) {
  if (!p) {
    return 0;
  } else if (l == r) {
    return v[p].w;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    return Ask(v[p].l, l, mid, x) + v[p].w;
  } else {
    return Ask(v[p].r, mid + 1, r, x) + v[p].w;
  }
}

void Calc() {
  for (int i = n; i >= 1; i--) {
    Copy(s[i], s[i + 1], s[p[i] + 1], 1, n, p[i] - 1);
    Add(s[i], 1, n, i, p[i] - 1);
  }
}

void Ans() {
  for (int i = 1, x, y, p = 0; i <= m; i++) {
    cin >> x >> y;
    cout << (p = Ask(s[x ^ p], 1, n, y ^ p)) << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc(), Ans();
  return 0;
}
