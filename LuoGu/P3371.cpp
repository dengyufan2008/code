#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d = 0x7fffffff;
  bool b;
  vector<pair<int, int>> e;
} v[10001];
int n, m, s;

int main() {
  cin >> n >> m >> s;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
  }
  v[s].d = 0;
  for (int i = 2; i <= n; i++) {
    int mn = 0;
    for (int j = 1; j <= n; j++) {
      if (!v[j].b && v[mn].d > v[j].d) {
        mn = j;
      }
    }
    v[mn].b = 1;
    for (pair<int, int> i : v[mn].e) {
      v[i.first].d = min(v[i.first].d, v[mn].d + i.second);
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << v[i].d << " ";
  }
  return 0;
}
