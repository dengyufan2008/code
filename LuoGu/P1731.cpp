#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, m, s = 1e9;

void S(LL v, LL k, LL r, LL h, LL d) {
  if (r <= k || v < 0) {
    return;
  }
  if (!v && !k) {
    s = min(s, d);
  }
  for (LL i = r - 1; i; i--) {
    for (LL j = h - 1; j; j--) {
      S(v - i * i * j, k - 1, i, j, d + 2 * i * j);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  S(n, m, sqrt(n) + 1, n + 1, 0);
  cout << s << endl;
  return 0;
}
