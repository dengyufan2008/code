#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, l, s1, s2, a[11];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  while (k--) {
    l = s1 = s2 = 0;
    while (n) {
      a[++l] = n % 10, n /= 10;
    }
    sort(a + 1, a + l + 1);
    for (int i = 1; i <= l; i++) {
      s1 = s1 * 10 + a[l - i + 1], s2 = s2 * 10 + a[i];
    }
    n = s1 - s2;
  }
  cout << n << endl;
  return 0;
}
