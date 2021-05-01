#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, k, x, sum, ans, mul, m, p[100001];
bool b[100001];

void M() {
    for (LL i = 2; i < 100001; i++) {
    if (!b[i]) {
      p[++m] = i;
      for (LL j = i; j < 100001; j += i) {
        b[j] = true;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  M();
  cin >> t;
  while (t--) {
    cin >> n;
    ans = k = 0, x = n;
    for (LL i = 1; i <= m; i++) {
      sum = 0;
      while (!(n % p[i])) {
        sum++;
        n /= p[i];
      }
      if (ans < sum) {
        k = p[i], ans = sum;
      }
    }
    mul = 1;
    cout << max(ans, (LL)1) << endl;
    for (LL i = 1; i < ans; i++) {
      cout << k << " ";
      mul *= k;
    }
    cout << x / mul << endl;
  }
  return 0;
}
