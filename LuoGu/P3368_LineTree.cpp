#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, d, s;
} v[2000001];
int n, m, a[500001];

void Build(int s, int l, int r) {
  v[s].l = l, v[s].r = r;
  if (l == r) {
    v[s].d = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  Build(s << 1, l, mid), Build(s << 1 | 1, mid + 1, r);
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

void Spread(int s) {
  if (v[s].s) {
    v[s << 1].d += (v[s << 1].r - v[s << 1].l + 1) * v[s].s;
    v[s << 1].s += v[s].s;
    v[s << 1 | 1].d += (v[s << 1 | 1].r - v[s << 1 | 1].l + 1) * v[s].s;
    v[s << 1 | 1].s += v[s].s;
    v[s].s = 0;
  }
}

void Change(int s, int l, int r, int x) {
  if (l <= v[s].l && r >= v[s].r) {
    v[s].d += (v[s].r - v[s].l + 1) * x, v[s].s += x;
    return;
  }
  Spread(s);
  int mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Change(s << 1, l, r, x);
  }
  if (mid < r) {
    Change(s << 1 | 1, l, r, x);
  }
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

int Ask(int s, int l, int r) {
  if (l <= v[s].l && r >= v[s].r) {
    return v[s].d;
  }
  Spread(s);
  int mid = (v[s].l + v[s].r) >> 1, ans = 0;
  if (mid >= l) {
    ans += Ask(s << 1, l, r);
  }
  if (mid < r) {
    ans += Ask(s << 1 | 1, l, r);
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (int i = 1, p, x, y, k; i <= m; i++) {
    cin >> p;
    if (p == 1) {
      cin >> x >> y >> k;
      Change(1, x, y, k);
    } else {
      cin >> x;
      cout << Ask(1, x, x) <<'\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
