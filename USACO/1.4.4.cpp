/*
ID: dengyuf1
TASK: combo
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans = 1, a[4], b[4];

int main() {
  freopen("combo.in", "r", stdin);
  freopen("combo.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= 3; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= 3; i++) {
    cin >> b[i];
  }
  if (n < 5) {
    cout << n * n * n << endl;
    return 0;
  }
  for (int i = 1; i <= 3; i++) {
    ans *= max(5 - min(max(a[i], b[i]) - min(a[i], b[i]), min(a[i], b[i]) - max(a[i], b[i]) + n), 0);
  }
  cout << 250 - ans << endl;
  return 0;
}
