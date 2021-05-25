#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d, x;
} e[2001];
struct B {
  int et, d = 2147483647, k;
} v[2001];
int n, m;

int M(int x, int y, int s) {
  if (x == y) {
    return s ? s : v[x].k ? v[x].k : 2147483647;
  }
  int ans = 2147483647;
  for (int i = v[x].et; i; i = e[i].p) {
    ans = min(ans, M(e[i].d, y, s + e[i].x));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    e[i] = {v[a].et, b, c}, v[a].et = i, v[a].k = (v[a].k || a == b) * c;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      v[i].d = min(v[i].d, M(i, j, 0) + M(j, i, 0));
    }
    cout << v[i].d << endl;
  }
  return 0;
}
