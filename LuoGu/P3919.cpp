#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, v;
} v[8000001];
int n, m, k1, k2, a[1000001], h[1000001];

void Copy(int &p) {
  v[++k1] = v[p];
  p = k1;
}

void Build(int &p, int l, int r) {
  p = ++k1;
  if (l == r) {
    v[p].v = a[l];
    return;
  }
  int mid = l + r >> 1;
  Build(v[p].l, l, mid), Build(v[p].r, mid + 1, r);
}

void Change(int &p, int l, int r, int x, int y) {
  Copy(p);
  if (l == r) {
    v[p].v = y;
  }
  int mid = l + r >> 1;

}

int Ask(int &p, int l, int r, int x) {

}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(h[0], 1, n);
  for (int i = 1, o, x, y, z; i <= m; i++) {
    cin >> x >> o >> y;
    if (o == 1) {
      cin >> z;
      Change(h[++k2] = h[x], 1, n, y, z);
    } else {
      cout << Ask(h[++k2] = h[x], 1, n, y) << '\n';
    }
  }
  return 0;
}
