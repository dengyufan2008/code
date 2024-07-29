#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1;
struct D {
  int l, r;
  LL w, t;
} d[kMaxN * 20];
struct V {
  int c, w, s;
  LL f;
  vector<int> e;
} v[kMaxN];
int t, n, m;

void Change(int &p, int l, int r, int x, int y) {
  d[++m] = d[0], p = m;
  if (l == r) {
    d[p].w = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(d[p].l, l, mid, x, y);
  } else {
    Change(d[p].r, mid + 1, r, x, y);
  }
}

void Tag(int p, LL t) {
  if (p) {
    d[p].w += t, d[p].t += t;
  }
}

void Pushdown(int p) {
  if (d[p].t) {
    Tag(d[p].l, d[p].t), Tag(d[p].r, d[p].t), d[p].t = 0;
  }
}

void Merge(int &p, int q, int l, int r, LL x, LL y, LL &w) {
  if (!p) {
    return Tag(p = q, x);
  } else if (!q) {
    return Tag(p, y);
  } else if (l == r) {
    w = max(w, d[p].w + d[q].w);
    d[p].w = max(d[p].w + y, d[q].w + x);
    return;
  }
  Pushdown(p), Pushdown(q);
  int mid = l + r >> 1;
  Merge(d[p].l, d[q].l, l, mid, x, y, w);
  Merge(d[p].r, d[q].r, mid + 1, r, x, y, w);
}

void T(int f, int x) {
  LL w = 0;
  Change(v[x].s, 1, n, v[x].c, v[x].w);
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].f += v[i].f, w += v[i].f;
      Merge(v[x].s, v[i].s, 1, n, v[x].f - v[i].f, v[i].f, w);
    }
  }
  v[x].f = max(v[x].f, w);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    m = 0;
    for (int i = 1; i <= n; i++) {
      v[i].s = v[i].f = 0, v[i].e.clear();
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].c;
    }
    for (int i = 1; i <= n; i++) {
      cin >> v[i].w;
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    T(0, 1), cout << v[1].f << '\n';
  }
  return 0;
}
