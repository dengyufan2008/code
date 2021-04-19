#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[101], b[101] = {1};
double tmp;

bool C(void) {
  for (int i = 1; i <= n; i++) {
    b[i] = b[i - 1] * a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n - i + 1; j++) {
      tmp = sqrt(b[j + i - 1] / b[j - 1]);
      if (tmp != (int)tmp) {
        return false;
      }
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
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    cout << (C() ? "NO" : "YES") << endl;
  }
  return 0;
}
