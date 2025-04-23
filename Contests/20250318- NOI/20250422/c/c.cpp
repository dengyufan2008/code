#include <fstream>
#include <set>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 1, kMaxM = 1e5 + 3;
int n, m, k, u, q[kMaxN];
long long ans;
multiset<int> s[kMaxM], t[kMaxM];

// f/s:弹出最大值 g/t:弹出最小值
class DS {
  int f[kMaxM], g[kMaxM];
  multiset<int> s[kMaxM], t[kMaxM];

  int GetRoot(int *f, int x) { return f[x] == x ? x : f[x] = GetRoot(f, f[x]); }

  void Merge1(int x, int y) {
    f[y] = x;
    if (s[x].size() < s[y].size()) {
      swap(s[x], s[y]);
    }
    for (int i : s[y]) {
      s[x].insert(i);
    }
    s[y].clear();
  }

  void Merge2(int x, int y) {
    g[y] = x;
    if (t[x].size() < t[y].size()) {
      swap(t[x], t[y]);
    }
    for (int i : t[y]) {
      t[x].insert(i);
    }
    t[y].clear();
  }

  void CheckMerge() {
    for (int i = GetRoot(f, 1), j = GetRoot(g, 1), p = 0;;) {
      while (*s[i].rbegin() <= *t[j].begin() && p && GetRoot(f, i + 1) <= k) {
        Merge1(GetRoot(f, i + 1), i);
        Merge2(j, p);
        p = j, i = GetRoot(f, i), j = GetRoot(g, j + 1);
      }
      p = i, i = GetRoot(f, i + 1);
      if (i > k) {
        break;
      }
      while (*s[i].rbegin() <= *t[j].begin() && p && GetRoot(f, i + 1) <= k) {
        Merge1(i, p);
        Merge2(GetRoot(g, j + 1), j);
        p = i, i = GetRoot(f, i + 1), j = GetRoot(g, j);
      }
      p = j, j = GetRoot(g, j + 1);
    }
  }

 public:
  void Init() {
    for (int i = 1; i <= k; i++) {
      f[i] = g[i] = i;
      s[i].swap(::s[i]);
      t[i].swap(::t[i]);
    }
    f[k + 1] = g[k + 1] = k + 1;
    CheckMerge();
  }

  int Calc(int w) {
    for (int i = GetRoot(f, 1), j = GetRoot(g, 1); i <= k; i = GetRoot(f, i + 1), j = GetRoot(g, j + 1)) {
      if (*s[i].rbegin() > w) {
        s[i].insert(w);
        w = *s[i].rbegin();
        s[i].erase(--s[i].end());
      }
      if (*t[j].begin() < w) {
        t[j].insert(w);
        w = *t[j].begin();
        t[j].erase(t[j].begin());
      }
    }
    CheckMerge();
    return w;
  }
} ds;

void Init() {
  static int a[kMaxN];
  cin >> m >> u;
  for (int i = 1; i <= m; i++) {
    cin >> q[i];
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  static multiset<int> r;
  bool o = 1;
  r.insert(-1);
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c;
    if (o == 1 && c != 'B') {
      s[++k].swap(r);
    } else if (o == 0 && c == 'B') {
      t[k].swap(r);
    }
    r.insert(a[i]);
    o = c == 'B';
  }
  if (o == 1) {
    s[++k].swap(r);
    t[k].insert(1e9 + 1);
  } else {
    t[k].swap(r);
  }
  ds.Init();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  for (int i = 1; i <= m; i++) {
    ans += ds.Calc((q[i] + ans * u) % 1000000000);
    cout << ans << " \n"[i == m];
  }
  return 0;
}
