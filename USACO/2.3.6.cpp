/*
ID: dengyuf1
TASK: concom
LANG: C++
*/
#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  int d[101];
  vector<pair<int, int>> e;
} v[101];
int n;

int main() {
  // freopen("concom.in", "r", stdin);
  // freopen("concom.out", "w", stdout);
  cin >> n;
  for (int i = 1, x, y, z; i <= n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({z, y});
  }
  for (int i = 1; i <= n; i++) {
    
    for (int j = 1; j <= n; j++) {
      if (i != j && v[j].d[i] > 50) {
        cout << i << " " << j << endl;
      }
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
