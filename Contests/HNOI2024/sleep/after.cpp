#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("sleep.in");
ofstream cout("sleep.out");

const int kMaxN = 1.5e6 + 1;
struct A {
  int o, r, s;
  vector<int> e;
} a[kMaxN];
struct V {
  int l, r, mn, mx, t, pl, pr, c;
  LL ans;
};
int n, m;
class H {
  V v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].l = v[p].pl = l, v[p].r = v[p].pr = r;
    if (l < r) {
      int mid = l + r >> 1;
      Init(p << 1, l, mid);
      Init(p << 1 | 1, mid + 1, r);
    }
  }

  void Tag(int p, int k) {
    v[p].mn += k, v[p].mn += k, v[p].t += k, v[p].ans += 1LL * v[p].c * k;
  }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t);
      v[p].t = 0;
    }
  }

  int Max(int p, int l, int r) {
    if (v[p].l >= l && v[p].r <= r) {
      return v[p].mx;
    }
    Pushdown(p);
    int mid = v[p].l + v[p].r >> 1, ans = 0;
    if (mid >= l) {
      ans = max(ans, Max(p << 1, l, r));
    }
    if (mid < r) {
      ans = max(ans, Max(p << 1 | 1, l, r));
    }
    return ans;
  }

  LL Find(int p, int &w) {
    if (v[p].l == v[p].r) {
      return v[p].mx >= w ? w = v[p].mx : 0;
    }
    Pushdown(p);
    int mid = v[p].l + v[p].r >> 1;
    LL ans = 0;
    if (v[p << 1].mx < w) {
      ans = Find(p << 1 | 1, w);
    } else {
      ans = Find(p << 1, w) + v[p].ans;
      w = max(w, v[p << 1 | 1].mx);
    }
    return ans;
  }

  LL Calc(int p, int l, int r, int &w) {
    if (v[p].l >= l && v[p].r <= r) {
      return Find(p, w);
    }
    Pushdown(p);
    int mid = v[p].l + v[p].r >> 1;
    LL ans = 0;
    if (mid >= l) {
      ans += Calc(p << 1, l, r, w);
    }
    if (mid < r) {
      ans += Calc(p << 1 | 1, l, r, w);
    }
    return ans;
  }

  V Merge(V x, V y) {
    V ans = {x.l, y.r, min(x.mn, y.mn), max(x.mx, y.mx), 0};
    if (x.mn < y.mn) {
      ans.pl = x.pl, ans.pr = x.pr, ans.c = x.c, ans.ans = x.ans;
    } else if (x.mn > y.mn) {
      ans.pl = y.pl, ans.pr = y.pr, ans.c = y.c, ans.ans = y.ans;
    } else {
      ans.pl = x.pl, ans.pr = y.pr, ans.c = x.c + y.c, ans.ans = x.ans + y.ans;
      if (x.pr + 1 <= y.pl - 1) {
        ans.c++, ans.ans += Max()
      }
    }
    return ans;
  }

  V Ask(int p, int l, int r) {
    if (v[p].l >= l && v[p].r <= r) {
      return v[p];
    }
    Pushdown(p);
    int mid = v[p].l + v[p].r >> 1;
    if (mid >= l && mid < r) {
      V x = Ask(p << 1, l, r);
      V y = Ask(p << 1 | 1, l, r);
      return Merge(x, y);
    } else if (mid >= l) {
      return Ask(p << 1, l, r);
    } else {
      return Ask(p << 1 | 1, l, r);
    }
  }

  void Add(int p, int l, int r, int k) {
    if (v[p].l >= l && v[p].r <= r) {
      return Tag(p, k);
    }
    Pushdown(p);
    int mid = v[p].l + v[p].r >> 1;
    if (mid >= l) {
      Add(p << 1, l, r, k);
    }
    if (mid < r) {
      Add(p << 1 | 1, l, r, k);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

 public:
  H() { Init(1, 1, n); }
  void Add(int l, int r, int k) { Add(1, l, r, k); }
  int Max(int l, int r) { return Max(1, l, r); }
  V Ask(int l, int r) { return Ask(1, l, r); }
  LL Calc(int l, int r) {
    int w = 0;
    return Calc(1, l, r, w);
  }
} h;

void T(int x, int b) {
  static int k = 0;
  a[x].r = ++k, a[x].s = 1;
  if (a[x].e.empty() && b) {
    b--, a[x].e.push_back(++n);
  }
  for (int i : a[x].e) {
    T(i, b), a[x].s += a[i].s;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> a[i].o >> x;
    a[i].o -= !a[i].o;
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      a[i].e.push_back(y);
    }
  }
  T(1, 2);
  for (int i = 1; i <= n; i++) {
    if (a[i].o == 1) {
      h.Add(a[i].r + 1, a[i].r + a[i].s - 1, 1);
    }
  }
  for (int i = 1, o, x; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      a[x].o = -a[x].o;
      h.Add(a[x].r + 1, a[x].r + a[x].s - 1, a[x].o);
    } else {
      V v = h.Ask(a[x].r, a[x].r + a[x].s - 1);
      LL ans = h.Calc(a[x].r, a[x].r + a[x].s - 1);
      ans -= 1LL * (h.Max(v.l, v.l) + 1) * (v.c + (v.pr < v.r));
      v.pr < v.r && (ans += h.Max(v.pr + 1, v.r));
      cout << ans << '\n';
    }
  }
  return 0;
}
