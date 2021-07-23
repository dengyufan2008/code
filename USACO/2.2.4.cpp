/*
ID: dengyuf1
TASK: subset
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

int n, ans;

void S(int x, int t) {
  if (x < 0) {
    return;
  } else if (!x) {
    ans++;
    return;
  }
  for (int i = t + 1; i <= n; i++) {
    S(x - i, i);
  }
}

int main() {
  // freopen("subset.in", "r", stdin);
  // freopen("subset.out", "w", stdout);
  cin >> n;
  S(n - 1, 1);
  cout << ans << endl;
  return 0;
}
