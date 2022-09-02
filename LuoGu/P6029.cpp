#include <iostream>
#include <vector>

using namespace std;

struct V {
  vector<pair<int, int>> e;
} v[51];
int n, m, k;

int main() {
  cin >> n >> m >> k;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  return 0;
}
