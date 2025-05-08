#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 1, kInf = 1e9;
int n, m, k1, k2, a[kMaxN];
int mx1[kMaxN];  // i 后缀的第 k1 大
int mx2[kMaxN];  // i 后缀的第 k2 大
int f[kMaxN];    // \max_{mx2_x \ge i} \{i + \sum_{j=1}^{x-1} [a_j \ge k1] + [a_j \ge k2]\}
int g[kMaxN];    // \max_{mx1_x \ge i} \{i + \sum_{j=x}^n [a_j \ge k1 + i] + [a_j \ge k2 + i] \}

// 单点+1, 后缀求和
class Bit {
  int d[kMaxN];

 public:
  void Init() { fill(&d[1], &d[m] + 1, 0); }

  void Add(int x) {
    for (int i = x; i >= 1; i -= i & -i) {
      d[i]++;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i <= m; i += i & -i) {
      ans += d[i];
    }
    return ans;
  }
} bit;

// 区间加, 区间求 max
class Seg {
  struct V {
    int mx, t;
  } v[kMaxN << 2];

  void Tag(int p, int t) {
    v[p].mx += t, v[p].t += t;
  }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1, v[p].t);
      Tag(p << 1 | 1, v[p].t);
      v[p].t = 0;
    }
  }

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      return Tag(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].mx;
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = -kInf;
    if (mid >= _l) {
      ans = max(ans, Ask(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Add(int l, int r, int w) {
    if (l <= r) {
      Add(1, 1, n + 1, l, r, w);
    }
  }

  int Ask(int l, int r) {
    if (l <= r) {
      return Ask(1, 1, n + 1, l, r);
    } else {
      return -kInf;
    }
  }
} seg;

void Init() {
  static priority_queue<int, vector<int>, greater<int>> q1, q2;
  for (int i = 1; i <= k1; i++) {
    q1.push(0);
  }
  for (int i = 1; i <= k2; i++) {
    q2.push(0);
  }
  for (int i = n; i >= 1; i--) {
    q1.push(a[i]), q1.pop(), mx1[i] = q1.top();
    q2.push(a[i]), q2.pop(), mx2[i] = q2.top();
  }
  for (int i = 1, w = 0; i <= n; i++) {
    for (int j = mx2[i + 1] + 1; j <= mx2[i]; j++) {
      f[j] = j + w;
    }
    w += (a[i] >= k1) + (a[i] >= k2);
  }
  bit.Init();
  for (int i = n; i >= 1; i--) {
    bit.Add(a[i]);
    for (int j = mx1[i + 1] + 1; j <= mx1[i]; j++) {
      g[j] = j + bit.Ask(k1 + j) + bit.Ask(k2 + j);
    }
  }
}

void Calc() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {  // 不存在 AOE
    ans += (a[i] >= k1) + (a[i] >= k2);
  }
  for (int i = 1, w = 0; i <= n; i++) {  // 只存在贡献为 1 的 AOE
    for (int j = mx1[i + 1] + 1; j <= mx1[i]; j++) {
      ans = max(ans, g[j] + w);
    }
    w += (a[i] >= k1) + (a[i] >= k2);
  }
  bit.Init();
  for (int i = n; i >= 1; i--) {  // 只存在贡献为 2 的 AOE
    bit.Add(a[i]);
    for (int j = mx2[i + 1] + 1; j <= mx2[i]; j++) {
      ans = max(ans, f[j] + bit.Ask(k1 + j) + bit.Ask(k2 + j));
    }
  }
  for (int i = 1; i <= n; i++) {  // 两种贡献的 AOE 都存在
    for (int j = mx2[i + 1] + 1; j <= mx2[i]; j++) {
      seg.Add(j, j, f[j]);
    }
    for (int j = mx1[i + 1] + 1; j <= mx1[i]; j++) {
      ans = max(ans, seg.Ask(mx2[i + 1] + 1, j) + g[j]);
    }
    seg.Add(mx2[i + 1] + 1, a[i] - k1, 1);
    seg.Add(mx2[i + 1] + 1, a[i] - k2, 1);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k1 >> k2, m = k2;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], m = max(m, a[i]);
  }
  Init(), Calc();
  return 0;
}
