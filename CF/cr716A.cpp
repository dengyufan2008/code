#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, a[101], b[101] = {1};
double tmp;

bool C(void) {
  for (LL i = 1; i <= n; i++) {
    b[i] = b[i - 1] * a[i];
    if (!a[i]) {
      return false;
    }
  }
  for (LL i = 1; i <= n; i++) {            //长度
    for (LL j = 1; j <= n - i + 1; j++) {  //起始
      tmp = sqrt(b[j + i - 1] / b[j - 1]);
      if (tmp != (LL)tmp) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    cout << (C() ? "YES" : "NO") << endl;
  }
  return 0;
}
