#include <bits/stdc++.h>
#define LL long long

using namespace std;

int v, t, s, d;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> v >> t >> s >> d;
  cout << (d < t * v || d > s * v ? "Yes" : "No") << endl;
  return 0;
}
