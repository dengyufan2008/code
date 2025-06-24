#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 2, kMaxK = 26, kInf = 1e9;
const int kBase = 1145141, kMod = 998244353;
struct Q {
  int l, r, o;
} q[kMaxN];
struct E {
  int l, r, x, o;
};
int n, m, k, a[kMaxN], ans[kMaxN];
LL h1[kMaxN], h2[kMaxK][kMaxN], pw[kMaxN];
vector<E> e;

class Bit {
  int d[kMaxN];

 public:
  void Init() { fill(&d[1], &d[n] + 1, 0); }

  void Add(int x, int w) {
    for (int i = x; i >= 1; i -= i & -i) {
      d[i] = max(d[i], w);
    }
  }

  int Suf(int x) {
    int ans = 0;
    for (int i = x; i <= n; i += i & -i) {
      ans = max(ans, d[i]);
    }
    return ans;
  }
} bit;

class Seg {
  int v[kMaxN << 2];
  priority_queue<int> q1[kMaxN], q2[kMaxN];

  void Init(int p, int l, int r) {
    v[p] = -kInf;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Update(int p, int l, int r, int x) {
    if (l == r) {
      v[p] = q1[x].top();
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Update(p << 1, l, mid, x);
    } else {
      Update(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = max(v[p << 1], v[p << 1 | 1]);
  }

  int Suf(int p, int l, int r, int x) {
    if (l >= x) {
      return v[p];
    }
    int mid = l + r >> 1;
    int ans = Suf(p << 1 | 1, mid + 1, r, x);
    if (mid >= x) {
      ans = max(ans, Suf(p << 1, l, mid, x));
    }
    return ans;
  }

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      for (; !q1[i].empty(); q1[i].pop()) {
      }
      for (; !q2[i].empty(); q2[i].pop()) {
      }
      q1[i].push(-kInf);
    }
    Init(1, 1, n);
  }

  void Add(int x, int w) {
    int mx = q1[x].top();
    q1[x].push(w);
    if (w > mx) {
      Update(1, 1, n, x);
    }
  }

  void Del(int x, int w) {
    int mx = q1[x].top();
    q2[x].push(w);
    for (; !q2[x].empty() && q1[x].top() == q2[x].top();) {
      q1[x].pop(), q2[x].pop();
    }
    if (q1[x].top() < mx) {
      Update(1, 1, n, x);
    }
  }

  int Suf(int x) { return Suf(1, 1, n, x); }
} seg;

void Init() {
  static string s;
  cin >> s >> k >> m, n = s.size(), s = '~' + s;
  for (int i = 1; i <= n; i++) {
    a[i] = s[i] - 'a';
  }
  pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw[i] = pw[i - 1] * kBase % kMod;
  }
  for (int i = 1; i <= n; i++) {
    h1[i] = (h1[i - 1] * kBase + a[i] % k) % kMod;
  }
  for (int o = 0; o < k; o++) {
    for (int i = n; i >= 1; i--) {
      h2[o][i] = (h2[o][i + 1] * kBase + (a[i] + o) % k) % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r, q[i].o = i;
  }
}

int Extend(int x, int y, int o) {  // 右边偏移 o 再匹配
  int l = 1, r = min(x, n - y + 1);
  while (l <= r) {
    int mid = l + r >> 1;
    LL hl = (h1[x] - h1[x - mid] * pw[mid]) % kMod;
    LL hr = (h2[o][y] - h2[o][y + mid] * pw[mid]) % kMod;
    if ((hl + kMod) % kMod == (hr + kMod) % kMod) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r;
}

void CalcE() {
  int w = 0;
  for (int i = 1; i <= n; i++) {
    int l = Extend(i, i, 0);
    w = max(w, l * 2 - 1);
    if (i - l >= 1 && i + l <= n) {
      int ll = Extend(i - l, i + l, (a[i - l] - a[i + l] + k) % k);
      e.push_back({i + l, i + l + ll - 1, l * 2 - 1, 0});
      e.push_back({i - l - ll + 1, i - l, l * 2 - 1, 1});

      int lll = Extend(i - l - ll, i + l + ll, 0);
      e.push_back({i + l, i + l + ll - 1, (l + ll + lll) * 2 - 1, 2});
      e.push_back({i - l - ll + 1, i - l, (l + ll + lll) * 2 - 1, 2});
    }
  }
  for (int i = 1; i < n; i++) {
    int l = Extend(i, i + 1, 0);
    w = max(w, l * 2);
    if (i - l >= 1 && i + l + 1 <= n) {
      int ll = Extend(i - l, i + l + 1, (a[i - l] - a[i + l + 1] + k) % k);
      e.push_back({i + l + 1, i + l + ll, l * 2, 0});
      e.push_back({i - l - ll + 1, i - l, l * 2, 1});

      int lll = Extend(i - l - ll, i + l + ll + 1, 0);
      e.push_back({i + l + 1, i + l + ll, (l + ll + lll) * 2, 2});
      e.push_back({i - l - ll + 1, i - l, (l + ll + lll) * 2, 2});
    }
  }
  fill(&ans[1], &ans[m] + 1, w);
}

void CalcContain() {
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.r < j.r;
  });
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.r < j.r;
  });
  bit.Init();
  for (int i = 1, j = 0, k = 1; i <= n; i++) {
    for (; j < e.size() && e[j].r == i; j++) {
      if (e[j].o == 2) {
        bit.Add(e[j].l, e[j].x);
      }
    }
    for (; k <= m && q[k].r == i; k++) {
      ans[q[k].o] = max(ans[q[k].o], bit.Suf(q[k].l));
    }
  }
}

void CalcTouch(int o) {
  static vector<pair<int, bool>> v[kMaxN];
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.r < j.r;
  });
  for (int i = 0; i < e.size(); i++) {
    if (e[i].o == o) {
      v[e[i].l].push_back({i, 1});
      v[e[i].r].push_back({i, 0});
    }
  }
  seg.Init();
  for (int i = 1, j = 1; i <= n; i++) {
    for (auto t : v[i]) {
      if (t.second) {
        seg.Add(e[t.first].l, e[t.first].x - (e[t.first].l - 1) * 2);
      } else {
        seg.Del(e[t.first].l, e[t.first].x - (e[t.first].l - 1) * 2);
      }
    }
    v[i].clear();
    for (; j <= m && q[j].r == i; j++) {
      ans[q[j].o] = max(ans[q[j].o], seg.Suf(q[j].l) + i * 2);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), CalcE(), CalcContain();
  CalcTouch(0);
  for (int i = 1; i <= m; i++) {
    swap(q[i].l, q[i].r);
    q[i].l = n - q[i].l + 1;
    q[i].r = n - q[i].r + 1;
  }
  for (E &i : e) {
    swap(i.l, i.r);
    i.l = n - i.l + 1;
    i.r = n - i.r + 1;
  }
  CalcTouch(1);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
