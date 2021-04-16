#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int d;
  bool operator<(const A &a) const {
    return d % 2 > a.d % 2 || d < a.d;
  }
} a[2001];

int t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].d;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      cout << a[i].d << " ";
    }
    cout << endl;
  }
  return 0;
}
