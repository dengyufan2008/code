#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 1e4 + 1, kInf = 1e18;
int n, pm, qm, s[kMaxN], p[kMaxN], q[kMaxN];
bool pu, qu;
vector<int> a[kMaxN];

void Input() {
  static int p[kMaxN];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[p[i]].push_back(x);
  }
}

void Sort(vector<pair<int, int>> &t, int w) {
  static vector<int> d[kMaxN];
  for (auto i : t) {
    d[i.first].push_back(i.second);
  }
  t.clear();
  for (int i = 0; i <= w; i++) {
    for (int j : d[i]) {
      t.push_back({i, j});
    }
    d[i].clear();
  }
}

void CalcP(int l, int x) {
  static vector<pair<int, int>> t;
  t.clear();
  for (int i = l; i < x; i++) {
    t.push_back({s[i], i});
  }
  Sort(t, x - l);
  for (int i = 0, j = 0; i <= pm; i++) {
    p[i] = i ? p[i - 1] : l;
    for (; j < t.size() && t[j].first == i; j++) {
      p[i] = max(p[i], t[j].second + 1);
    }
  }
}

void CalcQ(int x, int r) {
  static vector<pair<int, int>> t;
  t.clear();
  for (int i = x; i < r; i++) {
    t.push_back({s[i], i});
  }
  Sort(t, r - x);
  for (int i = 0, j = 0; i <= qm; i++) {
    q[i] = i ? q[i - 1] : r;
    for (; j < t.size() && t[j].first == i; j++) {
      q[i] = min(q[i], t[j].second);
    }
  }
}

void Trans1(LL *f, int l, int x, int c, pair<int, int> v) {  // 只能向左的物品
  int y = v.second;
  for (; y > l && s[y - 1]; y--) {
    s[y - 1]--, pu = 1;
  }
  if (pu) {
    CalcP(l, x), pu = 0;
  }
  for (int i = 0, j = 0; i <= min(c, pm); i++) {
    f[i] += 1LL * v.first * (v.second - y);
    if (p[i] > y && p[i] <= v.second) {
      y = p[i];
    }
  }
}

void Trans2(LL *f, int r, int x, int c, pair<int, int> v) {  // 只能向右的物品
  int y = v.second;
  for (; y < r && s[y]; y++) {
    s[y]--, qu = 1;
  }
  if (qu) {
    CalcQ(x, r), qu = 0;
  }
  for (int i = 0, j = 0; i <= min(c, qm); i++) {
    f[c - i] += 1LL * v.first * (y - v.second);
    if (q[i] < y && q[i] >= v.second) {
      y = q[i];
    }
  }
}

void Trans3(LL *f, int l, int r, int x, int c, int v) {  // 都能去的物品
  static LL g[kMaxN];
  if (pu) {
    CalcP(l, x), pu = 0;
  }
  if (qu) {
    CalcQ(x, r), qu = 0;
  }
  fill(&g[0], &g[min(c + 1, pm)] + 1, kInf);
  for (int i = 0; i <= min(c, pm); i++) {
    g[i + 1] = min(g[i + 1], f[i] + 1LL * v * (x - p[i]));  // 去左边
    g[i] = min(g[i], f[i] + 1LL * v * (q[c - i] - x));      // 去右边
  }
  copy(&g[0], &g[min(c + 1, pm)] + 1, &f[0]);
}

LL Solve(int l, int r) {
  static LL f[kMaxN];  // 分配了 j 个去左边
  static vector<pair<int, int>> v;
  int x = l;
  for (; s[x] < 0; x++) {
  }
  v.clear();
  for (int i = l; i <= r; i++) {
    s[i] = abs(s[i]);
    for (int j : a[i]) {
      v.push_back({j, i});
    }
  }
  sort(v.begin(), v.end());
  pm = a[x].size() - s[x], qm = s[x], pu = qu = 1;
  f[0] = 0, fill(&f[1], &f[pm] + 1, kInf);
  for (int i = 0, c = 0; i < v.size(); i++) {
    if (v[i].second < x) {
      Trans1(f, l, x, c, v[i]);
    } else if (v[i].second > x) {
      Trans2(f, r, x, c, v[i]);
    } else {
      Trans3(f, l, r, x, c, v[i].first);
      c++;
    }
  }
  return f[pm];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input();
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + (int)a[i].size() - 1;
  }
  int ans1 = 0;
  LL ans2 = 0;
  for (int i = 1, p = 0; i <= n; i++) {
    ans1 += abs(s[i]);
    if (!s[i]) {
      ans2 += Solve(p + 1, i), p = i;
    }
  }
  cout << ans1 << ' ' << ans2 << '\n';
  return 0;
}
