#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d, f[301];
  bool b;
  vector<int> e;
} v[301];
int n, m, ans[301];

void T(int f, int x) {
  for (int i : v[x].e) {
    if (f != i) {
      T(x, i);
      for (int j = 0; j <= 300; j++) {
        for (int k = 0; k <= 300; k++) {
          v[x].f[j] = max(v[x].f[j], v[x].f[j - k] + v[i].f[k]);
        }
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, k; i <= n; i++) {
    cin >> k >> v[i].d;
    v[i].b = k, v[i].e.push_back(k), v[k].e.push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].b) {
      T(114514, i);
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
