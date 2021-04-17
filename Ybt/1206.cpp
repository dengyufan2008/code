#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, m, n;

int C(int m, int n) {  //m个苹果放在n个篮子的分法
  if (!m || n == 1) {
    return 1;
  } else if (n > m) {
    return C(m, m);
  }
  return C(m - n, n) + C(m, n - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> m >> n;
    cout << C(m, n) << endl;
  }
  return 0;
}
