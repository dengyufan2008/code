#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d, x;
} e[2001];
struct B {
  int et, d = 2e9 + 1;
} v[2001];
int n, m;
bool b[2001];

int S(int x, int y, int s) {
  if (b[x]) {
    return 2e9 + 1;
  }
  if (x == y) {
    return s;
  }
  b[x] = true;
  int ans = 2e9 + 1;
  for (int i = v[x].et; i; i = e[i].p) {
    ans = min(ans, S(e[i].d, y, s + e[i].x));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    e[i] = {v[a].et, b, c}, v[a].et = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = v[i].et; j; j = e[j].p) {
      fill(&b[0], &b[2000] + 1, false);
      v[i].d = min(v[i].d, e[j].x + S(e[j].d, i, 0));
    }
    cout << (v[i].d >= 2e9 + 1 ? -1 : v[i].d) << endl;
  }
  return 0;
}
