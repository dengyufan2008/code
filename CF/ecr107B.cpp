#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, a, b, c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    cout << (int)(pow(10, a - 1) + pow(10, c - 1)) << " " << (int)pow(10, b - 1) << endl;
  }
  return 0;
}
