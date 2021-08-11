#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d[2] = {0x7fffffff, 0x7fffffff};
  bool b[2];
  vector<pair<int, int>> e[2];
} v[1001];
int n, m, ans;

void M(int c) {
  v[1].d[c] = 0;
  for (int i = 2; i <= n; i++) {
    int mn = 0;
    for (int j = 1; j <= n; j++) {
      if (!v[j].b[c] && v[mn].d[c] > v[j].d[c]) {
        mn = j;
      }
    }
    v[mn].b[c] = 1;
    for (pair<int, int> j : v[mn].e[c]) {
      v[j.first].d[c] = min(v[j.first].d[c], v[mn].d[c] + j.second);
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e[0].push_back(make_pair(y, z));
    v[x].e[1].push_back(make_pair(x, z));
  }
  M(0), M(1);
  for (int i = 2; i <= n; i++) {
    ans += v[i].d[0] + v[i].d[1];
  }
  cout << ans << endl;
  return 0;
}
