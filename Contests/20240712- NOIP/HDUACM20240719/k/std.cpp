#include <bits/stdc++.h>

typedef long long int64;

const int N = 70000;

int n, a[N + 9];
std::vector<int> e[N + 9];

void Read() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  for (int i = 1; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    // std::cerr<<' '<<x<<" - "<<y<<'\n';
    e[x].push_back(y);
    e[y].push_back(x);
  }
}

int fa[N + 9];
int ld[N + 9], rd[N + 9], co;
int ll[N + 9], rl[N + 9], cl;
std::vector<int> sta[N + 9], dn[N + 9], rdn[N + 9];

void DFSOrder(int x, int fat) {
  fa[x] = fat;
  ld[x] = ++co;
  // std::cerr<<' '<<x<<" : "<<ld[x]<<'\n';
  ll[x] = cl += e[x].size() == 1;
  int c = a[x];
  if (sta[c].empty()) {
    rdn[c].push_back(x);
  } else {
    dn[sta[c].back()].push_back(x);
  }
  for (int y : e[x]) {
    if (y == fat) continue;
    sta[c].push_back(y);
    DFSOrder(y, x);
    sta[c].pop_back();
  }
  rd[x] = co;
  rl[x] = cl;
}

int rt;

void InitOrder() {
  for (int i = 1; i <= n; ++i)
    if (e[i].size() > 1) {
      rt = i;
      break;
    }
  DFSOrder(rt, 0);
}

//                     x   yl  yr  v
std::vector<std::tuple<int, int, int, int>> line[N + 9];

void InitLine() {
  auto Insert = [&](int c, int k, const std::vector<int> &vec) {
    // std::cerr<<"  + "<<c<<' '<<k<<" : ";
    // for (int x:vec) std::cerr<<x<<' ';
    // std::cerr<<'\n';
    std::vector<int> p({ld[k] - 1, rd[k] + 1});
    for (int x : vec) {
      p.push_back(ld[x]);
      p.push_back(rd[x]);
    }
    std::sort(p.begin(), p.end());
    std::vector<std::pair<int, int>> seg;
    for (int i = 0; i < (int)p.size(); i += 2) {
      int l = p[i] + 1;
      int r = p[i + 1] - 1;
      if (l > r) continue;
      seg.emplace_back(l, r);
    }
    for (auto [l, r] : seg)
      for (auto [u, v] : seg) {
        line[c].emplace_back(l, u, v, 1);
        line[c].emplace_back(r + 1, u, v, -1);
      }
  };
  for (int i = 0; i <= n; ++i)
    Insert(i, rt, rdn[i]);
  for (int i = 1; i <= n; ++i)
    if (i != rt) Insert(a[fa[i]], i, dn[i]);
  // for (int i=0;i<=n;++i){
  //   std::cerr<<"  "<<i<<" :\n";
  //   for (auto [p,l,r,v]:line[i])
  //     std::cerr<<"    "<<p<<' '<<l<<' '<<r<<' '<<v<<'\n';
  // }
}

struct tree {
  int cnt, add;
} tr[N * 4 + 9];
int m;

inline void Pushup(int k) {
  int x = k << 1, y = k << 1 | 1;
  tr[k].cnt = (tr[x].add ? 0 : tr[x].cnt) + (tr[y].add ? 0 : tr[y].cnt);
}

void Build(int n) {
  for (m = 1; m <= n; m <<= 1);
  for (int i = 1; i < m << 1; ++i) tr[i].add = tr[i].cnt = 0;
  for (int i = 1; i <= n; ++i) tr[m + i].cnt = 1;
  for (int i = m - 1; i >= 1; --i) Pushup(i);
}

void ChangeAdd(int l, int r, int v) {
  l += m - 1;
  r += m + 1;
  for (; l ^ r ^ 1;) {
    if (l & 1 ^ 1) tr[l ^ 1].add += v;
    Pushup(l >>= 1);
    if (r & 1) tr[r ^ 1].add += v;
    Pushup(r >>= 1);
  }
  for (l >>= 1; l; l >>= 1) Pushup(l);
}

int QueryCnt() { return tr[1].add ? 0 : tr[1].cnt; }

std::vector<std::tuple<int, int, int>> temp[N + 9];
int max;
int64 cnt;

int64 ScanningLine(int mid) {
  for (int i = 0; i <= mid; ++i)
    for (auto [x, l, r, v] : line[i])
      temp[x].emplace_back(l, r, v);
  Build(n);
  int64 res = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto [l, r, v] : temp[i]) {
      // std::cerr<<"  "<<l<<' '<<r<<' '<<v<<'\n';
      ChangeAdd(l, r, v);
    }
    // int t=QueryCnt();
    // std::cerr<<" "<<mid<<' '<<i<<" : "<<t<<'\n';
    res += QueryCnt();
  }
  // std::cerr<<" "<<mid<<" : "<<res<<'\n';
  for (int i = 0; i <= n + 1; ++i) temp[i].clear();
  return res;
}

void Solve() {
  int l = 0, r = n;
  max = -1;
  cnt = 1LL * n * n;
  for (; l <= r;) {
    int mid = l + r >> 1;
    int64 res = ScanningLine(mid);
    res ? (l = mid + 1, max = mid, cnt = res) : r = mid - 1;
  }
  std::cout << max + 1 << ' ' << cnt << '\n';
}

void Clear() {
  co = cl = 0;
  for (int i = 0; i <= n + 1; ++i) {
    e[i].clear();
    sta[i].clear();
    dn[i].clear();
    rdn[i].clear();
    fa[i] = 0;
    line[i].clear();
  }
}

void work() {
  Read();
  // std::cerr<<' '<<n<<" kk\n";
  InitOrder();
  // std::cerr<<' '<<n<<" kk\n";
  InitLine();
  // std::cerr<<' '<<n<<" kk\n";
  Solve();
  // std::cerr<<' '<<n<<" kk\n";
  Clear();
}

int main() {
  std::ios::sync_with_stdio(0);
  int T = 1;
  std::cin >> T;
  for (; T--;) work();
  return 0;
}