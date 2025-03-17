#include <fstream>
#include <set>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
int n, m, k, u, ans, f[kMaxN];
bool b[kMaxN];
set<int> s[kMaxN];

class Link {
 public:
  struct V {
    int w, p, n;
    bool b;  // 是否在链表内
  } v[kMaxN];

  void Insert(int x, int w, int p) {
    int n = v[p].n;
    v[x] = {w, p, n, 1}, v[p].n = v[n].p = x;
    ans = min(ans, min(v[p].w - x + 1, w - n + 1));
  }

  void Delete(int x) {
    v[x].b = 0, v[v[x].p].n = v[x].n, v[v[x].n].p = v[x].p;
    ans = min(ans, v[v[x].p].w - v[x].n + 1);
  }

  void Change(int x, int w) {
    v[x].w = w;
    ans = min(ans, w - v[x].n + 1);
  }
} link;

class Seg {
  int pre, mx[kMaxN << 2];

  void Init(int p, int l, int r) {
    mx[p] = kInf;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  bool Change(int p, int l, int r, int x, int w) {  // 返回是否是前缀最大值
    if (l == r) {
      mx[p] = w;
      return 1;
    }
    int mid = l + r >> 1, ans;
    if (mid >= x) {
      ans = Change(p << 1, l, mid, x, w);
    } else {
      ans = Change(p << 1 | 1, mid + 1, r, x, w);
      ans &= mx[p << 1] <= w;
    }
    mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    return ans;
  }

  void Find(int p, int l, int r, int w) {
    if (mx[p] < w) {
      return;
    } else if (l == r) {
      link.Insert(l, mx[p], pre);
      return;
    }
    int mid = l + r >> 1;
    Find(p << 1 | 1, mid + 1, r, max(w, mx[p << 1]));
    Find(p << 1, l, mid, w);
  }

  void Find(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      return Find(p, l, r, w);
    }
    int mid = l + r >> 1;
    if (mid < _r) {
      Find(p << 1 | 1, mid + 1, r, _l, _r, max(w, mx[p << 1]));
    }
    if (mid >= _l) {
      Find(p << 1, l, mid, _l, _r, w);
    }
  }

 public:
  void Init() { Init(1, 0, n); }

  void Change(int x, int w) {
    bool o = Change(1, 0, n, x, w);
    if (link.v[x].b) {
      int y = link.v[x].n;
      y = y ? y - 1 : n;
      if (x < y) {
        pre = x, Find(1, 0, n, x + 1, y, 0);
      }
      o ? link.Change(x, w) : link.Delete(x);
    }
  }
} seg;

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

void Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  if (x == y) {
    return;
  }
  s[x].size() > s[y].size() ? swap(x, y) : void();
  f[x] = y, b[max(*s[x].begin(), *s[y].begin())] = 1;
  if (b[k]) {
    for (; b[k]; k--) {
    }
    seg.Change(0, k);
  }
  int o = 0;
  for (auto r = s[x].begin(), l = r++; l != s[x].end(); l = r++) {
    auto q = s[y].insert(*l).first, p = q++;
    if (p != s[y].begin() && o != *--p) {
      seg.Change(*p, *l);
    }
    if (q != s[y].end() && (r == s[x].end() || *q < *r)) {
      seg.Change(*l, *q);
    }
    o = *l;
  }
  s[x].clear();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> u, k = ans = n;
  for (int i = 1; i <= n; i++) {
    f[i] = i, s[i].insert(i);
  }
  link.Insert(0, n, 0);
  for (int i = 1; i <= n; i++) {
    link.Insert(i, kInf, i - 1);
  }
  seg.Init(), seg.Change(0, n);
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    x = (x + u * ans - 1) % n + 1;
    y = (y + u * ans - 1) % n + 1;
    Merge(x, y);
    cout << ans << '\n';
  }
  return 0;
}
