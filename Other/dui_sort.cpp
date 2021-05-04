#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1;

struct A {
  int _n, n, a[kMaxN];

} h;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h.n;
  for (int i = 1, tmp; i <= h._n; i++) {
    cin >> tmp;

  }
  h.Sort();
  for (int i = 1; i <= h._n; i++) {
    cout << h.a[i] << " ";
  }
  return 0;
}
