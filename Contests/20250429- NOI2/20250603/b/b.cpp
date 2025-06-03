#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1;
int n, q;
vector<int> a[kMaxN];

class Seg {
  struct V {
    LL s;
    int mx, t;
    int l, r;
  } v[kMaxN * 36];
  int m, t, s[kMaxN];

  void Init(int &p, int l, int r) {
    p = ++m, v[p].t = 0;
    if (l == r) {
      v[p].s = v[p].mx = l;
      v[p].l = v[p].r = 0;
      return;
    }
    int mid = l + r >> 1;
    Init(v[p].l, l, mid);
    Init(v[p].r, mid + 1, r);
    v[p].s = v[v[p].l].s + v[v[p].r].s;
    v[p].mx = v[v[p].r].mx;
  }

  void Copy(int &p) { v[++m] = v[p], p = m; }

  void Tag(int p, int l, int r, int w) {
    v[p].s = 1LL * w * (r - l + 1);
    v[p].mx = v[p].t = w;
  }

  void Pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    Copy(v[p].l), Copy(v[p].r);
    Tag(v[p].l, l, mid, v[p].t);
    Tag(v[p].r, mid + 1, r, v[p].t);
    v[p].t = 0;
  }

  void Cover(int &p, int l, int r, int _l, int _r, int w, bool isnew = 0) {
    !isnew ? Copy(p) : void();
    if (l >= _l && r <= _r) {
      return Tag(p, l, r, w);
    }
    (isnew = v[p].t) ? Pushdown(p, l, r) : void();
    int mid = l + r >> 1;
    if (mid >= _l) {
      Cover(v[p].l, l, mid, _l, _r, w, isnew);
    }
    if (mid < _r) {
      Cover(v[p].r, mid + 1, r, _l, _r, w, isnew);
    }
    v[p].s = v[v[p].l].s + v[v[p].r].s;
    v[p].mx = v[v[p].r].mx;
  }

  int LowerBound(int p, int l, int r, int w) {
    if (l == r || v[p].t) {
      return l;
    }
    int mid = l + r >> 1;
    if (v[v[p].l].mx >= w) {
      return LowerBound(v[p].l, l, mid, w);
    } else {
      return LowerBound(v[p].r, mid + 1, r, w);
    }
  }

  LL Sum(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].s;
    } else if (v[p].t) {
      return 1LL * v[p].mx * (min(r, _r) - max(l, _l) + 1);
    }
    int mid = l + r >> 1;
    LL ans = 0;
    if (mid >= _l) {
      ans += Sum(v[p].l, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Sum(v[p].r, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void Init() { m = t = s[0] = 0, Init(s[t], 1, n + 1); }
  void Forward() { t++, s[t] = s[t - 1]; }

  void CheckMax(int l, int w) {
    int p = LowerBound(s[t], 1, n + 1, w);
    if (l < p) {
      Cover(s[t], 1, n + 1, l, p - 1, w);
    }
  }

  LL Ask(int t, int l, int r) {
    int p = LowerBound(s[t], 1, n + 1, r + 1);
    if (l < p) {
      return 1LL * (r + 1) * (p - l) - Sum(s[t], 1, n + 1, l, p - 1);
    } else {
      return 0;
    }
  }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[x].push_back(i);
  }
  seg.Init();
  for (int i = 0; i < n; i++) {
    seg.Forward();
    reverse(a[i].begin(), a[i].end());
    a[i].push_back(0);
    int p = n + 1;
    for (int j : a[i]) {
      seg.CheckMax(j + 1, p), p = j;
    }
  }
  for (int i = 1, x, y; i <= q; i++) {
    static LL k;
    cin >> x >> y >> k;
    k = 1LL * (y - x + 1) * (y - x + 2) / 2 - k + 1;
    int l = 1, r = n;
    while (l <= r) {
      int mid = l + r >> 1;
      if (seg.Ask(mid, x, y) >= k) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << r << '\n';
  }
  return 0;
}
