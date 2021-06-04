#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, k, s, a[200002];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + m);
  a[++m] = n + 1;
  k = n;
  for (int i = 1; i <= m; i++) {
    if (a[i] > a[i - 1] + 1) {
      k = min(k, a[i] - a[i - 1] - 1);
    }
  }
  for (int i = 1; i <= m; i++) {
    if (a[i] > a[i - 1] + 1) {
      s += 1 + (a[i] - a[i - 1] - 2) / k;
    }
  }
  cout << s << endl;
  return 0;
}
