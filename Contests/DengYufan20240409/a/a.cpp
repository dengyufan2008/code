#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 2, kMaxL = 20, kMod = 1e9 + 7;
struct V {
  int ls, rs, lmx, rmx;
  int lt[kMaxL], lw[kMaxL], rt[kMaxL], rw[kMaxL];
} v[kMaxN];
int n;
LL ans;
pair<int, int> a[kMaxN], p[kMaxN * 2];
class Seg {
  pair<int, int> d[kMaxN * 8];

  void Pushdown(int p) {
    if (~d[p].second) {
      d[p << 1].first = d[p << 1].second = d[p].second;
      d[p << 1 | 1].first = d[p << 1 | 1].second = d[p].second;
      d[p].second = -1;
    }
  }

  void Change(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      d[p].first = d[p].second = x;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
  }

  int Ask(int p, int l, int r, int x) {
    if (l == r) {
      return d[p].first;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

 public:
  void Change(int l, int r, int x) { Change(1, 1, n * 2, l, r, x); }
  int Ask(int x) { return Ask(1, 1, n * 2, x); }
} seg;
class Bt {
  int d[kMaxN];

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }

 public:
  int Ask(int x, int y) { return Ask(y) - Ask(x - 1); }

  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      d[i] += y;
    }
  }
} bt;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    p[a[i].first] = {i, 1}, p[a[i].second] = {i, 0};
  }
  seg.Change(1, n * 2, n + 1);
  for (int i = n; i >= 1; i--) {
    v[i].lt[0] = seg.Ask(a[i].first);
    v[i].rt[0] = seg.Ask(a[i].second);
    seg.Change(a[i].first, a[i].second, i);
  }
  for (int i = 1; i <= n * 2; i++) {
    if (p[i].second) {
      v[p[i].first].lw[0] = bt.Ask(p[i].first, v[p[i].first].lt[0] - 1);
    } else {
      bt.Add(p[i].first, 1);
      v[p[i].first].rw[0] = bt.Ask(p[i].first, v[p[i].first].rt[0] - 1);
    }
  }
  v[n + 1].lt[0] = v[n + 1].rt[0] = n + 1;
  for (int i = n + 1; i >= 1; i--) {
    for (int j = 1; j < kMaxL; j++) {
      v[i].lt[j] = v[v[i].lt[j - 1]].lt[j - 1];
      v[i].rt[j] = v[v[i].rt[j - 1]].rt[j - 1];
      v[i].lw[j] = v[i].lw[j - 1] + v[v[i].lt[j - 1]].lw[j - 1];
      v[i].rw[j] = v[i].rw[j - 1] + v[v[i].rt[j - 1]].rw[j - 1];
    }
  }
  seg.Change(1, n * 2, 0);
  for (int i = 1; i <= n; i++) {
    v[i].ls = seg.Ask(a[i].first);
    v[i].rs = seg.Ask(a[i].second);
    seg.Change(a[i].first, a[i].second, i);
  }
  for (int i = n; i >= 1; i--) {
    v[i].lmx = max(v[i].lmx, i), v[i].rmx = max(v[i].rmx, i);
    for (int j : {v[i].ls, v[i].rs}) {
      if (j) {
        v[j].lmx = max(v[j].lmx, v[i].lmx);
        v[j].rmx = max(v[j].rmx, v[i].rmx);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int w = 0, x = i;
    for (int j = kMaxL - 1; j >= 0; j--) {
      if (v[x].lt[j] <= v[i].lmx) {
        w -= v[x].lw[j], x = v[x].lt[j];
      }
    }
    w -= v[x].lw[0], x = i;
    for (int j = kMaxL - 1; j >= 0; j--) {
      if (v[x].rt[j] <= v[i].rmx) {
        w += v[x].rw[j], x = v[x].rt[j];
      }
    }
    w += v[x].rw[0], ans = (ans + Pow(w)) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
