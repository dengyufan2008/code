#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kV = 1e9;
int n, a[kMaxN];
LL ans;

// 初始 v_i = -i, 后缀加, 区间查 max
class Seg {
  struct V {
    int mx, t, l, r;
  } v[kMaxN * 40];
  int s, m;

  void Tag(int p, int t) {
    v[p].mx += t, v[p].t += t;
  }

  void Pushdown(int p, int l, int r) {
    if (v[p].t) {
      if (!v[p].l) {
        v[++m].mx = -l, v[p].l = m;
      }
      Tag(v[p].l, v[p].t);
      if (!v[p].r) {
        v[++m].mx = -((l + r >> 1) + 1), v[p].r = m;
      }
      Tag(v[p].r, v[p].t);
      v[p].t = 0;
    }
  }

  void Pushup(int p, int l, int r) {
    v[p].mx = -l;
    if (v[p].l) {
      v[p].mx = max(v[p].mx, v[v[p].l].mx);
    }
    if (v[p].r) {
      v[p].mx = max(v[p].mx, v[v[p].r].mx);
    }
  }

  void Add(int &p, int l, int r, int x, int w) {
    if (!p) {
      v[++m].mx = -l, p = m;
    }
    if (l >= x) {
      return Tag(p, w);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    Add(v[p].r, mid + 1, r, x, w);
    if (mid >= x) {
      Add(v[p].l, l, mid, x, w);
    }
    Pushup(p, l, r);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (!p) {
      return -max(l, _l);
    } else if (l >= _l && r <= _r) {
      return v[p].mx;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1, ans = -_l;
    if (mid >= _l) {
      ans = max(ans, Ask(v[p].l, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, Ask(v[p].r, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Add(int x, int w) { Add(s, 1, kV, x, w); }
  int Ask(int l, int r) { return Ask(s, 1, kV, l, r); }
} seg;

void Init() {
  static int l[kMaxN], d[kMaxN];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return a[i] < a[j] || a[i] == a[j] && i < j;
  });
  for (int i = 1; i <= n; i++) {
    for (int j = l[i]; j <= n; j += j & -j) {
      ans += d[j];
    }
    for (int j = l[i]; j >= 1; j -= j & -j) {
      d[j]++;
    }
  }
}

void Do() {
  for (int i = 1; i <= n; i++) {
    seg.Add(a[i], 1);
  }
  for (int i = n; i >= 1; i--) {
    ans -= seg.Ask(a[i], kV) - seg.Ask(a[i], a[i]);
    seg.Add(a[i], -1);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Do();
  return 0;
}
