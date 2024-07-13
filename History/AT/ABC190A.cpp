#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a, b, c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c;
  cout << (!c && a > b || c && a >= b ? "Takahashi" : "Aoki") << endl;
  return 0;
}
