#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, p[100001], mx[100001];

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> p[i];
      mx[i] = (p[mx[i - 1]] < p[i] ? i : mx[i - 1]);
    }
    for (int i = n; i >= 1; i--) {
      for (int j = mx[i]; j <= n; j++) {
        cout << p[j] << " ";
      }
      n = mx[i] - 1;
    }
    cout << endl;
  }
  return 0;
}
