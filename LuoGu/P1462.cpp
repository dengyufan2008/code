#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int f;
  vector<pair<int, int>> e;
} v[10001];
int n, m, b, l, r, mid;

int main() {
  cin >> n >> m >> b;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].f;
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({z, y}), v[y].e.push_back({z, x});
  }
  while (l <= r) {
    mid = (l + r) >> 1;
    
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
