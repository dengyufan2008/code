#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, d, a, t;  // Data, AddMark, TimeMark
} v[400001];
int n, m, p, a[100001];

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

void SpreadTime(int s) {
  if (v[s].t > 1) {
    v[s << 1].d *= v[s].t;
    v[s << 1 | 1].d *= v[s].t;
    v[s << 1].a *= v[s].t, v[s << 1].t *= v[s].t;
    v[s << 1 | 1].a *= v[s].t, v[s << 1 | 1].t *= v[s].t;
    v[s].t = 1;
  }
}

void SpreadAdd(int s) {
  if (v[s].a > 0) {
    v[s << 1].a += v[s].a;
    v[s << 1 | 1].a += v[s].a;
    v[s << 1].d += (v[s << 1].r - v[s << 1].l + 1) * v[s].a;
    v[s << 1 | 1].d += (v[s << 1 | 1].r - v[s << 1 | 1].l + 1) * v[s].a;
    v[s].a = 0;
  }
}

void Time(int s, int l, int r, int x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d *= x, v[s].a *= x, v[s].t *= x;
    return;
  }
  SpreadTime(s);
  int mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Time(s << 1, l, mid, x);
  }
  if (mid < r) {
    Time(s << 1 | 1, mid + 1, r, x);
  }
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

void Add(int s, int l, int r, int x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d += (v[s].r - v[s].l + 1) * x, v[s].a += x;
    return;
  }
  SpreadAdd(s);
  int mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Add(s << 1, l, mid, x);
  }
  if (mid < r) {
    Add(s << 1 | 1, mid + 1, r, x);
  }
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

int Ask(int s, int l, int r) {
  if (v[s].l >= l && v[s].r <= r) {
    return v[s].d;
  }
  SpreadTime(s), SpreadAdd(s);
  int mid = (v[s].l + v[s].r) >> 1, ans = 0;
  if (mid >= l) {
    ans += Ask(s << 1, l, mid);
  }
  if (mid < r) {
    ans += Ask(s << 1 | 1, mid + 1, r);
  }
  return ans;
}

int main() {
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (int i = 1, c, x, y, k; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> k;
      Time(1, x, y, k);
    } else if (c == 2) {
      cin >> x >> y >> k;
      Add(1, x, y, k);
    } else {
      cin >> x >> y;
      cout << Ask(1, x, y) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
