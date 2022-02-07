#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V1 {
  int v;
  vector<int> e;
} v1[501];
struct V2 {
  int v;
  vector<int> e;
} v2[501];
int n, m, e, ans;

bool T(int x, int v) {
  if (v1[x].v != v) {
    v1[x].v = v;
    for (int i : v1[x].e) {
      if (!v2[i].v || T(v2[i].v, v)) {
        v2[i].v = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m >> e;
  for (int i = 1, x, y; i <= e; i++) {
    cin >> x >> y;
    v1[x].e.push_back(y), v2[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    ans += T(i, i);
  }
  cout << ans;
  return 0;
}
