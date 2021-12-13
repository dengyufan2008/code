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

void Time(int s, int l, int r, int x) {
  ;
}

void Add(int s, int l, int r, int x) {
  ;
}

int Ask(int s, int l, int r) {
  ;
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
