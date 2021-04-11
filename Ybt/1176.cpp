#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL e;
  double v;
} a[101];

int n, k;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].e >> a[i].v;
  }
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (a[j].v > a[j + 1].v) {
        swap(a[j].v, a[j + 1].v), swap(a[j].e, a[j + 1].e);
      }
    }
  }
  cout << a[k].e << " " << a[k].v;
  return 0;
}
