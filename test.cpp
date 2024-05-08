#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int kMaxN = 40001, kMaxL = 16;
struct V {
  int w, r, l0, l1, f[kMaxL];
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, b, a[kMaxN];
vector<int> l;
mt19937 Rand(715);

void S(int f, int x) {
  static int k = 0;
  v[x].r = ++k, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, b = sqrt(n);
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, 1);
  for (int i = 1; i <= b; i++) {
    int &x = a[i] = Rand();
    for (; v[x].b; x = Rand()) {
    }
    v[x].b = 1;
  }
  sort(a + 1, a + b + 1, [](int i, int j) {
    return v[i].r < v[j].r;
  });
  l.push_back(1);
  for (int i = 1 + (a[1] == 1); i <= n; i++) {
    ;
  }
  return 0;
}
