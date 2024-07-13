/*
ID: dengyuf1
TASK: dualpal
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, s, ans;

bool C(int n, int k) {
  int p = 0, a[101] = {};
  while (n) {
    a[++p] = n % k;
    n /= k;
  }
  for (int i = 1, j = p; i < j; i++, j--) {
    if (a[i] != a[j]) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("dualpal.in", "r", stdin);
  freopen("dualpal.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> s;
  for (int i = s + 1, num = 0; ans < n; i++, num = 0) {
    for (int j = 2; j <= 10 && num < 2; j++) {
      num += C(i, j);
    }
    if (num >= 2) {
      ans++;
      cout << i << endl;
    }
  }
  return 0;
}
