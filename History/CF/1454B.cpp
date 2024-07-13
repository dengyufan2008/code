#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, mx, a[200001], d[200001];

void W() {
  for (int i = 1; i <= mx; i++) {
    if (a[i] == 1) {
      cout << d[i] << endl;
      return;
    }
  }
  cout << -1 << endl;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    fill(a + 1, a + mx + 1, 0), fill(d + 1, d + mx + 1, 0), mx = 0;
    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      mx = max(mx, tmp);
      a[tmp]++;
      if (!d[tmp]) {
        d[tmp] = i;
      }
    }
    W();
  }
  return 0;
}
