#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct {
  int d, l, c;
  vector<int> e;
} v[20001];
int n, m;
vector<int> ans;

void S(int f, int x) {
  if (v[x].d) {
    v[f].l = min(v[f].l, v[x].d);
    return;
  }
  v[x].d = v[x].l = v[f].d + 1;
  for (int i : v[x].e) {
    S(x, i);
  }
  if (v[x].c - !f >= 1) {
    ans.push_back(x);
  }
  v[f].l = min(v[f].l, v[x].l);
  v[f].c += v[f].d <= v[x].l;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    S(0, i);
  }
  sort(ans.begin(), ans.end());
  for (int i : ans) {
    cout << i << '\n';
  }
  return 0;
}
