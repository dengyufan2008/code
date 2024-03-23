#include <bits/stdc++.h>
using namespace std;
namespace QYB {
  int n, m, ans = 1, s[3005], d[6005]; bool vis[3005][3005];
  // bool debug = false;
  struct hashint {
    using ull = unsigned long long;
    using uint = unsigned int;
    static const uint P1 = 1000000007, P2 = 1000000009; uint a, b;
    hashint(uint _x = 0): a(_x), b(_x) { }
    hashint(uint _a, uint _b): a(_a), b(_b) { }
    hashint operator+(hashint x) { return {(a + x.a) % P1, (b + x.b) % P2}; }
    hashint operator-(hashint x) { return {(a - x.a + P1) % P1, (b - x.b + P2) % P2}; }
    hashint operator*(hashint x) { return {(ull)a * x.a % P1, (ull)b * x.b % P2}; }
    hashint &operator+=(hashint x) { return *this = *this + x; }
    hashint &operator-=(hashint x) { return *this = *this - x; }
    hashint &operator*=(hashint x) { return *this = *this * x; }
    bool operator==(hashint x) { return a == x.a && b == x.b; }
    bool operator!=(hashint x) { return a != x.a || b != x.b; }
  } h[3005][3005], rev[3005], pw[3005], spw[3005], ipw[3005];
  const hashint bs = {137, 157}, ibs = {58394161, 566878986};
  hashint gethash(int l, int len) {
    if (l < 1 || l + len - 1 > n) return 0;
    return (rev[l] - rev[l + len]) * ipw[n + 1 - l - len];
  } namespace S1 {
    int sum[12005]; hashint ssum[12005]; int mul[12005];
    void build(int p, int l, int r) {
      sum[p] = 0; ssum[p] = mul[p] = 0;
      if (l == r) return; int mid = l + r >> 1;
      build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
    } void pushtag(int p, int x) {
      mul[p] += x; ssum[p] *= pw[x];
    } void pushdown(int p) {
      if (mul[p] != 0) pushtag(p << 1, mul[p]), pushtag(p << 1 | 1, mul[p]), mul[p] = 0;
    } void update(int p) {
      sum[p] = sum[p << 1] + sum[p << 1 | 1];
      ssum[p] = ssum[p << 1] + ssum[p << 1 | 1];
    } void modify1(int p, int l, int r, int x, hashint d) {
      if (l == r) return sum[p] += 1, ssum[p] += d, void();
      int mid = l + r >> 1; pushdown(p);
      if (x <= mid) modify1(p << 1, l, mid, x, d);
      else modify1(p << 1 | 1, mid + 1, r, x, d * pw[sum[p << 1]]);
      return update(p);
    } void modify2(int p, int l, int r, int L, int R) {
      if (R < l || r < L) return;
      if (L <= l && r <= R) return pushtag(p, 1);
      int mid = l + r >> 1; pushdown(p);
      modify2(p << 1, l, mid, L, R);
      modify2(p << 1 | 1, mid + 1, r, L, R);
      return update(p);
    } /*int query1(int p, int l, int r, int L, int R) {
      if (R < l || r < L) return 0;
      if (L <= l && r <= R) return sum[p];
      int mid = l + r >> 1; pushdown(p);
      return query1(p << 1, l, mid, L, R) + query1(p << 1 | 1, mid + 1, r, L, R);
    } hashint query2(int p, int l, int r, int L, int R) {
      if (R < l || r < L) return 0;
      if (L <= l && r <= R) return ssum[p];
      int mid = l + r >> 1; pushdown(p);
      return query2(p << 1, l, mid, L, R) + query2(p << 1 | 1, mid + 1, r, L, R);
    } */
    int query1(int p, int l, int r, int c, int f, int y) {
      if (sum[p] <= c) return 0;
      if (c == 0 && ssum[p] * ipw[y] == gethash(f, sum[p])) return sum[p];
      if (l == r && c == 0) return 0;
      int mid = l + r >> 1; pushdown(p);
      int tmp = query1(p << 1 | 1, mid + 1, r, c, f, y + sum[p << 1]);
      if (tmp == max(0, sum[p << 1 | 1] - c)) {
        tmp += query1(p << 1, l, mid, max(0, c - sum[p << 1 | 1]), f + tmp, y);
      } return tmp;
    } int query2(int p, int l, int r, int c, int f, int y) {
      // if (debug) cerr << p << " " << l << " " << r << " " << c << " " << f << " " << y << endl;
      if (sum[p] <= c) return 0;
      if (c == 0 && ssum[p] * ipw[y] == gethash(f - sum[p] + 1, sum[p])) return sum[p];
      if (l == r && c == 0) return 0;
      int mid = l + r >> 1; pushdown(p);
      int tmp = query2(p << 1, l, mid, c, f, y);
      // if (debug) cerr << "res " << (p << 1) << " " << tmp << endl;
      if (tmp == max(0, sum[p << 1] - c)) {
        tmp += query2(p << 1 | 1, mid + 1, r, max(0, c - sum[p << 1]), f - tmp, y + sum[p << 1]);
      } return tmp;
    } void work() {
      int q[3005], p[3005];
      for (int i = 1; i <= n; i++) q[i] = i;
      sort(q + 1, q + n + 1, [](int i, int j) { return s[i] < s[j]; });
      for (int i = 1; i <= n; i++) p[q[i]] = i;
      for (int l = 1; l <= n; l++) {
        build(1, 1, n); int maxn = 0, maxcnt = 0, minn = m + 1, mincnt = 0;
        for (int r = l; r <= n; r++) {
          if (s[r] > maxn) maxn = s[r], maxcnt = 1;
          else if (s[r] == maxn) maxcnt++;
          if (s[r] < minn) minn = s[r], mincnt = 1;
          else if (s[r] == minn) mincnt++;
          modify1(1, 1, n, p[r], s[r]);
          modify2(1, 1, n, p[r] + 1, n);
          hashint tmp = h[l][r] = ssum[1];
          int p = query1(1, 1, n, maxcnt, r + 1, 0);
          if (r - maxcnt - p + 1 == l) vis[r - maxcnt - p + 1][r + p] = true;
          ans = max(ans, 2 * p + maxcnt);
          p = query2(1, 1, n, mincnt, l - 1, 0);
          if (l + mincnt + p - 1 == r) vis[l - p][l + mincnt + p - 1] = true;
          ans = max(ans, 2 * p + mincnt);
        }
      }
    }
  } char getchar() {
    static char buf[1 << 25], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 25, stdin)) == buf? EOF: *p1++;
  } int read() {
    int res = 0; char ch = getchar();
    while (ch < 48 || ch > 57) ch = getchar();
    while (ch >= 48 && ch <= 57) res = res * 10 + ch - 48, ch = getchar();
    return res;
  } void manacher() {
    static int a[6005]; a[0] = -1; a[2 * n + 2] = -2;
    for (int i = 1; i <= n; i++) a[2 * i] = s[i];
    for (int i = 2, p = 1; i <= 2 * n + 1; i++) {
      int t = max(0, 2 * p - i);
      d[i] = max(0, min(p + d[p], i + d[t]) - i);
      while (a[i + d[i] + 1] == a[i - d[i] - 1]) ++d[i];
      if (i + d[i] > p + d[p]) p = i;
    }
  } void init() {
    manacher(); pw[0] = spw[0] = ipw[0] = 1;
    for (int i = 1; i <= n; i++) {
      spw[i] = spw[i - 1] + (pw[i] = pw[i - 1] * bs);
      ipw[i] = ipw[i - 1] * ibs;
    } for (int i = n; i >= 1; i--) {
      rev[i] = rev[i + 1] + pw[n - i] * s[i];
    } S1::work();
  } void solve1() {
    static int cnt[3005];
    for (int i = 1; i <= n; i++) ++cnt[s[i]];
    for (int i = 1; i <= n; i++) ans = max(ans, cnt[i]);
  } void solve2() {
    for (int i = 1; i <= n; i++) vis[i][i - 1] = true;
    for (int l = 1; l <= n; l++) {
      for (int r = l; r <= n; r++) {
        if (l == r) { vis[l][r] = true; continue; }
        if (s[l] == s[r]) vis[l][r] |= vis[l + 1][r - 1];
        int p = l + r - d[l + r] - 1 >> 1;
        if (p >= l) vis[l][r] |= h[l][p] == gethash(l + r - p, p - l + 1);
        if (vis[l][r]) ans = max(ans, r - l + 1);
      }
    }
  } void solve3() {
    for (int i = 2; i <= 2 * n; i++) {
      int l = i - d[i] + 1 >> 1, r = i + d[i] - 1 >> 1;
      priority_queue<int> q;
      for (int j = 1, i = l - 1; j; j++) {
        if (r + j == n + 1) { ans = max(ans, r - l - 1 + 2 * j); break; }
        if (j != 1 && s[r + j] > s[r + j - 1]) { ans = max(ans, r - l - 1 + 2 * j); break; }
        while (i >= 1 && (q.empty() || q.top() < s[r + j])) q.push(s[i--]);
        if (q.empty() || q.top() != s[r + j]) { ans = max(ans, r - l - 1 + 2 * j); break; } q.pop();
      } while (!q.empty()) q.pop();
      for (int j = 1, i = r + 1; j; j++) {
        if (l - j == 0) { ans = max(ans, r - l - 1 + 2 * j); break; }
        if (j != 1 && s[l - j] < s[l - j + 1]) { ans = max(ans, r - l - 1 + 2 * j); break; }
        while (i <= n && (q.empty() || -q.top() > s[l - j])) q.push(-s[i++]);
        if (q.empty() || -q.top() != s[l - j]) { ans = max(ans, r - l - 1 + 2 * j); break; } q.pop();
      }
    }
  } int main() {
    freopen("kanzenkankaku.in", "r", stdin);
    freopen("kanzenkankaku.out", "w", stdout);
    n = read(); m = read();
    for (int i = 1; i <= n; i++) s[i] = read();
    init();
    solve1();
    solve2();
    solve3();
    return !printf("%d\n", ans);
  }
} int main() { return QYB::main(); }