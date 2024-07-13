#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int r, f[2];
  bool b;
  vector<int> e;
} v[6001];
int n, s;

void T(int f, int x) {
  for (int i : v[x].e) {
    if (f != i) {
      T(x, i);
      v[x].f[0] += max(v[i].f[0], v[i].f[1]);
      v[x].f[1] += v[i].f[0];
    }
  }
  v[x].f[1] += v[x].r;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].r;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> y >> x;
    v[y].b = 1, v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].b) {
      s = i;
    }
  }
  T(114514, s);
  cout << max(v[s].f[0], v[s].f[1]) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
