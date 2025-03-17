#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define PII pair<int, int>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
int n, m;
PII a[kMaxN];

namespace Case1 {  // 包含了恶魔的区间有公共点
struct Q {
  int l, r, w;
};
vector<Q> q[kMaxN];
vector<PII> ans;

class Seg {  // 勾石标记永久化
  struct V {
    int c, t;
    PII x;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].c = r - l + 1, v[p].t = 0, v[p].x = {r, l};
    if (l == r) {
      v[p].x.second = 0;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Update(int p) {
    if (v[p].t) {
      v[p].c = 0, v[p].x = {0, 0};
      return;
    }
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
    if (v[p << 1].c >= 2) {
      v[p].x = v[p << 1].x;
    } else if (v[p << 1 | 1].c >= 2) {
      v[p].x = v[p << 1 | 1].x;
    } else {
      v[p].x.first = max(v[p << 1].x.first, v[p << 1 | 1].x.first);
      v[p].x.second = min(v[p << 1].x.first, v[p << 1 | 1].x.first);
    }
  }

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      v[p].t += w;
      if (l == r) {
        if (v[p].t) {
          v[p].c = 0, v[p].x = {0, 0};
        } else {
          v[p].c = 1, v[p].x = {l, 0};
        }
      } else {
        Update(p);
      }
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    Update(p);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Add(int l, int r, int w) { Add(1, 1, n, l, r, w); }
  int Sum() { return v[1].c; }
  PII Ask() { return v[1].x; }
} seg;

int Solve() {
  for (int i = 1; i <= m; i++) {
    if (a[i].first > 1) {
      q[1].push_back({a[i].first, a[i].second, 1});
      q[a[i].first].push_back({a[i].first, a[i].second, -1});
    }
    if (a[i].second < n) {
      q[a[i].second + 1].push_back({a[i].first, a[i].second, 1});
    }
  }
  seg.Init(), ans.clear();
  for (int i = 1; i <= n; i++) {
    for (Q j : q[i]) {
      seg.Add(j.l, j.r, j.w);
    }
    q[i].clear();
    if (seg.Sum() == 2) {
      PII x = seg.Ask();
      ans.push_back(x);
    }
  }
  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  return ans.size();
}
}  // namespace Case1

namespace Case2 {  // 包含了恶魔的区间无公共点
int f[kMaxN];
int g[kMaxN];

class Seg1 {
  struct V {
    int c, t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].c = r - l + 1, v[p].t = 0;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      v[p].t += w;
      if (l == r) {
        v[p].c = !v[p].t;
      } else {
        v[p].c = v[p].t ? 0 : v[p << 1].c + v[p << 1 | 1].c;
      }
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    v[p].c = v[p].t ? 0 : v[p << 1].c + v[p << 1 | 1].c;
  }

  int Pre(int p, int l, int r) {
    if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (v[p << 1 | 1].c) {
      return Pre(p << 1 | 1, mid + 1, r);
    }
    return Pre(p << 1, l, mid);
  }

