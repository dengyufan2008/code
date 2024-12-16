#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 5001, kMaxM = 15001, kV = 1e5, kInf = 1e9;
struct Q {
  int o, l, r;
};
int n, m, ans, a[kMaxN], l[kMaxN], w[kMaxN];
int s[2][kMaxN], f[2][kMaxN], p[2][kMaxN];
vector<Q> q[kMaxN];
vector<int> _l[2];

struct Stack {
  int k;
  pair<int, int> v[kMaxN];

  void Clear() { k = 0; }

  void Push(int x, int t) {
    for (; k && t >= v[k].second; k--) {
    }
    v[++k] = {x, t};
  }

  int Ask(int t) {
    for (; k && t >= v[k].second; k--) {
    }
    return k ? v[k].first : 0;
  }
} stk[2];

struct Seg {
  struct V {
    pair<int, int> mn;
    bool b;
  } v[kMaxN << 2];

  void Tag(int p) { v[p].b = 1, v[p].mn = {kInf, 0}; }

  void Pushdown(int p) {
    if (v[p].b) {
      Tag(p << 1), Tag(p << 1 | 1), v[p].b = 0;
    }
  }

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      v[p].mn = {y, x};
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
  }

  void Delete(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return Tag(p);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Delete(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      Delete(p << 1 | 1, mid + 1, r, _l, _r);
    }
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
  }

  pair<int, int> Ask(int p, int l, int r, int _l) {
    if (l >= _l) {
      return v[p].mn;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    pair<int, int> ans = Ask(p << 1 | 1, mid + 1, r, _l);
    if (mid >= _l) {
      ans = min(ans, Ask(p << 1, l, mid, _l));
    }
    return ans;
  }

  void Change(int x, int y) { Change(1, 0, n, x, y); }
  void Delete(int x, int y) { Delete(1, 0, n, x, y); }
  pair<int, int> Ask(int x) { return Ask(1, 0, n, x); }
} seg[2];

void Solve(int lo, int ro, int lv, int rv) {
  if (lo > ro || lv == rv) {
    for (int i = lo; i <= ro; i++) {
      w[l[i]] = lv;
    }
    return;
  }
  int x = lv + rv >> 1, y = x + 1;
  s[0][lo - 1] = s[1][lo - 1] = 0;
  for (int i = lo; i <= ro; i++) {
    s[0][i] = s[0][i - 1] + abs(x - a[l[i]]);
    s[1][i] = s[1][i - 1] + abs(y - a[l[i]]);
  }
  stk[0].Clear(), stk[1].Clear();
  seg[0].Delete(0, n), seg[1].Delete(0, n);
  seg[0].Change(0, 0), seg[1].Change(0, 0);
  for (int u = lo; u <= ro; u++) {
    int i = l[u];
    for (Q j : q[i]) {
      j.l < i ? seg[j.o].Delete(j.l, i - 1) : void();
      i < j.r ? stk[j.o].Push(i, j.r) : void();
    }
    pair<int, int> ask0 = seg[1].Ask(stk[1].Ask(u < ro ? l[u + 1] - 1 : kInf));
    pair<int, int> ask1 = seg[0].Ask(stk[0].Ask(u < ro ? l[u + 1] - 1 : kInf));
    f[0][u] = ask0.first + s[0][u], p[0][u] = ask0.second;
    f[1][u] = ask1.first + s[1][u], p[1][u] = ask1.second;
    seg[0].Change(i, f[0][u] - s[1][u]);
    seg[1].Change(i, f[1][u] - s[0][u]);
  }
  _l[0].clear(), _l[1].clear();
  for (int i = ro, u = f[0][ro] > f[1][ro]; i >= lo; u ^= 1) {
    for (int j = p[u][i]; i >= lo && l[i] > j; i--) {
      _l[u].push_back(l[i]);
    }
  }
  reverse(_l[0].begin(), _l[0].end());
  reverse(_l[1].begin(), _l[1].end());
  int mid1 = lo;
  for (int i : _l[0]) {
    l[mid1++] = i;
  }
  int mid2 = mid1;
  for (int i : _l[1]) {
    l[mid2++] = i;
  }
  Solve(lo, mid1 - 1, lv, x), Solve(mid1, mid2 - 1, y, rv);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], l[i] = i;
  }
  for (int i = 1, o, l, r, x; i <= m; i++) {
    cin >> o >> l >> r >> x;
    q[x].push_back({o, l, r});
  }
  Solve(1, n, 1, kV);
  for (int i = 1; i <= n; i++) {
    ans += abs(a[i] - w[i]);
  }
  cout << ans << '\n';
  return 0;
}
