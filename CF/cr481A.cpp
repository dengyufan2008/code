#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, a[51];
bool b[51], p[1001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  m = n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    if (p[a[i]]) {
      m--;
      b[i] = true;
    } else {
      p[a[i]] = true;
    }
  }
  cout << m << endl;
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      cout << a[i] << " ";
    }
  }
  return 0;
}
