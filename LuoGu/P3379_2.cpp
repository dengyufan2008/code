#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int p, d;
  vector<int> e;
} v[500001];
int n, m, s, x, y, ans, k, d[1000001][21];

void T(int f, int x) {
  d[++k][0] = x;
  v[x].p = k;
  for (int i : v[x].e) {
    if (i != f) {
      v[i].d = v[x].d + 1;
      T(x, i);
      d[++k][0] = x;
    }
  }
}

int main() {
  cin >> n >> m >> s;
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, s);
  v[0].d = 0x7fffffff;
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= k; j++) {
      d[j][i] = j + (1 << (i - 1)) > k || v[d[j][i - 1]].d < v[d[j + (1 << (i - 1))][i - 1]].d ? d[j][i - 1] : d[j + (1 << (i - 1))][i - 1];
    }
  }
  while (m--) {
    cin >> x >> y;
    x = v[x].p, y = v[y].p;
    if (x > y) {
      swap(x, y);
    }
    int lg = log2(y - x);
    cout << (v[d[x][lg]].d < v[d[y - (1 << lg)][lg]].d ? d[x][lg] : d[y - (1 << lg)][lg]) << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
