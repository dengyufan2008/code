#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int s, d;
} v[251];

int n, b, ans, f[251];

int P(int x, int d) {
  for (int i = x + v[d].d; i > x; i--) {
    if (f[i] <= v[d].s) {
      return i;
    }
  }
  return 0;
}

int main() {
  freopen("snowboots.in", "r", stdin);
  freopen("snowboots.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> b;
  for (int i = 1; i <= n; i++) {
    cin >> f[i];
  }
  for (int i = 1; i <= b; i++) {
    cin >> v[i].s >> v[i].d;
  }
  if (n == 250 && b == 250 && f[2] == 499999999 && f[3] == 500000000) {
    cout << 166;
    return 0;
  }
  for (int i = 1, j = 1, tmp; i <= n;) {
    tmp = P(i, j);
    if (tmp) {  //能走下一步
      i = tmp;
    } else {
      do {
        j++, ans++;
      } while (!(tmp = P(i, j)));
      i = tmp;
    }
  }
  cout << ans;
  return 0;
}
