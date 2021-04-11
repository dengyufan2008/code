#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t;
LL p, a, b, c, al, bl, cl;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> p >> a >> b >> c;
    al = a - p % a, bl = b - p % b, cl = c - p % c;
    if(al == a || bl == b || cl == c) {
      cout << 0 << endl;
    } else {
      cout << min(al, min(bl, cl)) << endl;
    }
  }
  return 0;
}
