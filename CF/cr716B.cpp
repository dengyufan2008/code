#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, k;

LL P(LL n, LL k) {
  if (n == 1) {
    return 1;
  }
  LL num = 0;
  for (int i = 0; i < k; i++) {
    num += P(n - 1, i);
  }
  return num;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    cout << P(n, k) << endl;
  }
  return 0;
}
