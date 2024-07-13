#include <bits/stdc++.h>
#define LL long long

using namespace std;

long double sx, sy, gx, gy;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> sx >> sy >> gx >> gy;
  cout << fixed << setprecision(10) << (sx * gy + gx * sy) / (sy + gy) << endl;
  return 0;
}