  int Pre(int p, int l, int r, int x, bool t) {
    t |= v[p].t;
    if (r <= x) {
      return !t && v[p].c ? Pre(p, l, r) : 0;
    }
    int mid = l + r >> 1, ans = 0;
    if (mid < x) {
      ans = Pre(p << 1 | 1, mid + 1, r, x, t);
    }
    if (!ans) {
      ans = Pre(p << 1, l, mid, x, t);
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Add(int l, int r, int w) { Add(1, 1, n, l, r, w); }
  int Pre(int x) { return x == 1 ? 0 : Pre(1, 1, n, x - 1, 0); }
} seg1;

class Seg2 {
  int v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p] = n;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Change(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p] = w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, w);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, w);
    }
    v[p] = min(v[p << 1], v[p << 1 | 1]);
  }

  int Min(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1, ans = n;
    if (mid >= _l) {
      ans = min(ans, Min(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = min(ans, Min(p << 1 | 1, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Change(int x, int w) { Change(1, 1, n, x, w); }
  int Min(int l, int r) { return Min(1, 1, n, l, r); }
} seg2;

class Seg3 {
  struct V {
    int mx, mx2, t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].mx = n, v[p].mx2 = v[p].t = 0;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Tag(int p, int t) {
    if (v[p].mx > t) {
      v[p].mx = v[p].t = t;
    }
  }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t), v[p].t = 0;
    }
  }

  void Pushup(int p) {
    v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
    v[p].mx2 = max(v[p << 1].mx2, v[p << 1 | 1].mx2);
    if (v[p << 1].mx != v[p].mx) {
      v[p].mx2 = max(v[p].mx2, v[p << 1].mx);
    }
    if (v[p << 1 | 1].mx != v[p].mx) {
      v[p].mx2 = max(v[p].mx2, v[p << 1 | 1].mx);
    }
  }

  void CheckMin(int p, int l, int r, int _l, int _r) {
    if (v[p].mx <= _r) {
      return;
    } else if (l >= _l && r <= _r && v[p].mx2 < _r) {
      return Tag(p, _r);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      CheckMin(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      CheckMin(p << 1 | 1, mid + 1, r, _l, _r);
    }
    Pushup(p);
  }

  int AskMax(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].mx;
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans = max(ans, AskMax(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, AskMax(p << 1 | 1, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  // checkmin 的值为右端点
  void CheckMin(int l, int r) { CheckMin(1, 1, n, l, r); }
  int AskMax(int l, int r) { return AskMax(1, 1, n, l, r); }
} seg3;

class Union {
  int v[kMaxN];

 public:
  void Init() {
    for (int i = 0; i <= n; i++) {
      v[i] = i;
    }
  }

  int GetRoot(int x) {
    return v[x] == x ? x : v[x] = GetRoot(v[x]);
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    x != y && (v[x] = y);
  }
} uni;

class Bit {
  int v[kMaxN];

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      v[i] = 0;
    }
  }

  void Add(int x, int w) {
    for (int i = x; i >= 1; i -= i & -i) {
      v[i] += w;
    }
  }

  int AskSuf(int x) {
    int ans = 0;
    for (int i = x; i <= n; i += i & -i) {
      ans += v[i];
    }
    return ans;
  }
} bit;

void CalcFG1(int *d) {
  struct Q {
    int l, r, w;
  };
  static vector<Q> q[kMaxN];
  static int t[kMaxN];
  for (int i = 1; i <= m; i++) {
    if (a[i].first > 1) {
      q[1].push_back({a[i].first, a[i].second, 1});
      q[a[i].first].push_back({a[i].first, a[i].second, -1});
    }
    if (a[i].second < n) {
      q[a[i].second + 1].push_back({a[i].first, a[i].second, 1});
    }
  }
  seg1.Init();
  for (int i = 1; i <= n; i++) {
    for (Q j : q[i]) {
      seg1.Add(j.l, j.r, j.w);
    }
    q[i].clear(), t[i] = seg1.Pre(i);
  }
  sort(a + 1, a + m + 1, [](PII i, PII j) {
    return i.second < j.second;
  });
  seg2.Init();
  for (int i = n, j = m; i >= 1; i--) {
    for (; j >= 1 && a[j].second == i; j--) {
      seg2.Change(a[j].first, a[j].second);
    }
    if (t[i] < i) {
      d[i] = seg2.Min(t[i] + 1, i);
    } else {
      d[i] = n;
    }
  }
}

void CalcFG2(int *d) {
  static int t[kMaxN];
  // already sorted
  // sort(a + 1, a + m + 1, [](PII i, PII j) {
  //   return i.second < j.second;
  // });
  uni.Init();
  for (int i = 1; i <= n; i++) {
    t[i] = n;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = uni.GetRoot(a[i].second); j >= a[i].first; j = uni.GetRoot(j)) {
      t[j] = a[i].second, uni.Merge(j, j - 1);
    }
  }
  sort(a + 1, a + m + 1, [](PII i, PII j) {
    return i.first < j.first;
  });
  seg3.Init();
  for (int i = n, j = m; i >= 1; i--) {
    if (i < t[i]) {
      d[i] = max(d[i], seg3.AskMax(i + 1, t[i]));
    }
    for (; j >= 1 && a[j].first == i; j--) {
      seg3.CheckMin(a[j].first, a[j].second);
    }
  }
}

LL CalcAns() {
  static vector<int> v[kMaxN];
  LL ans = 0;
  bit.Init();
  for (int i = 1; i <= n; i++) {
    v[g[i]].push_back(i), bit.Add(i, 1);
  }
  for (int i = 1; i <= n; i++) {
    for (int j : v[i]) {
      bit.Add(j, -1);
    }
    v[i].clear(), ans += bit.AskSuf(f[i] + 1);
  }
  return ans;
}

LL Solve() {
  CalcFG1(f), CalcFG2(f);  // y > f_x
  for (int i = 1; i <= m; i++) {
    a[i].first = n - a[i].first + 1;
    a[i].second = n - a[i].second + 1;
    swap(a[i].first, a[i].second);
  }
  CalcFG1(g), CalcFG2(g);  // x < g_y
  for (int i = 1; i <= m; i++) {
    a[i].first = n - a[i].first + 1;
    a[i].second = n - a[i].second + 1;
    swap(a[i].first, a[i].second);
  }
  reverse(g + 1, g + n + 1);
  for (int i = 1; i <= n; i++) {
    g[i] = n - g[i] + 1;
  }
  return CalcAns();
}
}  // namespace Case2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int u;
  cin >> u;
  while (u--) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
      cin >> a[i].first >> a[i].second;
    }
    cout << (Case1::Solve() + Case2::Solve()) % kMod << '\n';
  }
  return 0;
}
