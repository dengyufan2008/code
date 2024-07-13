#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> x;
  cout << 100 - x % 100 << endl;
  return 0;
}
