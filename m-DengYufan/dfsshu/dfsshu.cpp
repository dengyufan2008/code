#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int b;
  vector<int> e;
} v[1000000];
int n, m, d;

int T(int f, int x, int d) {
  int ans = 1;
  v[x].b = d;
  for (int i : v[x].e) {
    if (f != i) {
      ans += T(x, i, d);
    }
  }
  return ans;
}

int main() {
  // freopen("dfsshu.in", "r", stdin);
  // freopen("dfsshu.out", "w", stdout);
  cin >> n >> m >> d;
  for (int i = 0, u; i < n; i++) {
    cin >> u;
    v[i].e.push_back(u), v[u].e.push_back(i);
  }
  for (int i = 0; i < n; i++) {
    if (v[i].b == 0) {
      T(-1, i, T(-1, i, 0) < m ? -1 : 1);
    }
  }
  if (d < 2) {
  } else {
    int s = n;
    for (; s >= 1 && v[s].b == -1; s--) {
    }
    if (!s) {
      cout << '?' << endl;
      return 0;
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
