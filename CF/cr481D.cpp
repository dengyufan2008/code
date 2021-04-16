#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans, a[100001], b[100001];

bool P(int d) {
  ans = 0;
  copy(&a[3], &a[n] + 1, &b[3]);
  for (int i = 2, s = 0; i <= n; i++) {
    s = b[i + 1] - b[i] - d;
    if (s >= -1 && s <= 1) {
      ans++;
      b[i + 1] += s;
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = -1; i <= 1; i++) {  //枚举a[1],a[2]增量
    for (int j = -1; j <= 1; j++) {
      b[1] = a[1] + i, b[2] = a[2] + j;
      if (P(b[2] - b[1])) {
        cout << ans << endl;
        return 0;
      }
    }
  }
  cout << -1;
  return 0;
}
