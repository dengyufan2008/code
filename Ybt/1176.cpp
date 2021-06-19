#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  string e;
  double v;
  bool operator<(const A a) const {
    return v > a.v;
  }
} a[101];

int n, k;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].e >> a[i].v;
  }
  sort(a + 1, a + n + 1);
  cout << a[k].e << " " << a[k].v << endl;
  return 0;
}
