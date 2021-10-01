#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int f[2];  // 0:该节点没有士兵  1:该节点有士兵
  vector<int> e;
} v[1500];
int n;

void T(int f, int x) {
  for (int i : v[x].e) {
    if (f != i) {
      T(x, i);
      v[x].f[0] += v[i].f[1];
      v[x].f[1] += min(v[i].f[0], v[i].f[1]);
    }
  }
  v[x].f[1]++;
}

int main() {
  cin >> n;
  for (int i = 0, x, y, z; i < n; i++) {
    cin >> x >> y;
    for (int j = 1; j <= y; j++) {
      cin >> z;
      v[i].e.push_back(z), v[z].e.push_back(i);
    }
  }
  T(114514, 0);
  cout << min(v[0].f[0], v[0].f[1]) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
