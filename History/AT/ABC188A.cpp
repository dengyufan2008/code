#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x, y;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> x >> y;
  cout << (min(x, y) + 3 > max(x, y) ? "Yes" : "No") << endl;
  return 0;
}
