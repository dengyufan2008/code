#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a1, a2, a3;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a1 >> a2 >> a3;
  cout << (a1 - a2 == a2 - a3 || a1 - a3 == a3 - a2 || a2 - a1 == a1 - a3 || a2 - a3 == a3 - a1 || a3 - a1 == a1 - a2 || a3 - a2 == a2 - a1 ? "Yes" : "No") << endl;
  return 0;
}
