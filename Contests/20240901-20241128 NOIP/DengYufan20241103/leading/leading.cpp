#include <fstream>
#define LL long long

using namespace std;

ifstream cin("leading.in");
ofstream cout("leading.out");

const int kMaxN = 5e5 + 1;
struct E {
  int c, w;
} a[kMaxN], b[kMaxN];
struct Ans {
  int l1, r1, l2, r2;
  LL w;
} ans;
int n, m, al[kMaxN], ar[kMaxN];
LL dl[kMaxN], dr[kMaxN], f[kMaxN], g[kMaxN];

void Update(int l1, int r1, int l2, int r2, LL w) {
  if (ans.w < w) {
    ans = {l1, r1, l2, r2, w};
  }
}

void Init() {
  static int mid, o[kMaxN << 1];
  LL w = 0;
  for (int i = 1; i <= n + m; i++) {
    o[i] = 0;
  }
  for (int i = 1; i <= max(n, m); i++) {
    dl[i] = dr[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    w += a[i].w, o[a[i].c] = i;
  }
  Update(1, n, 0, 0, w), w = w + 1 >> 1;
  for (int i = 1; i <= n; i++) {
    w -= a[i].w;
    if (w <= 0) {
      mid = i;
      break;
    }
  }
  dl[mid] = a[mid].w;
  for (int i = mid - 1; i >= 1; i--) {
    dl[i] = dl[i + 1] + a[i].w;
  }
  if (mid < n) {
    dr[mid + 1] = a[mid + 1].w;
    for (int i = mid + 2; i <= n; i++) {
      dr[i] = dr[i - 1] + a[i].w;
    }
  }
  for (int i = 1; i <= m; i++) {
    al[i] = 1, ar[i] = n;
    if (o[b[i].c]) {
      if (o[b[i].c] <= mid) {
        al[i] = o[b[i].c] + 1;
      } else {
        ar[i] = o[b[i].c] - 1;
      }
    }
  }
}

void Divide(int l, int r) {
  static int x, h, t, pl[kMaxN], pr[kMaxN], ql[kMaxN], qr[kMaxN];
  static pair<LL, int> q[kMaxN];
  static LL w;
  if (l > r) {
    return;
  }
  int mid = l + r >> 1;
  pl[mid] = al[mid], pr[mid] = ar[mid];
  for (int i = mid - 1; i >= l; i--) {
    pl[i] = max(pl[i + 1], al[i]);
    pr[i] = min(pr[i + 1], ar[i]);
  }
  ql[mid] = al[mid], qr[mid] = ar[mid];
  for (int i = mid + 1; i <= r; i++) {
    ql[i] = max(ql[i - 1], al[i]);
    qr[i] = min(qr[i - 1], ar[i]);
  }

  w = b[mid].w, f[mid] = w + dr[pr[mid]];  // <=, <=
  for (int i = mid - 1; i >= l; i--) {
    w += b[i].w, f[i] = w + dr[pr[i]];
  }
  w = 0, g[mid] = dl[ql[mid]];
  for (int i = mid + 1; i <= r; i++) {
    w += b[i].w, g[i] = w + dl[ql[i]];
  }
  h = 1, t = 0;
  for (int i = l, j = r, k = r; i <= mid; i++) {
    for (; j >= mid && ql[j] >= pl[i]; j--) {
      for (; t >= h && q[t].first <= g[j]; t--) {
      }
      q[++t] = {g[j], j};
    }
    for (; k >= mid && qr[k] <= pr[i]; k--) {
    }
    for (; h <= t && q[h].second > k; h++) {
    }
    if (h <= t) {
      Update(ql[q[h].second], pr[i], i, q[h].second, f[i] + q[h].first);
    }
  }

  w = b[mid].w, f[mid] = w;  // <=, >=
  for (int i = mid - 1; i >= l; i--) {
    w += b[i].w, f[i] = w;
  }
  w = 0, g[mid] = dl[ql[mid]] + dr[qr[mid]];
  for (int i = mid + 1; i <= r; i++) {
    w += b[i].w, g[i] = w + dl[ql[i]] + dr[qr[i]];
  }
  w = 0;
  for (int i = l, j = r, k = r, jk = r; i <= mid; i++) {
    for (; j >= mid && ql[j] >= pl[i]; j--) {
    }
    for (; k >= mid && qr[k] <= pr[i]; k--) {
    }
    for (; jk > j && jk > k; jk--) {
      if (w < g[jk]) {
        w = g[jk], x = jk;
      }
    }
    Update(ql[x], qr[x], i, x, f[i] + w);
  }

  w = b[mid].w, f[mid] = w + dl[pl[mid]] + dr[pr[mid]];  // >=, <=
  for (int i = mid - 1; i >= l; i--) {
    w += b[i].w, f[i] = w + dl[pl[i]] + dr[pr[i]];
  }
  w = 0, g[mid] = 0;
  for (int i = mid + 1; i <= r; i++) {
    w += b[i].w, g[i] = w;
  }
  w = 0;
  for (int i = mid, j = mid, k = mid, jk = mid; i >= l; i--) {
    for (; j <= r && ql[j] <= pl[i]; j++) {
    }
    for (; k <= r && qr[k] >= pr[i]; k++) {
    }
    for (; jk < j && jk < k; jk++) {
      if (w < g[jk]) {
        w = g[jk], x = jk;
      }
    }
    Update(pl[i], pr[i], i, x, f[i] + w);
  }

  w = b[mid].w, f[mid] = w + dl[pl[mid]];  // >=, >=
  for (int i = mid - 1; i >= l; i--) {
    w += b[i].w, f[i] = w + dl[pl[i]];
  }
  w = 0, g[mid] = dr[qr[mid]];
  for (int i = mid + 1; i <= r; i++) {
    w += b[i].w, g[i] = w + dr[qr[i]];
  }
  h = 1, t = 0;
  for (int i = mid, j = mid, k = mid; i >= l; i--) {
    for (; j <= r && ql[j] <= pl[i]; j++) {
      for (; t >= h && q[t].first <= g[j]; t--) {
      }
      q[++t] = {g[j], j};
    }
    for (; k <= r && qr[k] >= pr[i]; k++) {
    }
    for (; h <= t && q[h].second < k; h++) {
    }
    if (h <= t) {
      Update(pl[i], qr[q[h].second], i, q[h].second, f[i] + q[h].first);
    }
  }

  Divide(l, mid - 1), Divide(mid + 1, r);
}

void Solve() { Init(), Divide(1, m), swap(ans.l1, ans.l2), swap(ans.r1, ans.r2); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].c;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i].w;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i].c;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i].w;
  }
  Solve(), swap(n, m), swap(a, b), Solve();
  cout << ans.w << '\n';
  ans.l1 > ans.r1 && (ans.l1 = ans.r1 = 0);
  ans.l2 > ans.r2 && (ans.l2 = ans.r2 = 0);
  // cout << ans.l1 << ' ' << ans.r1 << '\n';
  // cout << ans.l2 << ' ' << ans.r2 << '\n';
  return 0;
}
