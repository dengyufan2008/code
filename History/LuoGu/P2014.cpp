#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int f[301];
  vector<int> e;
} v[301];
int n, m;

void T(int f, int x) {
  for (int i : v[x].e) {
    if (f != i) {
      T(x, i);
    }
  }
  for (int i : v[x].e) {
    if (f != i) {
      for (int j = m; j >= 1; j--) {
        for (int k = 0; k < j; k++) {
          v[x].f[j] = max(v[x].f[j], v[x].f[j - k] + v[i].f[k]);
        }
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, k; i <= n; i++) {
    cin >> k >> v[i].f[1];
    v[i].e.push_back(k), v[k].e.push_back(i);
  }
  m++;
  T(114514, 0);
  cout << v[0].f[m] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
