#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, a[100001], b[100001], tot;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= n; i++) {
    tot += a[i] * b[i];
  }
  cout << (tot == 0 ? "Yes" : "No") << endl;
  return 0;
}
