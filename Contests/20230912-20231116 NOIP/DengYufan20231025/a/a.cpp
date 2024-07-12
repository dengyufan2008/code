#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxM = kMaxN * 48, kMaxV = 1e9;
struct V {
  int l, r, t;
  LL d;
} v[kMaxM];
int n, m, s, k, a[kMaxN];
LL ans;

void Pushdown(int p, int l, int r) {
  int mid = l + r >> 1;
  if (v[p].t) {
    !v[p].l && (v[p].l = ++k);
    v[v[p].l].d += 1LL * v[p].t * (mid - l + 1);
    v[v[p].l].t += v[p].t;
    !v[p].r && (v[p].r = ++k);
    v[v[p].r].d += 1LL * v[p].t * (r - mid);
    v[v[p].r].t += v[p].t;
    v[p].t = 0;
  }
}

void Add(int &p, int l, int r, int _l, int _r) {
  !p && (p = ++k);
  if (l >= _l && r <= _r) {
    v[p].d += r - l + 1, v[p].t++;
    return;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(v[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    Add(v[p].r, mid + 1, r, _l, _r);
  }
  v[p].d = v[v[p].l].d + v[v[p].r].d;
}

LL Ask(int p, int l, int r, int _l, int _r) {
  if (!p) {
    return 0;
  } else if (l >= _l && r <= _r) {
    return v[p].d;
  }
  int mid = l + r >> 1;
  LL ans = 1LL * (min(r, _r) - max(l, _l) + 1) * v[p].t;
  if (mid >= _l) {
    ans += Ask(v[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Ask(v[p].r, mid + 1, r, _l, _r);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    if (a[i] != a[i + 1]) {
      Add(s, 1, kMaxV, min(a[i], a[i + 1]), max(a[i], a[i + 1]) - 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i < n && a[i] < a[i + 1] || i > 1 && a[i] > a[i - 1]) {
      ans = max(ans, max(Ask(s, 1, kMaxV, max(a[i] - m, 1), max(a[i] - 1, 1)), Ask(s, 1, kMaxV, a[i], min(a[i] + m - 1, kMaxV))));
    }
    if (i < n && a[i] > a[i + 1] || i > 1 && a[i] < a[i - 1]) {
      ans = max(ans, max(Ask(s, 1, kMaxV, max(a[i] - m + 1, 1), a[i]), Ask(s, 1, kMaxV, min(a[i] + 1, kMaxV), min(a[i] + m, kMaxV))));
    }
  }
  cout << ans;
  return 0;
}
