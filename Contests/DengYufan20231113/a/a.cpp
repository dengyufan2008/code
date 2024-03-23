#include <algorithm>
#include <ctime>
#include <iostream>
#define LL __int128_t

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct A {
  LL w, t, c, s;
} a[kMaxN];
struct V {
  LL c, s, t;
  bool e;
} v[kMaxN << 2];
int n, m, t, c[kMaxN];
LL ans;

void Tag(int p, int l, int r, int t) {
  v[p].c += (a[r].c - a[l - 1].c) * t;
  v[p].s += (a[r].s - a[l - 1].s) * t;
  v[p].t += t;
}

void Erase(int p) {
  v[p].c = v[p].s = v[p].t = 0, v[p].e = 1;
}

void Pushdown(int p, int l, int r) {
  if (v[p].e) {
    Erase(p << 1), Erase(p << 1 | 1), v[p].e = 0;
  }
  if (v[p].t) {
    int mid = l + r >> 1;
    Tag(p << 1, l, mid, v[p].t);
    Tag(p << 1 | 1, mid + 1, r, v[p].t);
    v[p].t = 0;
  }
}

LL Calc(int p, int l, int r, int k) {
  if (l == r) {
    v[p].c -= k, v[p].s -= a[l].w * k;
    return a[l].w * k;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  LL ans;
  if (v[p << 1].c >= k) {
    ans = Calc(p << 1, l, mid, k);
  } else {
    ans = v[p << 1].s + Calc(p << 1 | 1, mid + 1, r, k - v[p << 1].c);
    Erase(p << 1);
  }
  v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1, w, t; i <= m; i++) {
    cin >> w >> t;
    a[i].w = w, a[i].t = t;
  }
  sort(a + 1, a + m + 1, [](A i, A j) { return i.w < j.w; });
  for (int &i = t = 1; i <= m && ~a[i].t; i++) {
    a[i].c = a[i - 1].c + a[i].t;
    a[i].s = a[i - 1].s + a[i].w * a[i].t;
  }
  for (int i = 1; i <= n; i++) {
    Tag(1, 1, t - 1, 1);
    if (v[1].c < c[i]) {
      ans += v[1].s + (c[i] - v[1].c) * a[t].w;
      Erase(1);
    } else {
      ans += Calc(1, 1, t - 1, c[i]);
    }
  }
  cout << (long long)ans;
  return 0;
}
