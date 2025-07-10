#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e6 + 1, kInf = 2e9 + 1;
struct Q {
  int l, r, x, o;
} q[kMaxN];
int n, m, a[kMaxN];
bool ans[kMaxN];
vector<int> v[kMaxN];

class Seg {
  struct V {
    int mn, mn2, t;  // 区间最小值, 严格次小值, 将之前的区间最小值 t 全都变为 mn 的标记
    int mnx, mx;     // 区间最小值中最大的 a_{i+1}, 区间中最大的 值 + a_{i+1}
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].mn = v[p].mn2 = kInf, v[p].t = -1;
    v[p].mnx = -kInf, v[p].mx = -kInf;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Tag(int p, int t) {
    v[p].t = v[p].mn, v[p].mn = t;
    v[p].mx = max(v[p].mx, t + v[p].mnx);
  }

  void Pushdown(int p) {
    if (v[p].t != -1) {
      if (v[p << 1].mn == v[p].t) {
        Tag(p << 1, v[p].mn);
      }
      if (v[p << 1 | 1].mn == v[p].t) {
        Tag(p << 1 | 1, v[p].mn);
      }
      v[p].t = -1;
    }
  }

  void Pushup(int p) {
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
    v[p].mn2 = min(v[p << 1].mn2, v[p << 1 | 1].mn2);
    v[p].mnx = -kInf, v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
    if (v[p << 1].mn == v[p].mn) {
      v[p].mnx = max(v[p].mnx, v[p << 1].mnx);
    } else {
      v[p].mn2 = min(v[p].mn2, v[p << 1].mn);
    }
    if (v[p << 1 | 1].mn == v[p].mn) {
      v[p].mnx = max(v[p].mnx, v[p << 1 | 1].mnx);
    } else {
      v[p].mn2 = min(v[p].mn2, v[p << 1 | 1].mn);
    }
  }

  void Active(int p, int l, int r, int x) {
    if (l == r) {
      v[p].mn = 0, v[p].mnx = v[p].mx = a[x + 1];
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Active(p << 1, l, mid, x);
    } else {
      Active(p << 1 | 1, mid + 1, r, x);
    }
    Pushup(p);
  }

  void Max(int p, int l, int r, int w) {
    if (v[p].mn >= w) {
      return;
    } else if (v[p].mn2 > w) {
      return Tag(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    Max(p << 1, l, mid, w);
    Max(p << 1 | 1, mid + 1, r, w);
    Pushup(p);
  }

  int Ask(int p, int l, int r, int _r) {
    if (r <= _r) {
      return v[p].mx;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    int ans = Ask(p << 1, l, mid, _r);
    if (mid < _r) {
      ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _r));
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n - 1); }
  void Active(int x) { Active(1, 1, n - 1, x); }
  void Max(int w) { Max(1, 1, n - 1, w); }
  int Ask(int r) { return Ask(1, 1, n - 1, r); }
} seg;

void Init() {
  static vector<int> l;
  l.clear(), l.push_back(1);
  for (int i = 1; i <= n; i++) {
    v[i].clear();
  }
  for (int i = 2; i <= n; i++) {
    for (; !l.empty() && a[l.back()] <= a[i]; l.pop_back()) {
    }
    if (!l.empty()) {
      v[l.back()].push_back(i);
    }
    l.push_back(i);
  }
}

void Calc() {
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.l < j.l;
  });
  seg.Init();
  for (int i = n, j = m; i >= 1; i--) {
    for (int k : v[i]) {
      seg.Active(k - 1);
    }
    seg.Max(a[i]);
    for (; j >= 1 && q[j].l == i; j--) {
      ans[q[j].o] = q[j].l == q[j].r || seg.Ask(q[j].r - 1) <= q[j].x;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r >> q[i].x, q[i].o = i;
  }
  if (n == 1) {
    for (int i = 1; i <= m; i++) {
      cout << "Yes\n";
    }
    return 0;
  }
  Init(), Calc();
  for (int i = 1; i <= m; i++) {
    cout << (ans[i] ? "Yes\n" : "No\n");
  }
  return 0;
}
