#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, x[101], y[101];

bool C() {
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = j + 1; k <= n; k++) {
        if ((x[i] - x[k]) * (y[j] - y[k]) == (x[j] - x[k]) * (y[i] - y[k])) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << (C() ? "Yes" : "No") << endl;
  return 0;
}
