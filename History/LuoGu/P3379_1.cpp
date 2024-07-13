#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d;
  vector<int> e;
} v[500001];
int n, m, s, x, y, d[500001][24];

void T(int f, int x) {
  for (int i : v[x].e) {
    if (i != f) {
      v[i].d = v[x].d + 1, d[i][0] = x;
      T(x, i);
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
  for (int i = 1; i <= 23; i++) {
    for (int j = 1; j <= n; j++) {
      d[j][i] = d[d[j][i - 1]][i - 1];
    }
  }
  while (m--) {
    cin >> x >> y;
    if (v[x].d < v[y].d) {
      swap(x, y);
    }
    for (int i = 23; i >= 0; i--) {
      if ((1 << i) & (v[x].d - v[y].d)) {
        x = d[x][i];
      }
    }
    for (int i = 23, h = v[x].d; i >= 0; i--) {
      if (h - (1 << i) >= 0 && d[x][i] != d[y][i]) {
        x = d[x][i], y = d[y][i];
      }
    }
    cout << (x == y ? x : d[x][0]) << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
