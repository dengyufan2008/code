#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, k, tot, a[3];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  while (n) {
    k++;
    a[n % 10 % 3]++;
    tot = (tot + n % 10) % 3;
    n /= 10;
  }
  if (!tot) {
    cout << 0 << endl;
  } else if (a[tot] && k > 1) {
    cout << 1 << endl;
  } else if (a[3 - tot] > 1 && k > 2) {
    cout << 2 << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}
