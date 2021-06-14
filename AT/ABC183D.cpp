#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, w, a[200002];

bool C() {
  for (LL i = 1; i <= 200001; i++) {
    a[i] += a[i - 1];
    if (a[i] > w) {
      return false;
    }
  }
  return true;
}
int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> w;
  for (LL i = 1, s, t, p; i <= n; i++) {
    cin >> s >> t >> p;
    a[s + 1] += p, a[t + 1] -= p;
  }
  cout << (C() ? "Yes" : "No") << endl;
  return 0;
}
