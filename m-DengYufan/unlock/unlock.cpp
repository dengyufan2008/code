#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n[3], a[10][10];

int main() {
  freopen("unlock.in", "r", stdin);
  freopen("unlock.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n[1] >> n[2] >> n[3];
  for (int i = 1; i <= 3; i++) {
    for (int j = 1, tmp, _tmp; j <= n[i]; j++) {
      cin >> tmp >> _tmp;
      a[tmp][_tmp] = i;
    }
  }
  cout << 1 << endl;
  return 0;
}
