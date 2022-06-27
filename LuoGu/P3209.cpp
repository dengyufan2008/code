#include <iostream>
#include <stack>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d, l, r;
  vector<int> e;
} v[401];
int t, n, m, k, l;
pair<int, int> a[10001];

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      v[i].d = v[i].l = v[i].r = 0;
      v[i].e.clear();
    }
    for (int i = 1; i <= m; i++) {
      cin >> a[i].first >> a[i].second;
    }
    for (int i = 1; i <= n; i++) {
      
    }
  }
  return 0;
}
