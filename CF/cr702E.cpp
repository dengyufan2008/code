#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL a, n;
  bool operator<(const A &x) const {
    return a < x.a;
  }
} v[200001];

LL t, n, ans, a[200001], b[200001];

bool C(LL x, LL _x) {
  for (LL i = x + 1; i <= _x; i++) {
    if (a[i - 1] < v[i].a) {
      return false;
    }
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> v[i].a;
      v[i].n = i;
    }
    ans = 0;
    sort(v + 1, v + 1 + n);
    for (LL i = 1; i <= n; i++) {
      a[i] = a[i - 1] + v[i].a;
    }
    for (LL i = n, p = n; i >= 1; i--) {
      if (C(i, p)) {
        p = i;
        b[v[i].n] = t + 1;  //没想到吧这就是我的标记数组
        ans++;
      } else {
        break;
      }
    }
    cout << ans << endl;
    for (LL i = 1; i <= n; i++) {
      if (b[i] == t + 1) {
        cout << i << " ";
      }
    }
    cout << endl;
  }
  return 0;
}
