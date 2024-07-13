#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL a, b, k, f[31][31];

string M(LL a, LL b, LL k) {
  if (!a) {
    return string(b, 'b');
  } else if (!b) {
    return string(a, 'a');
  } else if (k <= f[a - 1][b]) {
    return "a" + M(a - 1, b, k);
  } else {
    return "b" + M(a, b - 1, k - f[a - 1][b]);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> k;
  f[0][0] = 1;
  for (int i = 0; i <= a; i++) {
    for (int j = 0; j <= b; j++) {
      f[i][j] += (i > 0) * f[i - 1][j] + (j > 0) * f[i][j - 1];
    }
  }
  cout << M(a, b, k) << endl;
  return 0;
}
