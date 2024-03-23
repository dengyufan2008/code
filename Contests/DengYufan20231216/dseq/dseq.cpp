#include <cmath>
#include <fstream>

using namespace std;

ifstream cin("dseq.in");
ofstream cout("dseq.out");

const int kMaxN = 2.5e5 + 1, kMaxL = 7, kInf = 2e9;
struct A {
  int mn, mx, c;
};
struct B {
  int p, l;
  bool operator<(const B &b) const {
    return p < b.p;
  }
};
struct V {
  int wt, ct;
  A a;
  B b;
} v[kMaxL][kMaxN << 2];
int n, m;

int D(int x) {
  return x == 1 ? 1 : D(sqrt(x)) + 1;
}

A Merge(A x, A y) {
  return {min(x.mn, y.mn), max(x.mx, y.mx), x.c + y.c};
}

void Init(int p, int l, int r) {
  for (int i = 1; i < kMaxL; i++) {
    v[i][p].a = {kInf, -kInf, 0};
  }
  if (l != r) {
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }
}

void TagW(int p, int i, int w) {
  v[i][p].a.mn += w, v[i][p].a.mx += w, v[i][p].wt += w;
}

void TagC(int p, int i, int c) {
  v[i][p].a.c += c, v[i][p].ct += c;
}

void Pushdown(int p, int l, int r, int i) {
  int mid = l + r >> 1;
  if (v[i][p].wt) {
    TagW(p << 1, i, v[i][p].wt);
    TagW(p << 1 | 1, i, v[i][p].wt);
    v[i][p].wt = 0;
  }
  if (v[i][p].ct) {
    TagC(p << 1, i, v[i][p].ct);
    TagC(p << 1 | 1, i, v[i][p].ct);
    v[i][p].ct = 0;
  }
}

void Pushup(int p, int i) {
  v[i][p].a = Merge(v[i][p << 1].a, v[i][p << 1 | 1].a);
  v[i][p].b = max(v[i][p << 1].b, v[i][p << 1 | 1].b);
}

void ChangeA(int p, int l, int r, int x, int y, int i) {
  if (l == r) {
    v[i][p].b = {l, 1}, v[i][p].a = {x, x, 1};
    return;
  }
  Pushdown(p, l, r, i);
  int mid = l + r >> 1;
  if (mid >= x) {
    ChangeA(p << 1, l, mid, x, y, i);
  } else {
    ChangeA(p << 1 | 1, mid + 1, r, x, y, i);
  }
  Pushup(p, i);
}

B Ask(int p, int l, int r, int x, int i) {
  if (r <= x) {
    return v[i][p].b;
  }
  Pushdown(p, l, r, i);
  int mid = l + r >> 1;
  if (mid <= x) {
    B ans = Ask(p << 1 | 1, mid + 1, r, x, i);
    return max(ans, v[i][p << 1].b);
  }
  return Ask(p << 1, l, mid, x, i);
}

void ChangeB(int p, int l, int r, int x, int y, int i) {
  if (l == r) {
    v[i][p].b.p = x, v[i][p].b.l = y;
    return;
  }
  Pushdown(p, l, r, i);
  int mid = l + r >> 1;
  if (mid >= x) {
    ChangeB(p << 1, l, mid, x, y, i);
  } else {
    ChangeB(p << 1 | 1, mid + 1, r, x, y, i);
  }
  Pushup(p, i);
}

void Split(int x) {
  for (int i = 1; i < kMaxL; i++) {
    B p = Ask(1, 1, n, x, i);
    ChangeB(1, 1, n, p.p, x - p.p, i);
    ChangeB(1, 1, n, x, p.l - x + p.p, i);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  Init(1, 1, n);
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    ChangeA(1, 1, n, i, x, D(x));
  }
  for (int i = 1, o, l, r, x; i <= m; i++) {
    cin >> o >> l >> r;
    if (o == 1) {
      cin >> x;
      Split(l), Split(r + 1);
    } else if (o == 2) {
      cin >> x;
    } else {
      ;
    }
  }
  return 0;
}
