// #include <ctime>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 2e5 + 2;
struct V {
  LL w, l, r;
} v[kMaxN * 48];
LL n, m, k, _v, ans, r[kMaxN], c[kMaxN], s[kMaxN];
pair<LL, LL> a[kMaxN];

void Add(LL &p, LL l, LL r, LL x) {
  v[++_v] = v[p], p = _v;
  if (l == r) {
    v[p].w++;
    return;
  }
  LL mid = l + r >> 1;
  mid >= x ? Add(v[p].l, l, mid, x) : Add(v[p].r, mid + 1, r, x);
  v[p].w = v[v[p].l].w + v[v[p].r].w;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r) {
  if (!p) {
    return 0;
  } else if (l >= _l && r <= _r) {
    return v[p].w;
  }
  LL mid = l + r >> 1, ans = 0;
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
  cin >> n >> m >> k;
  fill(&r[1], &r[n] + 1, m + 1), fill(&c[1], &c[m] + 1, n + 1);
  for (LL i = 1; i <= k; i++) {
    cin >> a[i].first >> a[i].second;
    r[a[i].first] = min(r[a[i].first], a[i].second);
    c[a[i].second] = min(c[a[i].second], a[i].first);
  }
  for (LL i = 1, j = 0; i <= n; i++) {
    j |= r[i] == 1;
    if (j) {
      r[i] = 1;
    }
  }
  for (LL i = 1, j = 0; i <= m; i++) {
    j |= c[i] == 1;
    if (j) {
      c[i] = 1;
    }
  }
  for (LL i = m; i >= 1; i--) {
    Add(s[i] = s[i + 1], 1, m + 1, c[i]);
  }
  ans = n * m;
  for (LL i = 1; i <= n; i++) {
    ans -= Ask(s[r[i]], 1, m + 1, 1, i);
  }
  cout << ans;
  // cout << '\n' << clock();
  return 0;
}
