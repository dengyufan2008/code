/*
ID: dengyuf1
TASK: money
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

LL v, n, a[26], f[26][10001];

LL S(LL l, LL x) {
  if (l <= 0) {
    return 0;
  } else if (x <= 0) {
    return x == 0;
  } else if (f[l][x] != 1145141919810) {
    return f[l][x];
  } else {
    return f[l][x] = S(l, x - a[l]) + S(l - 1, x);
  }
}

int main() {
  freopen("money.in", "r", stdin);
  freopen("money.out", "w", stdout);
  cin >> n >> v;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&f[0][0], &f[25][10000] + 1, 1145141919810);
  cout << S(n, v) << endl;
  return 0;
}
