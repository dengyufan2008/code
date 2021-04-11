#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, h, ans, s[5001], v[5001];

int main() {
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
    }
    fill(&v[1], &v[n] + 1, 0);
    for (h = 1, ans = 0; s[h] == 1; h++) {
    }
    for (; h <= n; h++) {
      v[h] += s[h] - 1;
      for (int i = h + 2; i <= h + s[h]; i++) {
        v[i]++;
      }
      if (v[h] > s[h] - 1) {
        v[h + 1] += v[h] - s[h] + 1;
      }
      ans += max(s[h] - v[h] - 1, 0);
    }
    cout << ans << endl;
  }
  return 0;
}
