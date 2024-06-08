#include <fstream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("n.in");
ofstream cout("n.out");

const int kMaxN = 2e5 + 1;
struct T {
  LL s, ans;
  bool operator<(const T &t) const {
    if (s < 0) {
      return t.s >= 0 || ans < t.ans;
    } else {
      return t.s >= 0 && ans > t.ans;
    }
  }
  T operator+(T t) {
    return {s + t.s, max(ans, s + t.ans)};
  }
};
struct D {
  int l, r;
  T t;
} d[kMaxN * 48];
struct V {
  int f, r, s;
  T t, _t;
  vector<int> e;
} v[kMaxN];
int n, m;
LL ans[kMaxN];
vector<int> p;
set<pair<T, int>> s;

int GetR(int x) {
  return v[x].r == x ? x : v[x].r = GetR(v[x].r);
}

void S(int x) {
  p.push_back(x);
  for (int i : v[x].e) {
    S(i);
  }
}

void Init(int &p, int l, int r, int x, T t) {
  p = ++m;
  if (l == r) {
    d[p].t = t;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Init(d[p].l, l, mid, x, t);
  } else {
    Init(d[p].r, mid + 1, r, x, t);
  }
  d[p].t = d[d[p].l].t + d[d[p].r].t;
}

void Merge(int &p, int q, int l, int r) {
  if (!p || !q) {
    p |= q;
    return;
  }
  int mid = l + r >> 1;
  Merge(d[p].l, d[q].l, l, mid);
  Merge(d[p].r, d[q].r, mid + 1, r);
  d[p].t = d[d[p].l].t + d[d[p].r].t;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> n;
  for (int i = 2; i <= n; i++) {
    cin >> v[i].f;
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, v[i].t.s = -x, v[i].r = i;
  }
  for (int i = 2; i <= n; i++) {
    v[v[i].f].t.s -= v[i].t.s;
    v[v[i].f].t.ans -= v[i].t.s;
  }
  v[1]._t = v[1].t;
  for (int i = 2; i <= n; i++) {
    v[i]._t = v[i].t, s.insert({v[i].t, i});
  }
  for (int i = 2; i <= n; i++) {
    int x = s.begin()->second, r = GetR(v[x].f);
    s.erase({v[x].t, x}), s.erase({v[r].t, r});
    v[x].r = r, v[r].t = v[r].t + v[x].t;
    v[r].e.push_back(x);
    if (r > 1) {
      s.insert({v[r].t, r});
    }
  }
  p.resize(1), S(1);
  for (int i = 1; i <= n; i++) {
    v[p[i]].t = v[p[i]]._t;
    Init(v[p[i]].s, 1, n, i, v[p[i]].t);
  }
  for (int i = n; i > 1; i--) {
    ans[i] = d[v[i].s].t.ans + v[i].t.ans - v[i].t.s;
    Merge(v[v[i].f].s, v[i].s, 1, n);
  }
  ans[1] = d[v[1].s].t.ans + v[1].t.ans - v[1].t.s;
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
