#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL a, b, k, d[31][31];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> k;
  for (int i = 1; i <= 30; i++) {
    d[i][0] = d[0][i] = 1;
  }
  for (int i = 1; i <= 30; i++) {
    for (int j = 1; j <= 30; j++) {
      d[i][j] = d[i - 1][j] + d[i][j - 1];
    }
  }
  while (a || b) {
    if (a && (d[a - 1][b] >= k || !b)) {
      cout << 'a';
      a--;
    } else {
      cout << 'b';
      k -= d[a][b-- - 1];
    }
  }
  return 0;
}
