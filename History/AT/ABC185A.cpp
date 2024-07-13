#include <bits/stdc++.h>
#define LL long long

using namespace std;

int mn = 101;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  for (int i = 1, tmp; i <= 4; i++) {
    cin >> tmp;
    mn = min(mn, tmp);
  }
  cout << mn << endl;
  return 0;
}
